#include <bits/stdc++.h>

using namespace std;

int main() {
	int t, n, a, b, c;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d %d", &n, &a, &b, &c);
		if ((a ^ b) == c) {
			printf("%d %d\n", a, b);
		} else {
			printf("-1\n");
		}
	}
	return 0;
}
