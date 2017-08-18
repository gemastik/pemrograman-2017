#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100;
const int MOD = 1e9 + 7;
const int DX[] = { -1, 0, 1, 0 };
const int DY[] = { 0, -1, 0, 1 };

int r, c, p;
int dist[MAXN][30];
char grid[MAXN][30];
int fx[30], fy[30];

int getValue(int x, int y) {
	return isdigit(grid[x][y]) * (grid[x][y] - '0');
}

int len(int r1, int c1, int r2, int c2) {
	return 1 + abs(getValue(r1, c1) - getValue(r2, c2));
}

int portDist[30][30];

vector<int> costs;

int dijkstra(int x, int y) {
	int col = y;
	priority_queue<pair<int, pair<int, int>>> pq;
	pq.push({0, {x, y}});
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			dist[i][j] = INT_MAX;
		}
	}
	dist[x][y] = 1;

	while (!pq.empty()) {
		pair<int, pair<int, int>> u = pq.top();
		pq.pop();
		int d = -u.first;
		int x = u.second.first;
		int y = u.second.second;
		if (dist[x][y] == d) {
			for (int i = 0; i < 4; ++i) {
				int xx = x + DX[i], yy = y + DY[i];
				if (xx < 0 || xx == r || yy < 0 || yy == c || dist[xx][yy] <= dist[x][y] + len(x, y, xx, yy)) {
					continue;
				}
				dist[xx][yy] = dist[x][y] + len(x, y, xx, yy);
				pq.push({-dist[xx][yy], {xx, yy}});
			}
		}
	}

	for (int i = 0; i < p; ++i) {
		portDist[col][i] = dist[fx[i]][fy[i]];
		costs.push_back(dist[fx[i]][fy[i]]);
	}
}

int maxVal;

int dp[MAXN][30][2];

int calc(int idx, int i, int matched) {
	if (i == p) {
		return matched;
	}
	if (idx == c) return 0;
	int &ret = dp[idx][i][matched];
	if (ret != -1) return ret;
	ret = calc(idx + 1, i, matched);
	if (portDist[idx][i] <= maxVal) {
		(ret += calc(idx + 1, i + 1, matched | (portDist[idx][i] == maxVal))) %= MOD;
	}
	return ret;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d", &r, &c, &p);
		for (int i = 0; i < r; ++i) {
			scanf("%s", grid[i]);
			for (int j = 0; j < c; ++j) {
				if (isalpha(grid[i][j])) {
					fx[grid[i][j] - 'A'] = i;
					fy[grid[i][j] - 'A'] = j;
				}
			}
		}

		costs.clear();

		for (int i = 0; i < c; ++i) {
			dijkstra(0, i);
		}

		int ans = 0;

		sort(costs.begin(), costs.end());
		costs.erase(unique(costs.begin(), costs.end()), costs.end());

		for (int c : costs) {
			maxVal = c;
			memset(dp, -1, sizeof dp);
			(ans += (1LL * calc(0, 0, 0) * maxVal) % MOD) %= MOD;
		}

		printf("%d\n", ans);
	}
	return 0;
}