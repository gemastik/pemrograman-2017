#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int LOGN = 18;

int n;
int p[MAXN];
int r[MAXN];

vector<int> child[MAXN];
vector<int> q[MAXN];

int lvl[MAXN];

int dp[LOGN][MAXN];

void dfs(int u) {
	for (int v : child[u]) {
		lvl[v] = lvl[u] + 1;
		dfs(v);
	}
}

void preprocess() {
	dfs(1);
	for (int i = 1; i <= n; ++i) {
		dp[0][i] = p[i];
	}
	for (int i = 1; i < LOGN; ++i) {
		for (int j = 1; j <= n; ++j) {
			dp[i][j] = dp[i - 1][dp[i - 1][j]];
		}
	}
}

int lca(int u, int v) {
	if (lvl[u] < lvl[v]) {
		swap(u, v);
	}
	for (int i = LOGN - 1; i >= 0; --i) {
		if (lvl[u] - (1 << i) >= lvl[v]) {
			u = dp[i][u];
		}
	}
	if (u == v) return u;
	for (int i = LOGN - 1; i >= 0; --i) {
		if (dp[i][u] && dp[i][u] != dp[i][v]) {
			u = dp[i][u], v = dp[i][v];
		}
	}
	return p[u];
}

long long ans;

int ft[MAXN];

void update(int p, int v) {
	for (; p < MAXN; p += p & -p) {
		ft[p] += v;
	}
}

int query(int p) {
	int ans = 0;
	while (p) {
		ans += ft[p];
		p -= p & -p;
	}
	return ans;
}

int query(int l, int r) {
	return query(r) - query(l - 1);
}

void rec(int u) {
	update(r[u], 1);
	for (int i : q[u]) {
		ans += query(i + 1, MAXN - 1);
	}
	for (int v : child[u]) {
		rec(v);
	}
	update(r[u], -1);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			child[i].clear();
			q[i].clear();
		}
		for (int i = 2; i <= n; ++i) {
			scanf("%d", &p[i]);
			child[p[i]].push_back(i);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &r[i]);
		}
		preprocess();
		for (int i = 1; i < n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				q[lca(i, j)].push_back(max(r[i], r[j]));
			}	
		}
		ans = 0;
		rec(1);
		printf("%lld\n", ans);
	}
}
