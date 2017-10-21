#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50000;

int main() {
	int t, n, a, b, c;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d %d", &n, &a, &b, &c);
		int ans[MAXN] = {};
		for (int i = 30; i >= 0; --i) {
			int x = (a & (1 << i));
			if (x) {
				for (int j = 0; j < n; ++j) {
					ans[j] |= x;
				}
			} else if (b & (1 << i)) {
				ans[0] |= (1 << i);
				if (!(c & (1 << i))) {
					ans[1] |= (1 << i);
				}
			}
		}
		int ands = INT_MAX, ors = 0, xors = 0;
		for (int i = 0; i < n; ++i) {
			ands &= ans[i];
			ors |= ans[i];
			xors ^= ans[i];
		}
		if (ands != a || ors != b || xors != c) {
			printf("-1\n");
		} else {
			for (int i = 0; i < n; ++i) {
				printf("%d%c", ans[i], " \n"[i == n - 1]);
			}
		}
	}
	return 0;
}
