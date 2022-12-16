#pragma once

#include <algorithm>
#include <iostream>

#include "parlay/parallel.h"
#include "parlay/sequence.h"
#include "pargeo/atomics.h"
#include "pargeo/point.h"
#include "pargeo/ball.h"

namespace pargeo {

	template <int dim, class _point, class _ball>
	struct divRangeTree{
		using pointT = _point;
		using ballT = _ball;
		using intT = int;

		void recurseCount(parlay::slice<pointT **, pointT **> points, parlay::slice<ballT **, ballT **> regions, intT idim){
			pointT pMin, pMax;
			boundingBoxSerial(points, pMin, pMax);

			parlay::sequence<ballT *> filtered_regions(regions.size());
			parlay::sequence<intT> idmap(regions.size());
			int fi = 0;
			for(size_t i=0;i<regions.size();++i){
				int relation = regions[i]->compareBox(pMin, pMax);
				if(relation == 0){ // include
					regions[i]->count_increase(points.size());
				}else if(relation == 1){ // overlap
					idmap[fi] = i;
					filtered_regions[fi++] = regions[i];
				}
			}
			intT filtered_length = fi;


	}
	};

};
