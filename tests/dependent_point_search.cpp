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
#include "kdTree/kdTree.h"
#include "dynamicKdTree/dynKdTree.h"

static const int dim = 2;
using point = pargeo::point<dim>;
using pointD = pargeo::pointD<dim, int>;


int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(0);

	std::cout<<sizeof(typename pargeo::_empty)<<std::endl;
	pargeo::timer time;

	pargeo::commandLine P(argc, argv, "<inFile>");
	char* iFile = P.getArgument(0);

	parlay::sequence<pointD> ptrs = pargeo::pointIO::readPointsFromFile<pointD>(iFile);

	time.start();

	for(int i=0;i<10;i++){
		std::cout<<ptrs[i].attribute<<" ";
	}
	std::cout<<std::endl;

	parlay::sort_inplace(ptrs, pointD::attComp);

	int n = ptrs.size();

	parlay::parallel_for(0, n, [&](int i){
		ptrs[i].attribute = i;
	});


	assert(n >= 2);

	pargeo::dynKdTree::rootNode<dim, pointD> tree(ptrs, n-2, n);

	parlay::sequence<int> depPtr(n);

	depPtr[n-1] = -1;
	depPtr[n-2] = n-1;

	std::cout<<"preprocessing time: "<<time.get_next()<<std::endl;

	for(int i=n-3;i>=0;--i){
		auto ret = tree.kNN(ptrs[i], 1);
		depPtr[i] = ret[0].attribute;

		tree.insert(ptrs, i, i+1);
	}

	std::cout<<"insert+query time: "<<time.get_next()<<std::endl;


}
