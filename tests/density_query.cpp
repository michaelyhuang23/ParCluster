#include<iostream>
#include<fstream>
#include<string.h>
#include<algorithm>

#include "parlay/parallel.h"
#include "parlay/sequence.h"
#include "parlay/primitives.h"
#include "pargeo/parseCommandLine.h"
#include "pargeo/pointIO.h"
#include "pargeo/point.h"
#include "pargeo/getTime.h"
#include "kdTree/kdTree.h"

#include "parameter.h"


parlay::sequence<pointD> compute_densities(parlay::sequence<point>& ptrs){
	pargeo::kdTree::node<dim, point>* tree = 
		pargeo::kdTree::build<dim, point>(ptrs, true, 1);
	

	parlay::sequence<pointD> ptrDs(ptrs.size());

	parlay::parallel_for(0, ptrs.size(), [&](size_t i){
		ptrDs[i] = pointD(ptrs[i].coords(), pargeo::kdTree::rangeCount(tree, ptrs[i], drange));
	}, 1);

	return ptrDs;
}



int main(int argc, char* argv[]) {
	pargeo::timer time;

	pargeo::commandLine P(argc, argv, "-r{radiu} -i{inFile} -o{outFile}");
	drange = P.getOptionDoubleValue("-r", 10);
	char* iFile = P.getOptionValue("-i");
	char* oFile = P.getOptionValue("-o");

	std::cout<<"reading from: "<<iFile<<std::endl;
	std::cout<<"writing to: "<<oFile<<std::endl;

	std::ofstream fout(oFile);

	parlay::sequence<point> ptrs = pargeo::pointIO::readPointsFromFile<point>(iFile);

	time.start();

	parlay::sequence<pointD> ptrDs = compute_densities(ptrs);

	std::cout<<"density time: "<<time.get_next()<<std::endl;

	long long sum = 0;
	for(size_t i=0;i<ptrDs.size();i++){
	  for(int d=0;d<dim;d++){
	    fout<<ptrDs[i][d]<<" ";
	  }
	  fout<<ptrDs[i].attribute<<'\n';
	  sum += ptrDs[i].attribute;
	}

	std::cout<<"average density: "<<(double)sum/ptrDs.size()<<std::endl;
	std::cout<<"average percentage: "<<(double)sum/ptrDs.size()/ptrDs.size()<<std::endl;

	fout.close();
}
