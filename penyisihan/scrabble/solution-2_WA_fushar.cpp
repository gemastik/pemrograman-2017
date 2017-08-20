/*
 * (c) fushar (Ashar Fuadi)
 *
 * Reason for WA: lupa di-mod
*/

#include <bits/stdc++.h>

#define REP(i,n) for (int i = 0, _n = n; i < _n; i++)
#define FOR(i,a,b) for (int i = a, _b = b; i <= _b; i++)

using namespace std;

/***********************************************************/

const int MAXM = 11, MAXK = 26, MAXN = 51;

int T;
char S[MAXM];
int N, M, K;

int prevState[MAXM], nextState[MAXM][MAXK];

void doKmp() {
    int q = 0;
    prevState[0] = -1;
    prevState[1] = 0;
    FOR(i, 2, M) {
        while (q && S[q+1] != S[i]) q = prevState[q];
        if (S[q+1] == S[i]) q++;
        prevState[i] = q;
    }

    REP(i, M) REP(c, K) {
        int q = i;
        while (q && S[q+1] != 'a'+c) q = prevState[q];
        if (S[q+1] == 'a'+c) q++;
        nextState[i][c] = q;
    }
    REP(c, K) nextState[M][c] = M;
}

int nextMask[1<<MAXM][MAXK][MAXK];

void precomputeTransitions() {
    REP(mask, 1<<(M+1)) REP(a, K) REP(b, K) {
        int nmask = 0;
        REP(s, M+1) if (mask & (1<<s)) {
            nmask |= 1 << nextState[s][a];
            nmask |= 1 << nextState[s][b];
            nmask |= 1 << nextState[nextState[s][a]][b];
            nmask |= 1 << nextState[nextState[s][b]][a];
        }
        nextMask[mask][a][b] = nmask;
    }
}

int dp[MAXN][1<<MAXM];

int doDP() {
    dp[0][1] = 1;
    REP(i, N) REP(mask, 1<<(M+1)) REP(a, K) REP(b, K) {
        int nmask = nextMask[mask][a][b];
        dp[i+1][nmask] += dp[i][mask];
    }
    int res = 0;
    REP(mask, 1<<(M+1)) if (mask & (1<<M)) res = (res + dp[N][mask]);
    return res;
}

int main() {
    scanf("%d", &T);
    REP(tc, T) {
        scanf("%s %d %d", S+1, &N, &K);
        M = strlen(S+1);
        doKmp();
        precomputeTransitions();
        printf("%d\n", doDP());
    }
}
