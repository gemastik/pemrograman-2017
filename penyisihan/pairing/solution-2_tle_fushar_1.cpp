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

        priority_queue<tuple<ll, int, int>> pq;
        pq.push(make_tuple(-init, 0, 0));

        set<pair<int, int>> seen;
        seen.insert(make_pair(0, 0));

        while (!pq.empty()) {
            ll prod; int a, b;
            tie(prod, a, b) = pq.top(); pq.pop();
            prod *= -1;

            if (prod - init > 1000000) break;

            ans = min(ans, prod + C[prod % M]);

            if (a+1 < nA && !seen.count(make_pair(a+1, b))) {
                pq.push(make_tuple(-1ll * A[a+1] * B[b], a+1, b));
                seen.insert(make_pair(a+1, b));
            }
            if (b+1 < nB && !seen.count(make_pair(a, b+1))) {
                pq.push(make_tuple(-1ll * A[a] * B[b+1], a, b+1));
                seen.insert(make_pair(a, b+1));
            }
        }

        printf("%lld\n", ans);
    }
}
