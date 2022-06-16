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

	pargeo::timer queryT, prepT;

	pargeo::commandLine P(argc, argv, "-i{inFile}");
	char* iFile = P.getOptionValue("-i");

	parlay::sequence<pointD> ptrs = pargeo::pointIO::readPointsFromFile<pointD>(iFile);

	prepT.start();
	int n = ptrs.size();
	parlay::sequence<int> depPtr(n);

	parlay::stable_sort_inplace(ptrs, pointD::attCompRev);
	parlay::sequence<pointD> sptrs(ptrs);

	pargeo::pdKdTree::tree<dim, pointD>* root = pargeo::pdKdTree::build<dim, pointD>(sptrs, true, 16);
	root->pargeo::pdKdTree::node<dim, pointD>::initParallel();

	std::cout<<"prep time: "<<prepT.get_next()<<std::endl;
	
	queryT.start();

	depPtr[0] = -1;
	root->activateItem(0);
	
	for(int i=1;i<n;i++){
		pointD* ptr = root->NearestNeighbor(i);
	
		if(ptr)
			depPtr[i] = ptr->attribute;
		else
			depPtr[i] = -1;

		root->activateItem(i);
	}

	std::cout<<"query time: "<<queryT.get_next()<<std::endl;

/*	for(int i=0;i<n;i++){
	 	std::cout<<i<<"  ;  "<<ptrs[i][0]<<" "<<ptrs[i][1]<<":"<<ptrs[depPtr[i]][0]<<" "<<ptrs[depPtr[i]][1]<<"  ;  "<<depPtr[i]<<" ; "<<ptrs[i].dist(ptrs[depPtr[i]])<<std::endl;
		}*/

}



















