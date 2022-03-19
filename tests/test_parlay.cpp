#include <iostream>
#include <algorithm>
#include <fstream>
#include "parlay/parallel.h"
#include "parlay/sequence.h"
#include "parlay/primitives.h"
#include "pargeo/parseCommandLine.h"
#include "pargeo/pointIO.h"

using namespace std;

template<int _dim> class pointD { // point with density
	// Internal declarations
	typedef int intT;
	typedef double floatT;
	typedef pointD pointT;
	static constexpr double empty = std::numeric_limits<double>::max();

public:

	static const int dim = _dim;
	static const int dimsize = _dim+1;

	// Data field

	floatT x[_dim];
	floatT d;

	// Constructors
	pointD():d(empty){ for (int i=0; i<_dim; ++i) x[i]=empty; }
	pointD(floatT* p, floatT d_):d(d_){ for (int i=0; i<_dim; ++i) x[i]=p[i]; }
	pointD(pointT* p, floatT d_):d(d_){ for (int i=0; i<_dim; ++i) x[i]=p->x[i]; }
	pointD(parlay::slice<floatT*,floatT*> p, floatT d_):d(d_){
		for(int i=0; i<_dim; ++i) x[i] = p[i];
	}

	// Primitives
	int dimension() {return _dim;}
	void setEmpty() {x[0]=empty;}
	bool isEmpty() {return x[0]==empty;}

	pointT operator+(pointT op2) {
	floatT xx[_dim];
	for (int i=0; i<_dim; ++i) xx[i] = x[i]+op2.x[i];
	return pointT(xx);}

	pointT operator-(pointT op2) {
	floatT xx[_dim];
	for (int i=0; i<_dim; ++i) xx[i] = x[i]-op2.x[i];
	return pointT(xx);}

	pointT operator/(floatT dv) {
	floatT xx[_dim];
	for (int i=0; i<_dim; ++i) xx[i] = x[i]/dv;
	return pointT(xx);}

	pointT operator*(floatT dv) {
	floatT xx[_dim];
	for (int i=0; i<_dim; ++i) xx[i] = x[i]*dv;
	return pointT(xx);}

	floatT& operator[](int i) {return x[i];}

	friend bool operator==(pointT a, pointT b) {
	for (intT ii=0; ii<dim; ++ii) {
	  if (abs(a[ii]-b[ii]) > 0.0) return false;}
	return true;}

	friend bool operator<(pointT a, pointT b) { return a.d < b.d; }

	friend bool operator>(pointT a, pointT b) { return a.d > b.d; }

	friend bool operator!=(pointT a, pointT b) {return !(a==b);}

	floatT* coordinate() {return x;}

	floatT coordinate(int i) {return x[i];}

	floatT density() {return d;}


	inline floatT dist(pointT p) {
	floatT xx=0;
	for (int i=0; i<_dim; ++i) xx += (x[i]-p.x[i])*(x[i]-p.x[i]);
	return sqrt(xx);}

	inline floatT distSqr(pointT p) {
	floatT xx=0;
	for (int i=0; i<_dim; ++i) xx += (x[i]-p.x[i])*(x[i]-p.x[i]);
	return xx;}

	floatT dot(pointT p2) {
	floatT r = 0;
	for(int i=0; i<dim; ++i) r += x[i]*p2[i];
	return r;}

	pointT normalize() {
	auto r = pointT(x);
	floatT s = 0;
	for (int i=0; i<dim; ++i) s += x[i]*x[i];
	s = sqrt(s);
	for (int i=0; i<dim; ++i) r[i] /= s;
	return r;}

	floatT length() {
	floatT xx=0;
	for (int i=0; i<_dim; ++i) xx += x[i]*x[i];
	return sqrt(xx);}

	floatT lenSqr() {
	floatT xx=0;
	for (int i=0; i<_dim; ++i) xx += x[i]*x[i];
	return xx;}
};


int main(int argc, char* argv[]) {

	pargeo::commandLine P(argc, argv, "<inFile>");
	char* iFile = P.getArgument(0);

	using point = pointD<2>;
	parlay::sequence<point> ptrs = pargeo::pointIO::readPointsFromFile<point>(iFile);

	cout<<"original points:"<<endl;
	// for(int i=0;i<ptrs.size();i++)
	// 	cout<<ptrs[i][0]<<" "<<ptrs[i][1]<<" "<<ptrs[i].density()<<endl;

	ptrs = parlay::sort(ptrs);

	cout<<"\nsorted points:"<<endl;
	// for(int i=0;i<ptrs.size();i++)
	// 	cout<<ptrs[i][0]<<" "<<ptrs[i][1]<<" "<<ptrs[i].density()<<endl;

}
