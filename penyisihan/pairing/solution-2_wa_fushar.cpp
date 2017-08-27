/*
 * (c) fushar (Ashar Fuadi)
 *
 * Reason for WA: using dynamic double weighted MARSHAL
*/

#include <bits/stdc++.h>

#define REP(i,n) for (int i = 0, _n = n; i < _n; i++)
#define FOR(i,a,b) for (int i = a, _b = b; i <= _b; i++)

using namespace std;
using ll = long long;

/***********************************************************/

const int MAXN = 100005, MAXM = 100005;
const int MARSHAL = 2005;

int T;
int N, M;
int A[MAXN], B[MAXN], C[MAXM];
int nA, nB;

long long ans;

void solve(int X[], int nX, int Y[], int nY) {
    int lX = min(MARSHAL, nX);
    REP(i, lX) {
        REP(k, MARSHAL) {
            int j = rand() % (rand() % nY + 1);
            ll prod = 1ll * X[i] * Y[j];
            ans = min(ans, prod + C[prod % M]);
        }
    }
}

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

        ans = (ll) 1e12;

        solve(A, nA, B, nB);
        solve(B, nB, A, nA);

        printf("%lld\n", ans);
    }
}
