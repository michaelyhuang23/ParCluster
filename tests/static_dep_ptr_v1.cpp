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
	char* iFile = P.getArgument(0);

	parlay::sequence<pointD> ptrs = pargeo::pointIO::readPointsFromFile<pointD>(iFile);

	time.start();
	int n = ptrs.size();
	parlay::sequence<int> depPtr(n);

	parlay::stable_sort_inplace(ptrs, pointD::attComp);
	parlay::sequence<pointD> sptrs(ptrs);

	parlay::sequence<int> transition(n);
	transition[n-1] = n-1;
	parlay::parallel_for(0, n-1, [&](int i){
		transition[i] = (ptrs[i].attribute < ptrs[i+1].attribute) ? i : -1;
	});
	parlay::sequence<int> backLoc = parlay::filter(transition, [&](int i){return i>-1;});
	int m = backLoc.size();
	// for(int i=0;i<backLoc.size();i++)
	// 	std::cout<<backLoc[i]<<" ";
	// std::cout<<std::endl;

	if(m == 1){
		parlay::parallel_for(0,n,[&](int i){
			depPtr[i] = -1;
		});

		for(int i=0;i<n;i++){
			std::cout<<i<<"  ;  "<<ptrs[i][0]<<" "<<ptrs[i][1]<<":"<<ptrs[depPtr[i]][0]<<" "<<ptrs[depPtr[i]][1]<<"  ;  "<<depPtr[i]<<" ; "<<ptrs[i].dist(ptrs[depPtr[i]])<<std::endl;
		}
		return 1;
	}

	pargeo::pdKdTree::tree<dim, pointD>* root = pargeo::pdKdTree::build<dim, pointD>(sptrs, true, 16);
	root->pargeo::pdKdTree::node<dim, pointD>::initParallel();

	// std::cout<<"preprocessing time: "<<time.get_next()<<std::endl;

	// for(int i=backLoc[m-2]+1; i<n; i++){
	// 	depPtr[i] = -1;
	// 	root->activateItem(i);
	// }
	parlay::parallel_for(backLoc[m-2]+1, n, [&](int i){
		depPtr[i] = -1;
		root->activateItem(i);
	});
	
	for(int i=m-2;i>=0;i--){
		int st = 0, et = backLoc[i];
		if(i>0) st = backLoc[i-1]+1;

		// for(int i=st;i<et+1;i++){
		// 	pointD* ptr = root->NearestNeighbor(i);
		// 	if(ptr)
		// 		depPtr[i] = ptr->attribute;
		// 	else
		// 		depPtr[i] = -1;
		// }
		parlay::parallel_for(st, et+1, [&](int i){
			pointD* ptr = root->NearestNeighbor(i);
			if(ptr)
				depPtr[i] = ptr->attribute;
			else
				depPtr[i] = -1;
		});

		// for(int i=st;i<et+1;i++){
		// 	root->activateItem(i);
		// }
		parlay::parallel_for(st, et+1, [&](int i){
			root->activateItem(i);
		});
	}

	// std::cout<<"update query time: "<<time.get_next()<<std::endl;

	for(int i=0;i<n;i++){
		std::cout<<i<<"  ;  "<<ptrs[i][0]<<" "<<ptrs[i][1]<<":"<<ptrs[depPtr[i]][0]<<" "<<ptrs[depPtr[i]][1]<<"  ;  "<<depPtr[i]<<" ; "<<ptrs[i].dist(ptrs[depPtr[i]])<<std::endl;
	}

}



















