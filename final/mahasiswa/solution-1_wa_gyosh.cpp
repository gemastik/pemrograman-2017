/*
Reason: forgot that N can be 1
 */
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000001;

typedef long long ll;

int T;
int N, K;
ll M[MAXN];

void solve() {
  scanf("%d %d", &N, &K);
  for (int i = 0; i < N; i++) {
    scanf("%lld", &M[i]);
  }

  if (K == 1) {
    printf("%lld\n", M[0]+M[1]);
  } else if (K == 2) {
    printf("%lld\n", max(M[0], M[1]));
  }
}

int main() {
  scanf("%d", &T);
  for (int jt = 0; jt < T; jt++) {
    solve();
  }
}
