#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXR = 100005;

int n;
int p[MAXN];
int r[MAXN];
vector<int> child[MAXN];
vector<int> richness[MAXN];

// Euler Tour Tree

int b[MAXN];
int e[MAXN];
int idx = 0;

void dfs(int u) {
	b[u] = ++idx;
	for (int v : child[u]) {
		dfs(v);
	}
	e[u] = idx;
}

// Fenwick Tree

int ft[MAXN];

void update(int p, int v) {
	for (; p <= n; p += p & -p) {
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


int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			child[i].clear();
		}
		for (int i = 1; i < MAXR; ++i) {
			richness[i].clear();
		}
		for (int i = 2; i <= n; ++i) {
			scanf("%d", &p[i]);
			assert(p[i] > 0 && p[i] < i);
			child[p[i]].push_back(i);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &r[i]);
			assert(r[i] > 0 && r[i] < MAXR);
			richness[r[i]].push_back(i);

			update(i, 1);
		}
		idx = 0;
		dfs(1);
		assert(idx == n);
		long long ans = 0;
		for (int i = MAXR - 1; i; --i) {
			for (int j : richness[i]) {
				update(b[j], -1);
			}
			for (int j : richness[i]) {
				int subSize = query(b[j], e[j]);
				ans += ((long long) subSize * (subSize - 1)) >> 1;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
