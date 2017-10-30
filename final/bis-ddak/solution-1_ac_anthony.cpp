#include <bits/stdc++.h>

using namespace std;

const int MAXN = 12;

int n;

vector<int> optRoute[1 << MAXN];
int cost[1 << MAXN];

int dp[1 << MAXN][MAXN][MAXN];
int adj[MAXN][MAXN];

int rec(int mask, int start, int current) {
	if (mask == 0) return adj[current][start];
	int &ret = dp[mask][start][current];
	if (ret != -1) return ret;
	ret = 1e9;
	for (int v = 0; v < n; ++v) {
		if (adj[current][v] != 1e9 && (mask & (1 << v))) {
			ret = min(ret, adj[current][v] + rec(mask ^ (1 << v), start, v));
		}
	}
	return ret;
}

vector<int> route;

void dfs(int mask, int start, int current) {
	route.push_back(current);
	if (mask == 0) return;
	for (int v = 0; v < n; ++v) {
		if (adj[current][v] != 1e9 && (mask & (1 << v))) {
			if (adj[current][v] + rec(mask ^ (1 << v), start, v) == dp[mask][start][current]) {
				dfs(mask ^ (1 << v), start, v);
				break;
			}
		}
	}
}

void computeRoute(int mask) {
	for (int i = 0; i < n; ++i) {
		if (mask & (1 << i)) {
			if (mask - (1 << i) == 0) {
				cost[mask] = adj[i][i];
				return;
			}
			cost[mask] = rec(mask ^ (1 << i), i, i);
			route.clear();
			dfs(mask ^ (1 << i), i, i);
			optRoute[mask] = route;
		}
	}
}

int dp2[1 << MAXN];

int calc(int mask) {
	if (mask == 0) return 0;
	int &ret = dp2[mask];
	if (ret != -1) return ret;
	ret = 1e9;
	for (int i = mask; i; i = (i - 1) & mask) {
		if (cost[i] == -1) {
			computeRoute(i);
		}
		ret = min(ret, calc(mask ^ i) + cost[i]);
	}
	return ret;
}

vector<int> paths;

void rec2(int mask) {
	for (int i = mask; i; i = (i - 1) & mask) {
		if (calc(mask ^ i) + cost[i] == dp2[mask]) {
			if (i & (i - 1)) {
				paths.push_back(i);
			}
			rec2(mask ^ i);
			break;
		}
	}
}

int main() {
	int t, m;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				adj[i][j] = 1e9;
			}
			scanf("%d", &adj[i][i]);
		}
		for (int j = 0; j < m; ++j) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			adj[u - 1][v - 1] = w;
		}

		memset(dp, -1, sizeof dp);
		memset(cost, -1, sizeof cost);
		// for (int i = (1 << n) - 1; i >= 0; --i) {
		// 	computeRoute(i);
		// }
		memset(dp2, -1, sizeof dp2);
		int ans = calc((1 << n) - 1);
		paths.clear();
		rec2((1 << n) - 1);
		printf("%d %d\n", ans, paths.size());
		for (int m : paths) {
			printf("%d", optRoute[m].size());
			for (int v : optRoute[m]) {
				printf(" %d", v + 1);
			}
			printf("\n");
		}
	}
	return 0;
}