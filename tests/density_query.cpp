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

static const int dim = 2;
static const double drange = 20;
using point = pargeo::point<dim>;
using pointD = pargeo::pointD<dim, int>;






parlay::sequence<pointD> compute_densities(parlay::sequence<point>& ptrs){
	pargeo::timer tt; tt.start();
	pargeo::kdTree::node<dim, point>* tree = 
		pargeo::kdTree::build<dim, point>(ptrs, true, 16);
	

	parlay::sequence<pointD> ptrDs(ptrs.size());

	parlay::parallel_for(0, ptrs.size(), [&](size_t i){
		ptrDs[i] = pointD(ptrs[i].coords(), pargeo::kdTree::rangeCount(tree, ptrs[i], drange));
	});

	return ptrDs;
}



int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(0);

	pargeo::timer time;

	pargeo::commandLine P(argc, argv, "<inFile>");
	char* iFile = P.getArgument(0);

	parlay::sequence<point> ptrs = pargeo::pointIO::readPointsFromFile<point>(iFile);

	time.start();

	parlay::sequence<pointD> ptrDs = compute_densities(ptrs);

	for(int i=0;i<ptrDs.size();i++){
		std::cout<<ptrDs[i][0]<<" "<<ptrDs[i][1]<<" "<<ptrDs[i].attribute<<'\n';
	}

	std::cout<<"density time: "<<time.get_next()<<std::endl;
}
