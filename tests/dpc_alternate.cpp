#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <unordered_set>

#include "parlay/parallel.h"
#include "parlay/sequence.h"
#include "parlay/primitives.h"
#include "pargeo/parseCommandLine.h"
#include "pargeo/pointIO.h"
#include "pargeo/point.h"
#include "pargeo/getTime.h"
#include "pargeo/unionFind.h"
#include "priorityKdTree/psKdTree.h"
#include "origKdTree/kdTree.h"

#include "parameter.h"


parlay::sequence<pointF> compute_densities(parlay::sequence<point>& ptrs, int K){
	pargeo::origKdTree::node<dim, point>* tree = 
		pargeo::origKdTree::build<dim, point>(ptrs, true, 1);
	
	parlay::sequence<pointF> ptrDs(ptrs.size());

	auto knns = pargeo::origKdTree::batchKnn(ptrs, K, tree);

	parlay::parallel_for(0, ptrs.size(), [&](size_t i){
		float dist = ptrs[knns[i * K + K - 1]].dist(ptrs[i]);
		ptrDs[i] = pointF(ptrs[i].coords(), 1.0/dist);
	});

	return ptrDs;
}




int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(0);

	pargeo::timer densityT, depT, linkageT, totalT;

	pargeo::commandLine P(argc, argv, "-n{noiseCut} -d{depCut} -i{inFile} -k{densityK} -o{outFile}");
	noiseCut = P.getOptionDoubleValue("-n", 0);
	depCut = P.getOptionDoubleValue("-d", 0);
	int K = P.getOptionIntValue("-k", 6);

	char* iFile = P.getOptionValue("-i");
	std::string oFile = P.getOptionValue("-o", std::string(""));
	std::string dFile = P.getOptionValue("-decision", std::string(""));

	std::cout << "num_thread: " << parlay::num_workers() << std::endl;

	parlay::sequence<point> ptrs = pargeo::pointIO::readPointsFromFile<point>(iFile);
	int n = ptrs.size();
	std::cout << "n: " << n << std::endl;
	
	densityT.start(); totalT.start();
	parlay::sequence<pointF> ptrDs = compute_densities(ptrs, K);
	std::cout<< "density: "<<densityT.get_next()<<std::endl;

	depT.start();
	parlay::sequence<int> depPtr(n);
	parlay::sequence<pointF> sptrs(ptrDs);
	parlay::sequence<int> inverseMap(n);
	parlay::parallel_for(0, n, [&inverseMap](int i){ inverseMap[i] = i; });
	parlay::stable_sort_inplace(inverseMap, [&](int a, int b){ return pointF::attCompRev(sptrs[a], sptrs[b]); });
	parlay::stable_sort_inplace(ptrDs, pointF::attCompRev);

	pargeo::psKdTree::tree<dim, pointF>* root = pargeo::psKdTree::build<dim, pointF>(ptrDs, true, 16);
	root->pargeo::psKdTree::node<dim, pointF>::initParallel();
	parlay::parallel_for(0, n, [&](size_t i){
		pointF* ptr = root->NearestNeighborBounded(i);
		if(ptr)
			depPtr[inverseMap[i]] = inverseMap[ptr->attribute];
		else
			depPtr[inverseMap[i]] = -1;
	},1);
	std::cout<< "dependent: "<< depT.get_next()<<std::endl;

	linkageT.start();
	pargeo::unionFind<int> UF(n);
	parlay::parallel_for(0, n, [&](int i){
		if(sptrs[i].attribute >= noiseCut){
			if(depPtr[i] != -1 && (sptrs[i].distSqr(sptrs[depPtr[i]]) < depCut * depCut)){
				UF.link(i, depPtr[i]);
			}
		}
	});

	parlay::sequence<int> cluster(n);
	parlay::parallel_for(0, n, [&](int i){
		cluster[i] = UF.find(i);
	});
	std::cout<< "link:" <<linkageT.get_next()<<std::endl;
	std::cout<< "total:" <<totalT.get_next()<<std::endl;


	if(dFile.size()>0){
		std::ofstream fout(dFile);
		for(int i=0;i<n;i++) fout<<sptrs[i].attribute<<" "<<sptrs[i].dist(sptrs[depPtr[i]])<<'\n';
		fout.close();
	}

	if(oFile.size()>0){
		std::ofstream fout(oFile);
		for(int i=0;i<n;i++) fout<<cluster[i]<<'\n';
		fout.close();
	}
}