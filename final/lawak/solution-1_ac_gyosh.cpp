/*
O(N) using DFS + memo
 */
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int MAXN = 50001;
const int MAXQ = 50001;

int T;
int Hmin[MAXN];
int Hmax[MAXN];
int N, M, Q;
vector<int> adjlist[MAXN];

bool inStack[MAXN];
int dp[MAXN];

void clear() {
  for (int i = 0; i < MAXN; i++) {
    adjlist[i].clear();
  }
}

void dfsDp(int x) {
  if (dp[x] != -1) {
    return;
  }

  dp[x] = 0;
  inStack[x] = true;

  for (int i = 0; i < adjlist[x].size(); i++) {
    int v = adjlist[x][i];

    if (inStack[v]) {
      dp[x] = 1;
      break;
    }

    dfsDp(v);
    if (dp[v] == 1) {
      dp[x] = 1;
      break;
    }
  }

  inStack[x] = false;
}

void solve() {
  clear();

  scanf("%d %d", &N, &M);

  for (int i = 0; i < N; i++) {
    scanf("%d", &Hmin[i]);
  }
  for (int i = 0; i < N; i++) {
    scanf("%d", &Hmax[i]);
  }
  for (int i = 0; i < M; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--;
    v--;
    adjlist[u].push_back(v);
  }

  scanf("%d", &Q);
  memset(dp, -1, sizeof(dp));
  for (int i = 0; i < Q; i++) {
    int x, h;
    scanf("%d %d", &x, &h);

    x--;
    dfsDp(x);

    printf("%s\n", (dp[x] == 1) ? "Ya" : "Tidak");
  }
}

int main() {
  // scanf("%d", &T);
  T = 1;
  for (int jt = 0; jt < T; jt++) {
    solve();
  }
}
