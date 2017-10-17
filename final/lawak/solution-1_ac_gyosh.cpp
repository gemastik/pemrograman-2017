#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int MAXN = 100001;

int T;
int Hmin[MAXN];
int Hmax[MAXN];
int N, M, Q;
vector<int> adjlist[MAXN];
bool visited[MAXN];

int dfs(int node, int h) {
  int ret = 1;
  visited[node] = true;

  if ((Hmin[node] <= h) && (h <= Hmax[node])) {
    // Spread
    for (int next : adjlist[node]) {
      if (!visited[next]) {
        ret += dfs(next, h);
      }
    }
  }

  return ret;
}

void solve() {
  for (int i = 0; i < MAXN; i++) {
    adjlist[i].clear();
  }

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
  for (int i = 0; i < Q; i++) {
    int x, h;
    scanf("%d %d", &x, &h);

    x--;

    memset(visited, 0, sizeof(visited));
    printf("%d\n", dfs(x, h));
  }
}

int main() {
  scanf("%d", &T);
  for (int jt = 0; jt < T; jt++) {
    solve();
  }
}
