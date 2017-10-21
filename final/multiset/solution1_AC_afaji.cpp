#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include <utility>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <stack>
#include <string>
#include <map>
#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#define ll long long
#define read(x) scanf("%d",&x);
#define readll(x) cin>>x;
#define FOR(x,a,b) for(int x=a;x<b;x++)
#define MP make_pair
#define PB push_back
#define pii pair<int,int>
#define readN(N,X) for(int i=0;i<N;i++) cin>>X[i];
#define pff pair<double,double>
using namespace std;
const int MAXN = 100000;
set<int> res;
int cnt[MAXN + 100];


void solve(){
	res.clear();
	memset(cnt, 0, sizeof(cnt));
	for (int i=1;i<=MAXN+5;i++) res.insert(i);
	int N;
	cin>>N;
	while(N--){
		int q;
		int K;
		cin>>q;
		if (q == 1){
			int l;
			cin>>l>>l>>K;
			if (l > MAXN) continue;
			cnt[l]++;
			if (cnt[l] == 1) res.erase(l);
		}
		if (q == 2){
			int l;
			cin>>l>>l>>K;
			if (l > MAXN) continue;
			if (cnt[l] == 1) res.insert(l);
			cnt[l] = max(cnt[l] - 1, 0);
		}
		cout<< *res.begin() <<endl;
	}
	
}

int main(){
	ios_base::sync_with_stdio(false);
	int T;
	cin>>T;
	while (T--) solve();
}