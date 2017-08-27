/*
 * (c) fushar (Ashar Fuadi)
*/

#include <bits/stdc++.h>

#define REP(i,n) for (int i = 0, _n = n; i < _n; i++)
#define FOR(i,a,b) for (int i = a, _b = b; i <= _b; i++)

using namespace std;
using ll = long long;

/***********************************************************/

const int MAXN = 100005, MAXM = 100005;

int T;
int N, M;
int A[MAXN], B[MAXN], C[MAXM];
int nA, nB;

int main() {
    srand(12345);

    scanf("%d", &T);
    REP(tc, T) {
        scanf("%d %d", &N, &M);
        REP(i, N) scanf("%d", &A[i]);
        sort(A, A+N);
        nA = unique(A, A+N) - A;

        REP(i, N) scanf("%d", &B[i]);
        sort(B, B+N);
        nB = unique(B, B+N) - B;

        REP(i, M) scanf("%d", &C[i]);

        ll ans = (ll) 1e13;
        ll init = 1ll * A[0] * B[0];

        REP(i, nA) {
            REP(j, nB) {
                ll prod = 1ll * A[i] * B[j];
                if (prod - init > 1000000) break;
                ans = min(ans, prod + C[prod % M]);
            }
        }

        printf("%lld\n", ans);
    }
}
