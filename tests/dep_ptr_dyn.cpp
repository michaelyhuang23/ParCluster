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
#include "dynamicKdTree/dynKdTree.h"

#include "parameter.h"


int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(0);

	pargeo::timer queryT;

	pargeo::commandLine P(argc, argv, "-i{inFile}");
	char* iFile = P.getOptionValue("-i");

	parlay::sequence<pointD> ptrs = pargeo::pointIO::readPointsFromFile<pointD>(iFile);

	// time.start();
	queryT.start();

	parlay::stable_sort_inplace(ptrs, pointD::attComp);

	int n = ptrs.size();

	parlay::parallel_for(0, n, [&](int i){
		ptrs[i].attribute = i;
	});


	assert(n >= 2);

	pargeo::dynKdTree::rootNode<dim, pointD> tree(ptrs, n-2, n);

	parlay::sequence<int> depPtr(n);

	depPtr[n-1] = -1;
	depPtr[n-2] = n-1;

	// std::cout<<"preprocessing time: "<<time.get_next()<<std::endl;

	for(int i=n-3;i>=0;--i){
		auto ret = tree.kNN(ptrs[i], 1);
		depPtr[i] = ret[0].attribute;
		tree.insert(ptrs, i, i+1);
	}
	std::cout<<"place holder: 0.00"<<std::endl;
	std::cout<<"total time: "<<queryT.stop()<<std::endl;
	// std::cout<<"update query time: "<<time.get_next()<<std::endl;
	// for(int i=0;i<n;i++){
		// std::cout<<i<<"  ;  "<<ptrs[i][0]<<" "<<ptrs[i][1]<<":"<<ptrs[depPtr[i]][0]<<" "<<ptrs[depPtr[i]][1]<<"  ;  "<<depPtr[i]<<" ; "<<ptrs[i].dist(ptrs[depPtr[i]])<<std::endl;
	// }

}
