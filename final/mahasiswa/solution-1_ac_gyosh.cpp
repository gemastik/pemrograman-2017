#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000001;

typedef long long ll;

int T;
int N, K;

void solve() {
  scanf("%d %d", &N, &K);
  ll sum = 0;
  ll maks = 0;
  for (int i = 0; i < N; i++) {
    ll m;
    scanf("%lld", &m);

    sum += m;
    maks = max(maks, m);
  }

  if (K == 1) {
    printf("%lld\n", sum);
  } else if (K == 2) {
    printf("%lld\n", maks);
  }
}

int main() {
  scanf("%d", &T);
  for (int jt = 0; jt < T; jt++) {
    solve();
  }
}
