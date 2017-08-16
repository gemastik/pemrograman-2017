/*
* Greedy: soal pertama pasti untuk si author. kalo soalnya > 2, masing2 perusahaan dapet 1. 
* kalo soalnya 1, kasih ke perusahaan dengan kemunculan paling kecil di semua P
*/

#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstdio>
#include <iostream>
using namespace std;

int N;
int S[999];
int P[999][999];
int sumP[999];
int countP[999];
set<int> comp;

void solve() {
	cin>>N;
	comp.clear();
	for (int i=0;i<N;i++){
		cin>>S[i];
		S[i]--;
	}
	for (int i=0;i<N;i++){
		cin>>countP[i];
		for (int j=0;j<countP[i];j++) {
			cin>>P[i][j];
			sumP[P[i][j]]++;
		}
	}

	for (int i=0;i<N;i++){
		if (S[i]==0) continue;
		for (int j=0;j<countP[i];j++) {
			if (S[i] > 1) comp.insert(P[i][j]);
			if (comp.count(P[i][j])) continue;

			if (countP[i] == 1) comp.insert(P[i][j]);
			if (countP[i] == 2 && j == 0 && 
				sumP[P[i][0]] > sumP[P[i][1]])
				comp.insert(P[i][1]);
			else
				comp.insert(P[i][0]);
		}
	}
	cout<<N + comp.size()<<endl;
}

int main() {
	int T;
	cin>>T;
	while(T--) solve();
}