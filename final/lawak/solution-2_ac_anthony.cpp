#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50005;

int dfsNumberCounter, numSCC;

int dfs_low[MAXN];
int dfs_num[MAXN];
bitset<MAXN> visited;
vector<int> adj[MAXN];
vector<int> sccAdj[MAXN];
vector<int> S;

int in[MAXN];
int size[MAXN];

int pMin[MAXN], pMax[MAXN];

void tarjanSCC(int p, int u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
    S.push_back(u);
	visited[u] = 1;
	if (pMin[u] <= p && p <= pMax[u]) {
		for (int v : adj[u]) {
			if (dfs_num[v] == -1) {
				tarjanSCC(p, v);
			}
			if (visited[v]) {
				dfs_low[u] = min(dfs_low[u], dfs_low[v]);
			}
		}
	}
    if (dfs_low[u] == dfs_num[u]) {
		++numSCC;
        while (1) {
			int v = S.back(); S.pop_back(); visited[v] = 0;
			in[v] = numSCC;
			size[u]++;
            if (u == v) break;
        }
    }
}

vector<pair<int, int>> query[MAXN];

int dp[MAXN];

int calc(int u) {
	int &ret = dp[u];
	if (ret != -1) return ret;
	ret = size[u] > 1;
	for (int v : adj[u]) {
		ret |= calc(v);
	}
	return ret;
}

int ans[MAXN];

int main() {
	int t, n, m;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &pMin[i]);
			adj[i].clear();
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &pMax[i]);
		}
		for (int i = 0; i < m; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			adj[u].push_back(v);
		}

		for (int i = 0; i < 101; ++i) {
			query[i].clear();
		}

		int q, s, p;
		scanf("%d", &q);
		for (int i = 0; i < q; ++i) {
			scanf("%d %d", &s, &p);
			query[p].push_back({s, i});
		}

		for (int i = 0; i < 101; ++i) {
			for (int j = 1; j <= n; ++j) {
				dfs_num[j] = -1;
				dfs_low[j] = 0;
				visited[j] = 0;
				in[j] = -1;
				size[j] = 0;
				sccAdj[j].clear();
			}
			S.clear();
			dfsNumberCounter = numSCC = 0;

			for (int j = 1; j <= n; ++j) {
				if (dfs_num[j] == -1)
					tarjanSCC(i, j);
			}

			for (int j = 1; j <= n; ++j) {
				if (pMin[j] <= i && i <= pMax[j]) {
					for (int v : adj[j]) {
						if (in[j] != in[v]) {
							sccAdj[in[j]].push_back(in[v]);
						}
					}
				}
			}

			for (int j = 1; j <= numSCC; ++j) {
				dp[j] = -1;
				sort(sccAdj[j].begin(), sccAdj[j].end());
				sccAdj[j].erase(unique(sccAdj[j].begin(), sccAdj[j].end()), sccAdj[j].end());
			}

			for (const pair<int, int> q : query[i]) {
				ans[q.second] = calc(in[q.first]);
			}
		}

		for (int i = 0; i < q; ++i) {
			printf("%s\n", ans[i] ? "Ya" : "Tidak");
		}
	}
}
