#include<iostream>
#include<fstream>
#include<algorithm>

#include "parlay/parallel.h"
#include "parlay/sequence.h"
#include "parlay/primitives.h"
#include "pargeo/parseCommandLine.h"
#include "pargeo/pointIO.h"
#include "pargeo/point.h"
#include "pargeo/atomics.h"
#include "pargeo/getTime.h"

#include "parameter.h"


int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(0);

	pargeo::timer time;

	pargeo::commandLine P(argc, argv, "-i{inFile}");
	char* iFile = P.getOptionValue("-i");

	parlay::sequence<pointD> ptrs = pargeo::pointIO::readPointsFromFile<pointD>(iFile);

	time.start();

	parlay::stable_sort_inplace(ptrs, pointD::attComp);

	int n = ptrs.size();

	parlay::sequence<int> depPtr(n,-1);
	std::cout<<"preprocessing time: "<<time.get_next()<<std::endl;

	parlay::parallel_for(0, n, [&](int i){
		auto compDist = [&](size_t a, size_t b){
			if(b == -1) return true;
			if(a == -1) return false; // -1 is greatest
			return ptrs[i].dist(ptrs[a]) < ptrs[i].dist(ptrs[b]);
		};
		parlay::parallel_for(i+1, n, [&](int j){
		        pargeo::write_min(&depPtr[i], j, compDist);
		});
	});

	std::cout<<"update query time: "<<time.get_next()<<std::endl;
	// for(int i=0;i<n;i++){
	//  	std::cout<<i<<"  ;  "<<ptrs[i][0]<<" "<<ptrs[i][1]<<":"<<ptrs[depPtr[i]][0]<<" "<<ptrs[depPtr[i]][1]<<"  ;  "<<depPtr[i]<<" ; "<<ptrs[i].dist(ptrs[depPtr[i]])<<std::endl;
	// }

}
