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

	pargeo::commandLine P(argc, argv, "<inFile>");
	char* iFile = P.getArgument(0);

	parlay::sequence<pointD> ptrs = pargeo::pointIO::readPointsFromFile<pointD>(iFile);

	parlay::sort_inplace(ptrs, pointD::attComp);

	int n = ptrs.size();
	parlay::sequence<pointD> sptrs(ptrs);

	parlay::sequence<int> depPtr(n);


	pargeo::pdKdTree::tree<dim, pointD>* root = pargeo::pdKdTree::build<dim, pointD>(sptrs, true, 16);
	root->pargeo::pdKdTree::node<dim, pointD>::initParallel();

	depPtr[n-1] = -1;
	root->activateItem(n-1);
	for(int i=n-2;i>=0;i--){
		pointD* ptr = root->NearestNeighbor(i);
		if(ptr)
			depPtr[i] = ptr->attribute;
		else
			depPtr[i] = -1;
		root->activateItem(i);
	}

	for(int i=0;i<n;i++){
		std::cout<<i<<"  ;  "<<ptrs[i][0]<<" "<<ptrs[i][1]<<":"<<ptrs[depPtr[i]][0]<<" "<<ptrs[depPtr[i]][1]<<"  ;  "<<depPtr[i]<<std::endl;
	}

}



















