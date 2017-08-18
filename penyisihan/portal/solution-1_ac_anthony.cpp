#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100;
const int DX[] = { -1, 0, 1, 0 };
const int DY[] = { 0, -1, 0, 1 };

int r, c, p;
int fx, fy;
int dist[MAXN][30];
char grid[MAXN][30];

int getValue(int x, int y) {
	return isdigit(grid[x][y]) * (grid[x][y] - '0');
}

int len(int r1, int c1, int r2, int c2) {
	return 1 + abs(getValue(r1, c1) - getValue(r2, c2));
}

int dijkstra(int x, int y) {
	priority_queue<pair<int, pair<int, int>>> pq;
	pq.push({0, {x, y}});
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			dist[i][j] = INT_MAX;
		}
	}
	dist[x][y] = 0;

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

	return dist[fx][fy] + 1;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d", &r, &c, &p);
		for (int i = 0; i < r; ++i) {
			scanf("%s", grid[i]);
			for (int j = 0; j < c; ++j) {
				if (grid[i][j] == 'A') {
					fx = i, fy = j;
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < c; ++i) {
			ans += dijkstra(0, i);
		}
		printf("%d\n", ans);
	}
	return 0;
}
