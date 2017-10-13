#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

int T;
int N, A, B, C;

int MAX_BIT = 32;

/*
A B C  response
-----
0 0 0  0
0 0 1  impossible
0 1 0  0/1, even 1
0 1 1  0/1, odd 1
1 0 0  impossible
1 0 1  impossible
1 1 0  1, even 1
1 1 1  1, odd 1
 */

// Return 1/0
int getBit(int a, int x) {
  return ((a & (1<<x)) > 0) ? 1 : 0;
}

int setBit(int a, int x, int v) {
  // Turn off then set the bit
  return a ^ (getBit(a, x) * (1<<x)) | (v * (1<<x));
}

void solve() {
  scanf("%d %d %d %d", &N, &A, &B, &C);

  // Check possibility
  bool possible = true;
  bool mustFull1Even = false;
  bool mustFull1Odd = false;
  for (int i = 0; i < MAX_BIT; i++) {
    int bitA = getBit(A, i);
    int bitB = getBit(B, i);
    int bitC = getBit(C, i);

    if ( ((bitA == 0) && (bitB == 0) && (bitC == 1))
      || ((bitA == 1) && (bitB == 0)) ) {
      possible = false;
      break;
    }

    if ((bitA == 1) && (bitB == 1)) {
      if (bitC == 0) {
        mustFull1Even = true;
      } else {
        mustFull1Odd = true;
      }
    }
  }

  if (mustFull1Even && mustFull1Odd) {
    possible = false;
  }
  if (mustFull1Even && (N % 2 != 0)) {
    possible = false;
  }
  if (mustFull1Odd && (N % 2 != 1)) {
    possible = false;
  }

  if (!possible) {
    printf("-1\n");
    return;
  }

  vector<int> ans;

  // Put minimum solution to ans
  if ((A == B) && (A == C) && (B == C)) {
    ans.push_back(A);
  } else {
    int n; // Lowest possible number of elements to satisfy problem's needs
    if (mustFull1Odd) {
      n = 3;
    } else {
      n = 2;
    }

    for (int i = 0; i < n; i++) {
      ans.push_back(0);
    }

    for (int b = 0; b < MAX_BIT; b++) {
      int bitA = getBit(A, b);
      int bitB = getBit(B, b);
      int bitC = getBit(C, b);

      if ((bitA == 0) && (bitB == 0) && (bitC == 0)) {
        // Full 0
        for (int i = 0; i < ans.size(); i++) {
          ans[i] = setBit(ans[i], b, 0);
        }

      } else if ((bitA == 0) && (bitB == 1) && (bitC == 0)) {
        // Even number of 1s
        for (int i = 0; i < 2; i++) {
          ans[i] = setBit(ans[i], b, 1);
        }
        for (int i = 2; i < ans.size(); i++) {
          ans[i] = setBit(ans[i], b, 0);
        }

      } else if ((bitA == 0) && (bitB == 1) && (bitC == 1)) {
        // Odd number of 1s
        ans[0] = setBit(ans[0], b, 1);
        for (int i = 1; i < ans.size(); i++) {
          ans[i] = setBit(ans[i], b, 0);
        }

      } else if ((bitA == 1) && (bitB == 1)) {
        // Full 1, odd or even already handled
        for (int i = 0; i < ans.size(); i++) {
          ans[i] = setBit(ans[i], b, 1);
        }
      }
    }
  }

  // Add filler to N
  int fillerIdxStart = ans.size();
  for (int i = fillerIdxStart; i < N; i++) {
    ans.push_back(0);
  }
  for (int b = 0; b < MAX_BIT; b++) {
    int bitA = getBit(A, b);
    int bitB = getBit(B, b);
    int bitC = getBit(C, b);

    if ((bitA == 0) && (bitB == 0) && (bitC == 0)) {
      for (int i = fillerIdxStart; i < N; i++) {
        ans[i] = setBit(ans[i], b, 0);
      }

    } else if ((bitA == 0) && (bitB == 1)) {
      for (int i = fillerIdxStart; i < N; i++) {
        ans[i] = setBit(ans[i], b, 0);
      }

    } else if ((bitA == 1) && (bitB == 1)) {
      for (int i = fillerIdxStart; i < N; i++) {
        ans[i] = setBit(ans[i], b, 1);
      }
    }
  }

  printf("%d\n", (int)ans.size());
  for (int i = 0; i < ans.size(); i++) {
    printf("%d\n", ans[i]);
  }
}

int main() {
  scanf("%d", &T);
  for (int jt = 0; jt < T; jt++) {
    solve();
  }
}
