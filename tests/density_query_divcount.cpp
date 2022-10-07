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
#include "pargeo/ball.h"
#include "pargeo/getTime.h"
#include "divCount/divCount.h"

#include "parameter.h"


parlay::sequence<pointD> compute_densities(parlay::sequence<point>& ptrs){
	pargeo::divCount<dim, point, ball> divCounter;
	parlay::sequence<ball *> regions(ptrs.size());
	parlay::parallel_for(0, ptrs.size(), [&](size_t i){
		regions[i] = new ball(ptrs[i], drange);
	});
	parlay::sequence<point *> points(ptrs.size());
	parlay::parallel_for(0, ptrs.size(), [&](size_t i){
		points[i] = &ptrs[i];
	});
	parlay::sequence<int> counter(ptrs.size());
	divCounter.recurseCount(parlay::make_slice(points), parlay::make_slice(regions), counter, 16);
	parlay::sequence<pointD> ptrDs(ptrs.size());
	parlay::parallel_for(0, ptrs.size(), [&](size_t i){
		ptrDs[i] = pointD(ptrs[i].coords(), counter[i]);
	});
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
	
	for(int i=0;i<ptrDs.size();i++){
	  for(int d=0;d<dim;d++){
	    fout<<ptrDs[i][d]<<" ";
	  }
	  fout<<ptrDs[i].attribute<<'\n';
	}

	fout.close();
}
