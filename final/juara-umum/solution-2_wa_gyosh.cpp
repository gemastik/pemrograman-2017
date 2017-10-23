/*
Not handling special case when K=1
 */
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50001;
const int MAXM = 50001;

int T;
int N, M, K;

int received[MAXM][3];
int standings[MAXN][3];
int par[MAXN][3];
bool possible;

int findPar(int x, int y) {
  if (par[x][y] == x) return x;
  return par[x][y] = findPar(par[x][y], y);
}

void print() {
  if (!possible) {
    printf("mustahil\n");
    return;
  }

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

int ceilDiv(int a, int b) {
  return a/b + ((a % b > 0) ? 1 : 0);
}

void k2CaseAssignment() {
  if (N/2 <= N%2) {
    possible = false;
    return;
  }
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
}

void kMoreThan2CaseAssignment() {
  // Greedily assign medals to top K winner
  int winnerGold = N/K;
  int totalLoserGold = N % K;
  int loserUnivCount = M-K;

  if (loserUnivCount == 0) {
    if (totalLoserGold > 0) {
      possible = false;
      return;
    }

    for (int i = 0; i < K; i++) {
      received[i][0] = N / K;
      received[i][1] = N / K;
      received[i][2] = N / K;
    }
    return;
  }

  int maxLoserGold = ceilDiv(totalLoserGold, loserUnivCount);
  int minLoserGold = totalLoserGold / loserUnivCount;

  if (winnerGold > maxLoserGold) {
    /*
              G           S           B
    univ 1    winnerGold   winnerGold   winnerGold
    univ 2    winnerGold   winnerGold   winnerGold
    ...
    univ K    winnerGold   winnerGold   winnerGold
    univ K+1  maxLoserGold maxLoserGold maxLoserGold
    univ K+2  maxLoserGold maxLoserGold maxLoserGold
    ...
    univ M    minLoserGold minLoserGold minLoserGold
     */
    for (int i = 0; i < K; i++) {
      received[i][0] = winnerGold;
      received[i][1] = winnerGold;
      received[i][2] = winnerGold;
    }
    for (int i = K; i < M; i++) {
      received[i][0] = minLoserGold;
      received[i][1] = minLoserGold;
      received[i][2] = minLoserGold;
    }
    int loserReceivingMaxGold = totalLoserGold % loserUnivCount;
    for (int i = 0; i < loserReceivingMaxGold; i++) {
      received[K + i][0]++;
      received[K + i][1]++;
      received[K + i][2]++;
    }
  } else {
    int maxTotalLoserGoldCapacity = maxLoserGold*loserUnivCount - 1; // At least 1 loser univ mustn't received maxLoserGold

    int loserUnivReceivingMaxGold = totalLoserGold % loserUnivCount;
    int loserUnivReceivingMinGold = loserUnivCount - loserUnivReceivingMaxGold;
    int loserUnivReceivingMaxBronze = 2*loserUnivReceivingMinGold;
    int loserUnivReceivingMinBronze = loserUnivCount - loserUnivReceivingMaxBronze;
    int maxBronze = N - maxLoserGold - minLoserGold;
    int minBronze = minLoserGold;

    int maxTotalLoserBronzeCapacity = maxBronze*loserUnivReceivingMaxBronze + minBronze*loserUnivReceivingMinBronze;
    int totalLoserBronze = totalLoserGold;

    if ((totalLoserGold > maxTotalLoserGoldCapacity) || (totalLoserBronze > maxTotalLoserBronzeCapacity)) {
      possible = false;
      return;
    }

    for (int i = 0; i < K; i++) {
      received[i][0] = winnerGold;
      received[i][1] = winnerGold;
      received[i][2] = winnerGold;
    }

    // Fill the base
    for (int i = K; i < M; i++) {
      received[i][0] = minLoserGold;
      received[i][1] = minLoserGold;
      received[i][2] = minBronze;
    }

    // Do a pass for everyone getting extra medal
    int p = K;
    for (int i = 0; i < loserUnivReceivingMaxGold; i++) {
      received[p][0] = maxLoserGold;
      p++;
    }
    for (int i = 0; i < loserUnivReceivingMaxGold; i++) {
      received[p][1] = maxLoserGold;
      p++;
      if (p == M) p = K;
    }
    int bronzeLeft = totalLoserBronze - loserUnivReceivingMinBronze*minBronze;
    int personLeft = M - p;
    int bronzePerPerson = bronzeLeft / personLeft;
    for (int i = p; i < M; i++) {
      received[i][2] = bronzePerPerson;
      bronzeLeft -= bronzePerPerson;
    }
    for (int i = p; i < M; i++) {
      if (bronzeLeft == 0) break;
      received[i][2]++;
      bronzeLeft--;
    }
  }
}

void solve() {
  scanf("%d %d %d", &N, &M, &K);

  memset(received, 0, sizeof(received));

  possible = true;
  if (K == 2) {
    k2CaseAssignment();
  } else {
    kMoreThan2CaseAssignment();
  }

  print();
}

int main() {
  scanf("%d", &T);
  for (int jt = 0; jt < T; jt++) {
    solve();
  }
}
