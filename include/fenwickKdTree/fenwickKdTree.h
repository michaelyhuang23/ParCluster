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
		const size_t bucket_size = 64;
		int n;
		parlay::sequence<point> ptrs;
		parlay::sequence<bool> is_bucket;
		parlay::sequence<pargeo::kdTree::node<dim, point>*> trees;
		parlay::sequence<parlay::slice<point*, point*>> buckets;
		static inline size_t lowbit(size_t num){ return num&(-num); }
		fenwickKdTree(parlay::sequence<point>& ptrs_) : n(ptrs_.size()), ptrs(ptrs_) {
			trees = parlay::sequence<pargeo::kdTree::node<dim, point>*>(n+1, NULL);
			buckets = parlay::sequence<parlay::slice<point*, point*>>(n+1);
			is_bucket = parlay::sequence<bool>(n+1, false);
			parlay::parallel_for(0, n+1, [&](size_t i){
				if(lowbit(i)<=bucket_size) {
					is_bucket[i]=true;
					buckets[i]=ptrs.cut(i-lowbit(i)+1-1, i+1-1);
				}
			});
	

			for(size_t i=0;(1<<i)<=n;i++){
				if((1<<i) > bucket_size){
					size_t topB = (n-(1<<i))>>(i+1);
					parlay::parallel_for(0, topB+1, [&](size_t idx){
						size_t ed = (idx<<(i+1))^(1<<i);
						if(is_bucket[ed]) std::cout<<"error"<<std::endl;
						size_t st = ed^(1<<i)+1-1;
						trees[ed] = pargeo::kdTree::build<dim, point>(ptrs.cut(st, ed+1-1), true, bucket_size);
					});	
				}
			}
		}
	
		std::pair<size_t, point> query(int idx, point& q){ // query range [0, idx] for item idx
			idx++;
			double dist = std::numeric_limits<double>::max()/2;
			point* op = NULL;
			for(; idx > 0; idx -= lowbit(idx)){
				if(is_bucket[idx]){
					for(size_t i=0;i<buckets[idx].size();i++){
						double radius = q.dist(buckets[idx][i]);
						if(radius < dist){
							dist = radius;
							op = &buckets[idx][i];
						}
					}
				}else{
					pargeo::kdTree::NearestNeighbor<dim, point>(q, trees[idx], dist, op);
				}
			}
			return std::make_pair(op-ptrs.data(), *op);
		}
	};

};
