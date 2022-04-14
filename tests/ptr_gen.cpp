#include<bits/stdc++.h>

using namespace std;

double dRand(double fMin, double fMax){
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

int main(int argc, char** argv){
	srand(atoi(argv[1]));
	int n = 4;
	double RANGE = 4;
	for(int i=0;i<n;i++){
		cout<<dRand(-RANGE, RANGE)<<" "<<dRand(-RANGE, RANGE)<<endl;
	}
}
