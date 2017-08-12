/*
  reason for TLE: worst operation is 100.000 * 1000
 */
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int INF = 2123123123;
const LL INFLL = 2123123123LL * 2123123123LL;

int T;
int N, M;
int A[100005];
int B[100005];
int C[1005];

int minB[1005];

void solve() {
  scanf("%d %d", &N, &M);

  for (int i = 0; i < N; i++) {
    scanf("%d", &A[i]);
  }
  for (int i = 0; i < N; i++) {
    scanf("%d", &B[i]);
  }
  for (int i = 0; i < M; i++) {
    scanf("%d", &C[i]);
  }


  for (int i = 0; i < N; i++) {
    minB[i] = INF;
  }
  for (int i = 0; i < N; i++) {
    int x = B[i] % M;
    minB[x] = min(minB[x], B[i]);
  }


  LL answer = INF;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (minB[j] != INF) {
        int y = ((LL)A[i]*minB[j]) % M;
        answer = min(answer, (LL)A[i]*minB[j] + C[y]);
      }
    }
  }

  printf("%lld\n", answer);
}

int main() {
  scanf("%d", &T);
  for (int jt = 0; jt < T; jt++) {
    solve();
  }
}
