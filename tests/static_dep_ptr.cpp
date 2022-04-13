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

	pargeo::timer time;

	pargeo::commandLine P(argc, argv, "<inFile>");
	//char* iFile = P.getArgument(0);

    char* iFile = "../../tests/example_point_cloud_dense.txt";

	parlay::sequence<pointD> ptrs = pargeo::pointIO::readPointsFromFile<pointD>(iFile);

	time.start();

	for(int i=0;i<10;i++){
		std::cout<<ptrs[i].attribute<<" ";
	}
	std::cout<<std::endl;

	parlay::sequence<pointD> sptrs = parlay::sort(ptrs, pointD::attComp);

	int n = ptrs.size();

	parlay::sequence<int> depPtr(n);


	std::cout<<"preprocessing time: "<<time.get_next()<<std::endl;

	pargeo::pdKdTree::tree<dim, pointD>* root = pargeo::pdKdTree::build<dim, pointD>(sptrs, false, 16);
	root->pargeo::pdKdTree::node<dim, pointD>::initSerial();

	root->print_data();
	
	std::cout<<"construction time: "<<time.get_next()<<std::endl;

	depPtr[n-1] = -1;
	root->activateItem(n-1);
	for(int i=n-2;i>=0;i--){
		parlay::sequence<size_t> I = pargeo::pdKdTree::Knn<dim, pointD>(ptrs[i], 1, root);
		assert(I.size() > 0);
		depPtr[i] = I[0];

		root->activateItem(i);
	}

	std::cout<<"insert+query time: "<<time.get_next()<<std::endl;


}
