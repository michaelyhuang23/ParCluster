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
using point = pargeo::point<dim>;
using pointD = pargeo::pointD<dim, int>;


struct fenwickTree{
	int n;
	parlay::sequence<point> ptrs;
	parlay::sequence<pargeo::kdTree::node<dim, point>*> tree;
	static inline size_t lowbit(size_t num){ return num&(-num); }
	fenwickTree(parlay::sequence<point>& ptrs_) : n(ptrs_.size()), ptrs(ptrs_) {
		tree = parlay::sequence<pargeo::kdTree::node<dim, point>*>(n+1);
		for(size_t i = 1; i <= n; i++){
			size_t st = i-lowbit(i)+1-1;
			tree[i] = pargeo::kdTree::build<dim, point>(ptrs.cut(st, i+1-1), true, 16);
		}
	}
	std::pair<size_t, point> query(int idx, point& q){
		idx++;
		double dist = std::numeric_limits<double>::max()/2;
		size_t oid = -1;
		for(; idx > 0; idx -= lowbit(idx)){
			parlay::sequence<point>  ptr = {q};
			size_t id = pargeo::kdTree::batchKnn(ptr, 1, tree[idx])[0];
			if(ptrs[id].dist(q) < dist){
				dist = ptrs[id].dist(q);
				oid = id;
			}
		}
		return std::make_pair(oid, ptrs[oid]);
	}
};


int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(0);

	pargeo::timer queryT, updateT;

	pargeo::commandLine P(argc, argv, "-i{inFile}");
	char* iFile = P.getOptionValue("-i");

	parlay::sequence<pointD> ptrs = pargeo::pointIO::readPointsFromFile<pointD>(iFile);

	int n = ptrs.size();
	parlay::sequence<int> depPtr(n);

	parlay::stable_sort_inplace(ptrs, pointD::attComp);
	

	

}