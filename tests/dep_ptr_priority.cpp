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
#include "priorityKdTree/psKdTree.h"

#include "parameter.h"


int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(0);

	pargeo::timer queryT, prepT;

	pargeo::commandLine P(argc, argv, "-i{inFile}");
	char* iFile = P.getOptionValue("-i");

	parlay::sequence<pointD> ptrs = pargeo::pointIO::readPointsFromFile<pointD>(iFile);

	prepT.start();
	int n = ptrs.size();
	parlay::sequence<int> depPtr(n);

	parlay::stable_sort_inplace(ptrs, pointD::attCompRev);
	parlay::sequence<pointD> sptrs(ptrs);

	pargeo::psKdTree::tree<dim, pointD>* root = pargeo::psKdTree::build<dim, pointD>(sptrs, true, 16);
	root->pargeo::psKdTree::node<dim, pointD>::initParallel();

	std::cout<<"prep time: "<<prepT.get_next()<<std::endl;

	queryT.start();

	depPtr[0] = -1;
	
	for(int i=1;i<n;i++){
		pointD* ptr = root->NearestNeighborBounded(i);
		if(ptr)
			depPtr[i] = ptr->attribute;
		else
			depPtr[i] = -1;
	}

	std::cout<<"query time: "<<queryT.get_next()<<std::endl;


	for(int i=0;i<n;i++){
	 	std::cout<<i<<"  ;  "<<ptrs[i][0]<<" "<<ptrs[i][1]<<":"<<ptrs[depPtr[i]][0]<<" "<<ptrs[depPtr[i]][1]<<"  ;  "<<depPtr[i]<<" ; "<<ptrs[i].dist(ptrs[depPtr[i]])<<std::endl;
		}

}



















