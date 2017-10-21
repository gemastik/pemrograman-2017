#include <bits/stdc++.h>

using namespace std;


const int MAXN = 50005;

int dfsNumberCounter, numSCC;
int dfs_low[MAXN];
int dfs_num[MAXN];
bitset<MAXN> visited;
int in[MAXN];
int size[MAXN];
vector<int> S;

int n, m;
vector<int> adj[MAXN];
vector<int> sccAdj[MAXN];
int pMin[MAXN], pMax[MAXN];


void tarjanSCC(int u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
    S.push_back(u);
	visited[u] = 1;
	for (int v : adj[u]) {
		if (dfs_num[v] == -1) {
			tarjanSCC(v);
		}
		if (visited[v]) {
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
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

int main() {
	int t;
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
			adj[u].push_back(v);	// u is followed v
		}

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
				tarjanSCC(j);
		}

		for (int j = 1; j <= n; ++j) {
			for (int v : adj[j]) {
				if (in[j] != in[v]) {
					sccAdj[in[j]].push_back(in[v]);
				}
			}
		}

		for (int j = 1; j <= numSCC; ++j) {
			dp[j] = -1;
			sort(sccAdj[j].begin(), sccAdj[j].end());
			sccAdj[j].erase(unique(sccAdj[j].begin(), sccAdj[j].end()), sccAdj[j].end());
		}

		int q;
		scanf("%d", &q);
		while (q--) {
			int x, h;
			scanf("%d %d", &x, &h);
			printf("%s\n", calc(in[x]) ? "Ya" : "Tidak");
		}
	}
	return 0;
}
