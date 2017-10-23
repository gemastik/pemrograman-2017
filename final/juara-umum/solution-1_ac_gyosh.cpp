#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50001;
const int MAXM = 50001;

int T;
int N, M, K;

int received[MAXM][3];
int standings[MAXN][3];
int par[MAXN][3];

int findPar(int x, int y) {
  if (par[x][y] == x) return x;
  return par[x][y] = findPar(par[x][y], y);
}

void print() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 3; j++) {
      par[i][j] = i;
    }
  }

  memset(standings, -1, sizeof(standings));
  for (int i = 0; i < M; i++) {
    int p = 0;

    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < received[i][j]; k++) {
        while (standings[p][j] != -1) {
          // Jump
          p = (findPar(p, j) + 1) % N;
        }
        standings[p][j] = i;

        if (standings[(p-1+N) % N][j] != -1) {
          // Chunk them
          par[findPar((p-1+N) % N, j)][j] = findPar(p, j);
        }

        p = (p + 1) % N;
      }
    }
  }

  printf("mungkin\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%d", standings[i][j] + 1);
      if (j < 2) {
        printf(" ");
      } else {
        printf("\n");
      }
    }
  }
}

void solve() {
  scanf("%d %d %d", &N, &M, &K);

  if (N/2 <= N%2) {
    printf("mustahil\n");
    return;
  }

  memset(received, 0, sizeof(received));

  /*
          G          S          B
  univ 1  floor(N/2) floor(N/2) N%2
  univ 2  floor(N/2) floor(N/2) N%2
  univ 3  N%2        N%2        N-(N%2)-(N%2)
  univ 4  0          0          0
  ...
   */

  for (int i = 0; i < 2; i++) {
    received[i][0] = N / 2;
    received[i][1] = N / 2;
    received[i][2] = N % 2;
  }
  received[2][0] = N % 2;
  received[2][1] = N % 2;
  received[2][2] = N - 2*(N % 2);

  print();
}

int main() {
  scanf("%d", &T);
  for (int jt = 0; jt < T; jt++) {
    solve();
  }
}
