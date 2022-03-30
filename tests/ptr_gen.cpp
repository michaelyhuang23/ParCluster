#include<bits/stdc++.h>

using namespace std;

double dRand(double fMin, double fMax){
	double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main(int argc, char** argv){
	srand(atoi(argv[1]));
	int n = 10000000, d = 2;
	double RANGE = 1000000;
	double dRANGE = 5000;
	for(int i=0;i<n;i++){
		cout<<dRand(-RANGE, RANGE)<<" "<<dRand(-RANGE, RANGE)<<endl;
	}
}