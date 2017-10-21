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
#include <unordered_map>
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
const int MAXN = 150003;
const int SQRSIZE = 390;

ll arr[MAXN + 1];
ll block[SQRSIZE];
ll nett[SQRSIZE];
ll drop[SQRSIZE];
ll lowest[SQRSIZE];

unordered_map<int,int> revid;
void init(){
	memset(arr, 0, sizeof(arr));
	memset(block, 0, sizeof(block));
	memset(nett, 0, sizeof(nett));
	memset(drop, 0, sizeof(drop));
	memset(lowest, 0, sizeof(lowest));

}

inline void updateLowest(int idx){
	lowest[idx] = 99999999;
	for (int i=0;i<SQRSIZE;i++)
		lowest[idx] = min(lowest[idx], arr[idx * SQRSIZE + i]);
}
inline ll maks(ll a, ll b){
	if (a > b) return a;
	return b;
}
inline void updateBlock(int idx){
	for (int i=0;i<SQRSIZE;i++){
		arr[idx * SQRSIZE + i] = maks(maks(arr[idx * SQRSIZE + i] + drop[idx], 0) - drop[idx] + nett[idx], 0);
	}
	nett[idx] = 0;
	drop[idx] = 0;
	updateLowest(idx);
}

inline int query(){
	for (int i=0;i<SQRSIZE;i++){
		int low = maks(lowest[i] + drop[i], 0) - drop[i] + nett[i];
		if (low > 0) continue;

		updateBlock(i);
		for (int j=0;j<SQRSIZE;j++){
			if (arr[i * SQRSIZE + j] == 0) return i * SQRSIZE + j;
		}
	}
	return -1;
}

inline void update(int l, int r, int v){
	int front_ID = l/SQRSIZE;
	int back_ID = r/SQRSIZE;
	updateBlock(front_ID);
	if (front_ID != back_ID) updateBlock(back_ID);
	while (l < r && l % SQRSIZE != 0 && l != 0) {
    	arr[l] = maks(arr[l] + v, 0);
    	l++;
    }
    while (l + SQRSIZE <= r){
    	int idx = l / SQRSIZE;
        nett[idx] += v;
        drop[idx] = min(drop[idx], nett[idx]);
        l += SQRSIZE;
    }
    while (l<=r) {
		arr[l] = maks(arr[l] + v, 0);
    	l++;
    }
    updateLowest(front_ID);
    if (front_ID != back_ID) updateLowest(back_ID);
}

int Q[100005], L[100005], R[100005], K[100005];
set<int> ids;
int backid[150005];
inline void solve(){
	int N;
	cin>>N;
	init();
	ids.insert(1);
	for (int i=0;i<N;i++) {
		cin>>Q[i]>>L[i]>>R[i]>>K[i];
		ids.insert(L[i]);
		ids.insert(R[i]);
		ids.insert(R[i] + 1);
	}
	int MN = 0;
	for (int i: ids){
		revid[i] = MN;
		backid[MN++] = i;
	}
	for (int i=0;i<N;i++){
		int q = Q[i];
		int l,r, k;
		l = revid[L[i]];
		r = revid[R[i]];
		k = K[i];
		if (q == 1) { //add
			update(l,r, k);
		}
		if (q == 2) { //remove
			update(l,r,-k);
		}
		cout<<backid[query()]<<endl;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	int T;
	cin>>T;
	while (T--) solve();
}