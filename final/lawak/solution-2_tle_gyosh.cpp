/*
Reason for TLE: using dirty DFS + find cycle + prune immediately
 */
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int MAXN = 50001;
const int MAXQ = 50001;

struct Question{
  int x, h, idx;
};

int T;
int Hmin[MAXN];
int Hmax[MAXN];
int N, M, Q;
vector<int> adjlist[MAXN];
int inStack[MAXN];

void clear() {
  for (int i = 0; i < MAXN; i++) {
    adjlist[i].clear();
  }
}

int qId = 0; // Question ID, used to eliminate the needs to reset inStack for every question
int dankness;
bool dfs(int x) {
  if (inStack[x] == qId) {
    // Forming loop, returning true
    return true;
  }

  inStack[x] = qId;

  if ((Hmin[x] <= dankness) && (dankness <= Hmax[x])) {
    for (int v : adjlist[x]) {
      if (dfs(v)) return true;
    }
  }

  inStack[x] = -1;
  return false;
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
  memset(inStack, -1, sizeof(inStack));
  for (int i = 0; i < Q; i++) {
    int x, h;
    scanf("%d %d", &x, &h);

    x--;

    dankness = h;
    qId++;
    bool ans = dfs(x);
    printf("%s\n", ans ? "Ya" : "Tidak");
  }
}

int main() {
  // scanf("%d", &T);
  T = 1;
  for (int jt = 0; jt < T; jt++) {
    solve();
  }
}
