#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include <utility>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <stack>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;

typedef long long LL;

int T;
int N, A, B, C;

int JUTA = 1<<20;

void solve() {
  scanf("%d %d %d %d", &N, &A, &B, &C);

  int solA, solB;
  bool hasSolution = false;
  for (int i = 0; i < JUTA; i++) {
    int j = i ^ C;

    bool eqAnd = (i & j) == A;
    bool eqOr = (i | j) == B;
    if (eqAnd && eqOr) {
      hasSolution = true;
      solA = i;
      solB = j;
      break;
    }
  }

  if (!hasSolution) {
    printf("-1\n");
  } else {
    printf("%d %d\n", solA, solB);
  }
}

int main() {
  scanf("%d", &T);
  for (int jt = 0; jt < T; jt++) {
    solve();
  }
}
