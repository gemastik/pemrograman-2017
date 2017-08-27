/*
 * (c) fushar (Ashar Fuadi)
*/

#include <bits/stdc++.h>

#define REP(i,n) for (int i = 0, _n = n; i < _n; i++)
#define FOR(i,a,b) for (int i = a, _b = b; i <= _b; i++)

using namespace std;
using ll = long long;

/***********************************************************/

const int MAXM = 100005, oo = 10000000;

int T;
int N, M;
int A[MAXM], B[MAXM], C[MAXM];

int main() {
    srand(12345);

    scanf("%d", &T);
    REP(tc, T) {
        scanf("%d %d", &N, &M);
        REP(i, M) A[i] = B[i] = oo;
        REP(i, N) {
            int x;
            scanf("%d", &x);
            A[x%M] = min(A[x%M], x);
        }
        REP(i, N) {
            int x;
            scanf("%d", &x);
            B[x%M] = min(B[x%M], x);
        }
        REP(i, M) scanf("%d", &C[i]);

        ll ans = (ll) 1e13;
        REP(i, M) REP(j, M) {
            if (A[i] != oo && B[j] != oo) {
                ll prod = 1ll * A[i] * B[j];
                ans = min(ans, prod + C[prod%M]);
            }
        }

        printf("%lld\n", ans);
    }
}
