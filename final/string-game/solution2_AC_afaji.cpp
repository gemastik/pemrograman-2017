/*
TLE karena DP-nya nggak global
*/
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
int MOD = 1000000007;
const int MAXM = 10000;
int N, M;
string S;
int dp[2][32][26];
int total_ways[MAXM + 1][35];

vector<vector<long long>> matmul(vector<vector<long long>> m1, vector<vector<long long>> m2){
    int A = m1.size();
    int B = m2.size();
    int C = m2[0].size();
    vector<vector<long long>> res;
    res.resize(A, vector<long long>(C,0));

    for (int i=0;i<A;i++)
        for (int j=0;j<C;j++)
            for (int k=0;k<B;k++){
                res[i][j] = (res[i][j] + m1[i][k] * m2[k][j]) % MOD;
            }
    return res;
}

vector<vector<long long>> matpow(vector<vector<long long>> m, int P) {
    int dim = m.size();
    vector<vector<long long>> res;
    res.resize(dim, vector<long long>(dim,0));

    for (int i=0;i<dim;i++) res[i][i] = 1;
    if (P == 0) return res;
    if (P == 1) return m;
    vector<vector<long long>> half = matpow(m , P/2);
    half = matmul(half, half);
    if (P % 2) half = matmul(half, m);
    return half;
}

int grundy(string s){
    s += 'z';
    int res = 0;
    for (int i=0;i<s.size() - 1;i+=2)
        res ^= (s[i+1] - s[i]);
    return res;
}

void precomp(){
    M = MAXM;
    dp[0][0][0] = 1;
    // MEGA OPTIMIZE
    for (register int ii=1;ii<=M;++ii){
        int i = ii % 2;
        if (ii % 2) {
            for (int mask=0;mask <= 31; ++mask)
                for (int j=0;j<26;++j){
                    dp[i][mask][j] = 0;
                    for (int k=0;k<=j;++k){
                        dp[i][mask][j] = (dp[i][mask][j] + dp[i^1][mask ^ k][j - k]) % MOD;
                    }
                    total_ways[ii][mask] = (total_ways[ii][mask] + dp[i][mask][j]) % MOD;
                }
        } else {
            for (int mask=0;mask <= 31; ++mask){
                int kagi = 0;
                for (int j=0;j<26;++j){
                    kagi = (kagi + dp[i^1][mask][j]) % MOD;
                    dp[i][mask][j] = kagi;
                    total_ways[ii][mask] = (total_ways[ii][mask] + dp[i][mask][j]) % MOD;
                }
            }
        }
    }
    for (int mask=0; mask <= 31; mask++)
        for (int i=1;i<=M;i++)
            (total_ways[i][mask] += total_ways[i-1][mask]) %= MOD;
}

void solve(){
    cin>>N>>M;
    cin>>S;

    vector<vector<long long>> mat;
    mat.resize(32, vector<long long>(32,0));
    for (int i=0;i<32;i++)
        for (int j=0;j<32;j++)
            mat[i][j] = total_ways[M][i ^ j];

    mat = matpow(mat, N - 1);

    int res = 0;
    for (int i=0;i<32;i++)
        res = (res + mat[0][i]) % MOD;
    res = (res + MOD - mat[0][grundy(S)]) % MOD;
    cout<<res<<endl;
}

int main(){
    std::ios::sync_with_stdio(false);
    int T;
    cin>>T;
    precomp();
    while(T--) solve();
}
