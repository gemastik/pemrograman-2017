/*
Reason for TLE: not doing memoization
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

vector<int> dfsScc;
bool inStack[MAXN];
int dfsNum[MAXN];
int dfsLow[MAXN];
int dfsNumberCounter;
int sccCount;
int sccId[MAXN];
int sccSize[MAXN];
vector<int> sccAdjlist[MAXN];

void clear() {
  for (int i = 0; i < MAXN; i++) {
    adjlist[i].clear();
  }
}

void tarjanSCC(int u) {
  dfsLow[u] = dfsNum[u] = dfsNumberCounter++;
  dfsScc.push_back(u);
  inStack[u] = true;

  for (int v : adjlist[u]) {
    if (dfsNum[v] == -1)
      tarjanSCC(v);

    if (inStack[v]) {
      dfsLow[u] = min(dfsLow[u], dfsLow[v]);
    }
  }

  if (dfsLow[u] == dfsNum[u]) {
    sccSize[sccCount] = 0;

    // printf("SCC %d: ", sccCount);
    while ((dfsScc.size() > 0) && (dfsScc.back() != u)) {
      int node = dfsScc.back();
      // printf("%d ", 1+node);
      inStack[node] = false;
      sccId[node] = sccCount;
      dfsScc.pop_back();
      sccSize[sccCount]++;
    }
    int node = dfsScc.back();
    // printf("%d\n", 1+node);
    inStack[node] = false;
    sccId[node] = sccCount;
    dfsScc.pop_back();
    sccSize[sccCount]++;

    sccCount++;
  }
}

int dfs(int sccNode) {
  int ret = sccSize[sccNode];
  for (int next : sccAdjlist[sccNode]) {
    ret = max(ret, dfs(next));
    if (ret > 1) break;
  }
  return ret;
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

  // Discover SCC
  sccCount = 0;
  dfsNumberCounter = 0;
  dfsScc.clear();
  memset(inStack, 0, sizeof(inStack));
  memset(dfsNum, -1, sizeof(dfsNum));
  memset(dfsLow, -1, sizeof(dfsLow));
  memset(sccId, -1, sizeof(sccId));
  memset(sccSize, 0, sizeof(sccSize));
  for (int i = 0; i < N; i++) {
    if (dfsLow[i] == -1) {
      tarjanSCC(i);
    }
  }

  // Contract SCC, forming DAG
  for (int i = 0; i < sccCount; i++) {
    sccAdjlist[i].clear();
  }
  for (int i = 0; i < N; i++) {
    for (int j : adjlist[i]) {
      int u = sccId[i];
      int v = sccId[j];

      if (u != v) {
        sccAdjlist[u].push_back(v);
      }
    }
  }
  for (int i = 0; i < sccCount; i++) {
    sort(sccAdjlist[i].begin(), sccAdjlist[i].end());
    sccAdjlist[i].erase(unique(sccAdjlist[i].begin(), sccAdjlist[i].end()), sccAdjlist[i].end());
  }

  // Answer question with DFS
  scanf("%d", &Q);
  for (int i = 0; i < Q; i++) {
    int x, h;
    scanf("%d %d", &x, &h);

    x--;

    bool answer = dfs(sccId[x]) > 1;
    printf("%s\n", answer ? "Ya" : "Tidak");
  }
}

int main() {
  // scanf("%d", &T);
  T = 1;
  for (int jt = 0; jt < T; jt++) {
    solve();
  }
}
