/*
 * (c) fushar (Ashar Fuadi)
 *
 * Reason for WA: Array-nya kurang besar 1 indeks
*/

#include <bits/stdc++.h>

#define REP(i,n) for (int i = 0, _n = n; i < _n; i++)
#define FOR(i,a,b) for (int i = a, _b = b; i <= _b; i++)

using namespace std;

/***********************************************************/

const int MAXM = 3, MAXK = 26, MAXN = 50, MOD = 1000000007;

int T;
char S[MAXM];
pair<int, int> P;
int N, K;

int dp[MAXN][MAXK][MAXK][2];

int doDP() {
    dp[0][0][0][0] = 1;
    REP(i, N) REP(a, K) REP(b, K) REP(done, 2) REP(c, K) REP(d, K) {
        int ndone = done;
        ndone |= (P == make_pair(c, d));
        ndone |= (P == make_pair(d, c));
        if (i) ndone |= (P == make_pair(a, c));
        if (i) ndone |= (P == make_pair(a, d));
        if (i) ndone |= (P == make_pair(b, c));
        if (i) ndone |= (P == make_pair(b, d));
        dp[i+1][c][d][ndone] += dp[i][a][b][done];
        dp[i+1][c][d][ndone] %= MOD;
    }
    int res = 0;
    REP(a, K) REP(b, K) res = (res + dp[N][a][b][1]) % MOD;
    return res;
}

int main() {
    scanf("%d", &T);
    REP(tc, T) {
        scanf("%s %d %d", S, &N, &K);
        P = make_pair(S[0]-'a', S[1]-'a');
        printf("%d\n", doDP());
    }
}
