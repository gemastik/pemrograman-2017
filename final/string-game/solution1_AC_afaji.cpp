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
int IDF = 1;
int dp[2000000];
int vis[2000000];
unordered_map<string, int> idf;

int grundy(string s){
	int h = idf[s];
	if (h == 0) {
			idf[s] = IDF;
			h = IDF;
			IDF++;
		}
	int X = s.length();

	if (vis[h]) return dp[h];
	vis[h] = 1;
	bool mex[50];
	memset(mex, 0, sizeof(mex));
	for (int i=0;i<X;i++){
		if (i + 1 == X || s[i] < s[i+1]){
			int poll = 'z' - s[i];
			if (i + 1 < X) poll = s[i + 1] - s[i];
			for (int j = 1; j <= poll; j++){
				s[i] += j;
				mex[grundy(s)] = 1;
				s[i] -= j;
			}
		}
	}
	//get mex
	int res = 0;
	for (int i=0;i<=32;i++){
		res=i;
		if (mex[i] == 0) {
			break;
		}
	}
	dp[h] = res;
	return res;
}

void solve(){
	int N,M;
	string S;
	cin>>N>>M;
	cin>>S;
	int res = 0;
	int g = grundy(S);
	//bruteforce
	for (int i=0;i<26;i++){
		for (int j=i;j<=26;j++){
			if (M < 2) j = 26;
			for (int k=j;k<=26;k++){
				if (M < 3) k = 26;
				for (int l=k;l<=26;l++){
					if (M < 4) l = 26;
					for (int m=l;m<=26;m++){
						if (M < 5) m = 26;
						for (int n=m;n<=26;n++){
							if (M < 6) n = 26;
							string wow = "";
							if (i < 26 && M >= 1) wow += ( 'a' + i);
							if (j < 26 && M >= 2) wow += ( 'a' + j);
							if (k < 26 && M >= 3) wow += ( 'a' + k);
							if (l < 26 && M >= 4) wow += ( 'a' + l);
							if (m < 26 && M >= 5) wow += ( 'a' + m);
							if (n < 26 && M >= 6) wow += ( 'a' + n);
							
							if (g ^ grundy(wow)) res++;
						}
					}
				}
			}
		}
	}

	cout<<res<<endl;
}

int main(){
	int T;
	cin>>T;
	while(T--) solve();
}