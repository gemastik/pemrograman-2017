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

unordered_map<int, int> dp;
unordered_map<int, int> vis;

int grundy(string s){
	int h = 0;
	int X = s.length();
	for (int i=0;i<X;i++)
	if (vis[s]) return dp[s];
	vis[s] = 1;

	vector<int> l;

	for (int i=0;i<X;i++){
		if (i + 1 == s.length() || s[i] < s[i+1]){
			int poll = 'z' - s[i];
			if (i + 1 < s.length()) poll = s[i + 1] - s[i];
			for (int j = 1; j <= poll; j++){
				s[i] += j;
				l.push_back(grundy(s));
				s[i] -= j;
			}
		}
	}
	//get mex
	int res = 0;
	sort(l.begin(), l.end());
	for (int i:l){
		if (i == res) res++;
	}
	dp[s] = res;
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