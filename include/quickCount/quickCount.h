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

		void recurseCount(parlay::slice<pointT *, pointT *> points, paylay::slice<ballT *, ballT *> regions, pointT& pMin, pointT& pMax){
			intT k = findWidest();
			floatT xM = (pMax[k] + pMin[k]) / 2;
			// Split points by xM in dim k (parallel)
			sequence<bool> flags(points.size());
			parlay::parallel_for(0, points.size(),
								 [&](intT i)
									 {
										 if (points[i]->at(k) < xM)
											 flags[i] = 1;
										 else
											 flags[i] = 0;
									 });
			auto mySplit = kdTreeInternal::split_two(points, flags);
			auto splited = mySplit.first;
			intT median = mySplit.second;
			parlay::parallel_for(0, points.size(), [&](intT i)
												{ points[i] = splited[i]; }); // Copy back

			if (median == 0 || median == points.size())
			{
				median = (points.size() / 2.0);
			}

			pointT pMinL, pMaxL, pMinR, pMaxR;
			boundingBoxParallel(points.cut(0, median), pMinL, pMaxL);
			boundingBoxParallel(points.cut(median, points.size()), pMinR, pMaxR);

			// Now split the regions
			sequence<bool> region_flags(regions.size());
			parlay::parallel_for(0, regions.size(), [&](intT i){
				if(regions[i]->at(k) < xM){
					if(regions[i]->intersect(pMinR, pMaxR))
						region_flags[i] = 2;
					else
						region_flags[i] = 0;
				}else{
					if(regions[i]->intersect(pMinL, pMaxL))
						region_flags[i] = 2;
					else
						region_flags[i] = 1;
				}
			});




			// Recursive construction
			parlay::par_do(
				[&]()
					{ space[0] = nodeT(points.cut(0, median), median, space + 1, flags.cut(0, median), leafSize); },
				[&]()
					{ space[2 * median - 1] = nodeT(points.cut(median, size()), size() - median, space + 2 * median, flags.cut(median, size()), leafSize); });
			left = space;
			right = space + 2 * median - 1;
			left->sib = right;
			right->sib = left;
		}
	};

};
