/*
*
* 2ˆ10, AC 
* in case 1 <= S[i] <= 50, tetep AC
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
int countP[999];
int comp[999];
int compsize;

int hajar(int pos) {
	if (pos >= 2*N){
		return compsize;
	}
	int idx = pos/2;
	if (S[idx] == 0 || countP[idx] == 0)
		return hajar(pos+1);
	if (pos % 2 == 1 && S[idx] < 2)
		return hajar(pos+1);

	int res = 0;
	for (int i=0;i<countP[idx];i++){
		comp[P[idx][i]]++; compsize += (comp[P[idx][i]] == 1);
		res = max(res, hajar(pos+1));
		comp[P[idx][i]]--; compsize -= (comp[P[idx][i]] == 0);
	}
	return res;
}

void solve() {
	cin>>N;
	compsize=0;
	for (int i=0;i<N;i++){
		cin>>S[i];
		S[i]--;
		if (S[i] > 2) S[i] = 2;
	}
	for (int i=0;i<N;i++){
		cin>>countP[i];
		for (int j=0;j<countP[i];j++) cin>>P[i][j];
	}

	cout<<hajar(0) + N<<endl;
}

int main() {
	int T;
	cin>>T;
	while(T--) solve();
}