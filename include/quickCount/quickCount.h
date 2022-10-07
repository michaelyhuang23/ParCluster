#pragma once

#include <algorithm>
#include <iostream>

#include "parlay/parallel.h"
#include "parlay/sequence.h"
#include "pargeo/point.h"
#include "pargeo/ball.h"

namespace pargeo {

	template <int dim, class _point, class _ball>
	struct quickCount{
		using pointT = _point;
		using ballT = _ball;
		using intT = int;

		inline void minCoords(pointT &_pMin, pointT &p){
			for (int i = 0; i < dim; ++i)
				_pMin[i] = std::min(_pMin[i], p[i]);
		}

		inline void maxCoords(pointT &_pMax, pointT &p){
			for (int i = 0; i < dim; ++i)
				_pMax[i] = std::max(_pMax[i], p[i]);
		}

		void boundingBoxParallel(parlay::slice<pointT *, pointT *> items, pointT& pMin, pointT& pMax){
			intT P = parlay::num_workers() * 8;
			intT blockSize = (items.size() + P - 1) / P;
			pointT localMin[P];
			pointT localMax[P];
			for (intT i = 0; i < P; ++i)
			{
				localMin[i] = pointT(items[0]->coords());
				localMax[i] = pointT(items[0]->coords());
			}
			parlay::parallel_for(0, P,
								 [&](intT p)
									 {
										 intT s = p * blockSize;
										 intT e = std::min((intT)(p + 1) * blockSize, size());
										 for (intT j = s; j < e; ++j)
										 {
											 minCoords(localMin[p], items[j][0]);
											 maxCoords(localMax[p], items[j][0]);
										 }
									 });
			pMin = pointT(items[0]->coords());
			pMax = pointT(items[0]->coords());
			for (intT p = 0; p < P; ++p)
			{
				minCoords(pMin, localMin[p]);
				maxCoords(pMax, localMax[p]);
			}

		}

		template <typename In_Seq, typename Bool_Seq>
		auto split_two(In_Seq const &In,
					   Bool_Seq const &Fl,
					   parlay::flags fl = parlay::no_flag)
			-> std::pair<parlay::sequence<typename In_Seq::value_type>, size_t>
		{

			using namespace parlay;
			using namespace parlay::internal;

			using T = typename In_Seq::value_type;
			size_t n = In.size();
			size_t l = num_blocks(n, _block_size);
			sequence<size_t> Sums(l);
			sliced_for(
				n, _block_size,
				[&](size_t i, size_t s, size_t e)
					{
						size_t c = 0;
						for (size_t j = s; j < e; j++)
							c += (Fl[j] == false);
						Sums[i] = c;
					},
				fl);
			size_t m = scan_inplace(make_slice(Sums), addm<size_t>());
			sequence<T> Out = sequence<T>::uninitialized(n);
			sliced_for(
				n, _block_size,
				[&](size_t i, size_t s, size_t e)
					{
						size_t c0 = Sums[i];
						size_t c1 = s + (m - c0);
						for (size_t j = s; j < e; j++)
						{
							if (Fl[j] == false)
								assign_uninitialized(Out[c0++], In[j]);
							else
								assign_uninitialized(Out[c1++], In[j]);
						}
					},
				fl);
			return std::make_pair(std::move(Out), m);
		}

		template <typename In_Seq, typename Type_Seq>
		auto split_three(In_Seq const &In,
					   Type_Seq const &Fl,
					   parlay::flags fl = parlay::no_flag)
			-> std::tuple<parlay::sequence<typename In_Seq::value_type>, size_t, size_t>
		{

			using namespace parlay;
			using namespace parlay::internal;

			using T = typename In_Seq::value_type;
			size_t n = In.size();
			size_t l = num_blocks(n, _block_size);
			sequence<size_t> SumsC(l), SumsC2(l);
			sliced_for(
				n, _block_size,
				[&](size_t i, size_t s, size_t e)
					{
						size_t c = 0, c1 = 0;
						for (size_t j = s; j < e; j++){
							c += (Fl[j] == 0);
							c1 += (Fl[j] == 0 || Fl[j] == 1); // is left or mid
						}
						SumsC[i] = c;
						SumsC1[i] = c1;
					},
				fl);
			size_t m = scan_inplace(make_slice(SumsC), addm<size_t>());
			size_t m1 = scan_inplace(make_slice(SumsC1), addm<size_t>());
			sequence<T> Out = sequence<T>::uninitialized(n);
			sliced_for(
				n, _block_size,
				[&](size_t i, size_t s, size_t e)
					{
						size_t c0 = SumsC[i];
						size_t c1 = SumsC1[i] - SumsC[i] + m;
						size_t c2 = s - SumC1[i] + m1;
						for (size_t j = s; j < e; j++)
						{
							if (Fl[j] == 0)
								assign_uninitialized(Out[c0++], In[j]);
							else if (Fl[j] == 1)
								assign_uninitialized(Out[c1++], In[j]);
							else 
								assign_uninitialized(Out[c2++], In[j]);
						}
					},
				fl);
			return std::make_tuple(std::move(Out), m, m1);
		}

		void recurseCount(parlay::slice<pointT *, pointT *> points, paylay::slice<ballT *, ballT *> regions, pointT& pMin, pointT& pMax, intT cutoff=16){

			if(regions.size() * points.size() < cutoff){
				for(intT i=0;i<regions.size();++i)
					for(intT j=0;j<points.size();++j)
						if(regions[i].contains_point(points[j])) regions[i].count++;
			}

			intT k = findWidest();
			floatT xM = (pMax[k] + pMin[k]) / 2;
			// Split points by xM in dim k (parallel)
			sequence<bool> flags(points.size());
			parlay::parallel_for(0, points.size(),
								 [&](intT i)
									 {
					ballT					 if (points[i]->at(k) < xM)
											 flags[i] = 1;
										 else
											 flags[i] = 0;
									 });
			auto pointSplit = split_two(points, flags);
			sequence<pointT *> splitedPoints = pointSplit.first;
			intT median = pointSplit.second; // no need to copy back


			if (median == 0 || median == points.size()) // consider getting rid of this
			{
				median = (points.size() / 2.0);
			}

			pointT pMinL, pMaxL, pMinR, pMaxR;
			boundingBoxParallel(points.cut(0, median), pMinL, pMaxL);
			boundingBoxParallel(points.cut(median, points.size()), pMinR, pMaxR);

			// Now split the regions
			sequence<intT> region_flags(regions.size());
			parlay::parallel_for(0, regions.size(), [&](intT i){
				if(flags[i] == 1){ // to the left
					if(regions[i]->intersect_rect(pMinR, pMaxR))
						region_flags[i] = 1;
					else
						region_flags[i] = 0;
				}else{
					if(regions[i]->intersect_rect(pMinL, pMaxL))
						region_flags[i] = 1;
					else
						region_flags[i] = 2;
				}
			});
			auto regionSplit = split_three(regions, region_flags);
			sequence<ballT *> splitedRegions = get<0>(regionSplit);
			intT region_median = get<1>(regionSplit);
			intT region_median1 = get<2>(regionSplit);

			// Recursive construction
			parlay::par_do(
				[&](){ 
					recurseCount(splitedPoints.cut(0, median), splitedRegions.cut(0, region_median1), pMinL, pMaxL, cutoff);
				},
				[&](){
					recurseCount(splitedPoints.cut(median, splitedPoints.size()), splitedRegions.cut(region_median, splitedRegions.size()), pMinR, pMaxR, cutoff);
				});
		}
	};

};
