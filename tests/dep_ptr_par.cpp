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
#include "fenwickKdTree/fenwickKdTree.h"

static const int dim = 2;
using point = pargeo::point<dim>;
using pointD = pargeo::pointD<dim, int>;

int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(0);

	pargeo::timer prepT, queryT;

	pargeo::commandLine P(argc, argv, "-i{inFile}");
	char* iFile = P.getOptionValue("-i");

	parlay::sequence<pointD> ptrsD = pargeo::pointIO::readPointsFromFile<pointD>(iFile);

	prepT.start();
	int n = ptrsD.size();
	
	parlay::stable_sort_inplace(ptrsD, pointD::attCompRev);
	parlay::sequence<point> ptrs(n);
	parlay::parallel_for(0, n, [&](size_t i){ ptrs[i] = point(ptrsD[i].coords()); });
		
	pargeo::fenwickKdTree<dim> trees(ptrs);

	parlay::sequence<int> depPtr(n);
	depPtr[0] = -1;

	std::cout<<"preprocess time: "<<prepT.get_next()<<std::endl;

	queryT.start();
//	for(size_t idx = 1;idx<n;idx++){
//		depPtr[idx] = trees.query(idx-1, ptrs[idx]).first;
//	}
	parlay::parallel_for(1, n,
						 [&](size_t idx){
							 depPtr[idx] = trees.query(idx-1, ptrs[idx]).first;
						 });

	std::cout<<"query time: "<<queryT.get_next()<<std::endl;


/*	for(int i=0;i<n;i++){
	 	std::cout<<i<<"  ;  "<<ptrs[i][0]<<" "<<ptrs[i][1]<<":"<<ptrs[depPtr[i]][0]<<" "<<ptrs[depPtr[i]][1]<<"  ;  "<<depPtr[i]<<" ; "<<ptrs[i].dist(ptrs[depPtr[i]])<<std::endl;
		}*/
}


















