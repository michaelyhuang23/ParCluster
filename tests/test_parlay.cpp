#include <iostream>
#include <algorithm>
#include <fstream>
#include "parlay/parallel.h"
#include "parlay/sequence.h"
#include "parlay/primitives.h"
#include "pargeo/parseCommandLine.h"
#include "pargeo/pointIO.h"
#include "pargeo/point.h"

using namespace std;




int main(int argc, char* argv[]) {

	pargeo::commandLine P(argc, argv, "<inFile>");
	char* iFile = P.getArgument(0);

	using point = pargeo::point<2>;
	parlay::sequence<point> ptrs = pargeo::pointIO::readPointsFromFile<point>(iFile);

	cout<<"original points:"<<endl;
	// for(int i=0;i<ptrs.size();i++)
	// 	cout<<ptrs[i][0]<<" "<<ptrs[i][1]<<" "<<ptrs[i].density()<<endl;

	ptrs = parlay::sort(ptrs);

	cout<<"\nsorted points:"<<endl;
	// for(int i=0;i<ptrs.size();i++)
	// 	cout<<ptrs[i][0]<<" "<<ptrs[i][1]<<" "<<ptrs[i].density()<<endl;

}
