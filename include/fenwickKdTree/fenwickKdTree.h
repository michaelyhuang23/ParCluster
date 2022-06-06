#pragma once

#include <algorithm>
#include <iostream>

#include "parlay/parallel.h"
#include "parlay/sequence.h"
#include "pargeo/point.h"
#include "kdTree/kdTree.h"

namespace pargeo {

	template <int dim>
	struct fenwickKdTree{
		using point = pargeo::point<dim>;
		using pointD = pargeo::pointD<dim, int>;
		int n;
		int qc;
		parlay::sequence<point> ptrs;
		parlay::sequence<pargeo::kdTree::node<dim, point>*> trees;
		static inline size_t lowbit(size_t num){ return num&(-num); }
		fenwickKdTree(parlay::sequence<point>& ptrs_) : n(ptrs_.size()), ptrs(ptrs_) {
			qc = 0;
			trees = parlay::sequence<pargeo::kdTree::node<dim, point>*>(n+1);
			parlay::parallel_for(1, n+1,
								 [&](size_t i){
									 size_t st = i-lowbit(i)+1-1;
									 trees[i] = pargeo::kdTree::build<dim, point>(ptrs.cut(st, i+1-1), true, 16);});
		}
	
		std::pair<size_t, point> query(int idx, point& q){ // query range [0, idx] for item idx
			idx++;
			double dist = std::numeric_limits<double>::max()/2;
			point* op = NULL;
			for(; idx > 0; idx -= lowbit(idx)){
				pargeo::kdTree::NearestNeighbor<dim, point>(q, trees[idx], dist, op);
				qc++;
			}
			return std::make_pair(op-ptrs.data(), *op);
		}
	};

};
