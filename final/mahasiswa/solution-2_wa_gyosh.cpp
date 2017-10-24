/*
Reason: not using int64, overflow
 */
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000001;

int T;
int N, K;

int ceilDiv(int a, int b) {
  return (a/b) + (a%b > 0 ? 1 : 0);
}

void solve() {
  scanf("%d %d", &N, &K);
  int sum = 0;
  int maks = 0;
  for (int i = 0; i < N; i++) {
    int m;
    scanf("%d", &m);

    sum += m;
    maks = max(maks, m);
  }

  printf("%d\n", max(maks, ceilDiv(sum, K)));
}

int main() {
  scanf("%d", &T);
  for (int jt = 0; jt < T; jt++) {
    solve();
  }
}
