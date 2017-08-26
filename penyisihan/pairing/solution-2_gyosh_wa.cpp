/*
  reason for WA: is using "konstanta marshal"
 */
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int INF = 2123123123;
const LL INFLL = 2123123123LL * 2123123123LL;
const int MARSHAL = 2500;

int T;
int N, M;
int A[100005];
int B[100005];
int C[100005];

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

  sort(A, A + N);
  int sizeA = unique(A, A + N);

  sort(B, B + N);
  int sizeB = unique(B, B + N);

  LL answer = INFLL;
  for (int i = 0; i < min(sizeA, MARSHAL); i++) {
    for (int j = 0; j < min(sizeB, MARSHAL); j++) {
      int y = ((LL)A[i]*B[j]) % M;
      answer = min(answer, (LL)A[i]*B[j] + C[y]);
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
