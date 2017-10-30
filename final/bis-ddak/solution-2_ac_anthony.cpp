#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250;

int u[MAXN + 5], v[MAXN + 5];
bool used[MAXN + 5];
int p[MAXN + 5], way[MAXN + 5];
int minv[MAXN + 5];
int ans[MAXN + 5];
int n, m;
int k;
int val[MAXN + 5][MAXN + 5];

int Assign(){
	for (int i = 1; i <= k; ++i) {
		p[i] = way[i] = 0;
	}
    for(int i = 1 ; i <= k ; i++) {
        p[0] = i;
        int j0 = 0;
        for(int j = 1 ; j <= k ; j++)
            minv[j] = 1000000000, used[j] = 0;
        do {
            used[j0] = 1;
            int i0 = p[j0], delta = 1000000000, j1;
            for(int j = 1 ; j <= k ; j++)
                if (!used[j]) {
                    int cur = val[i0][j] - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur,way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j], j1 = j;     
                }
            for (int j = 0 ; j <= k ; j++)
                if (used[j])
                   u[p[j]] += delta,  v[j] -= delta; 
                else
                   minv[j] -= delta;  
            j0 = j1;           
        } while (p[j0] != 0);
        do{
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
		} while (j0);
    }
    for(int i = 1 ; i <= k ; i++)
        ans[p[i]] = i;
    
    int ret = 0;
    for(int i = 1 ; i <= k ; i++)
        ret += val[i][ans[i]];
           
    return ret;    
}

vector<vector<int>> output;
vector<int> dum;

void dfs(int u) {
	dum.push_back(u);
	used[u] = 1;
	if (!used[ans[u]]) {
		dfs(ans[u]);
	}
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				val[i][j] = 1e9;
			}
			scanf("%d", &val[i][i]);
		}
		for (int i = 0; i < m; ++i) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			val[u][v] = w;
		}
		k = n;
		int cost = Assign();
		memset(used, 0, sizeof used);
		output.clear();
		for (int i = 1; i <= n; ++i) {
			dum.clear();
			if (!used[i]) {
				dfs(i);
				if (dum.size() > 1) {
					output.push_back(dum);
				}
			}
		}
		printf("%d %d\n", cost, output.size());
		for (const vector<int>& v : output) {
			printf("%d", v.size());
			for (int u : v) {
				printf(" %d", u);
			}
			printf("\n");
		}
	}
	return 0;
}