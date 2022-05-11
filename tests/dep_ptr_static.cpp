#include<iostream>
#include<fstream>
#include<algorithm>

#include "parlay/parallel.h"
#include "parlay/sequence.h"
#include "parlay/primitives.h"
#include "pargeo/parseCommandLine.h"
#include "pargeo/pointIO.h"
#include "pargeo/point.h"
#include "pargeo/getTime.h"
#include "pseudoDynamicKdTree/pdKdTree.h"

static const int dim = 2;
using point = pargeo::point<dim>;
using pointD = pargeo::pointD<dim, int>;


int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(0);

	pargeo::timer queryT, updateT;

	pargeo::commandLine P(argc, argv, "-i{inFile}");
	char* iFile = P.getOptionValue("-i");

	parlay::sequence<pointD> ptrs = pargeo::pointIO::readPointsFromFile<pointD>(iFile);

	int n = ptrs.size();
	parlay::sequence<int> depPtr(n);

	parlay::stable_sort_inplace(ptrs, pointD::attComp);
	parlay::sequence<pointD> sptrs(ptrs);

	pargeo::pdKdTree::tree<dim, pointD>* root = pargeo::pdKdTree::build<dim, pointD>(sptrs, true, 16);
	root->pargeo::pdKdTree::node<dim, pointD>::initParallel();

	depPtr[n-1] = -1;
	root->activateItem(n-1);
	
	for(int i=n-2;i>=0;i--){
		queryT.start();
		pointD* ptr = root->NearestNeighbor(i);
		queryT.stop();

		if(ptr)
			depPtr[i] = ptr->attribute;
		else
			depPtr[i] = -1;

		updateT.start();
		root->activateItem(i);
		updateT.stop();
	}

	std::cout<<"query time: "<<queryT.get_total()<<std::endl;
	std::cout<<"update time: "<<updateT.get_total()<<std::endl;

	// for(int i=0;i<n;i++){
	// 	std::cout<<i<<"  ;  "<<ptrs[i][0]<<" "<<ptrs[i][1]<<":"<<ptrs[depPtr[i]][0]<<" "<<ptrs[depPtr[i]][1]<<"  ;  "<<depPtr[i]<<" ; "<<ptrs[i].dist(ptrs[depPtr[i]])<<std::endl;
	// }

}



















