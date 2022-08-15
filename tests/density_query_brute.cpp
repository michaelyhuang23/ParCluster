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

static double drange = 10;





parlay::sequence<pointD> compute_densities(parlay::sequence<point>& ptrs){
    parlay::sequence<pointD> ptrDs(ptrs.size());

	parlay::parallel_for(0, ptrDs.size(), [&](size_t i){
		ptrDs[i] = pointD(ptrs[i].coords(), 0);
		for(size_t j=0;j<ptrDs.size();j++)
			if(ptrs[j].dist(ptrs[i]) <= drange)
				ptrDs[i].attribute++;
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
		fout<<ptrDs[i][0]<<" "<<ptrDs[i][1]<<" "<<ptrDs[i].attribute<<'\n';
	}

	fout.close();
}
