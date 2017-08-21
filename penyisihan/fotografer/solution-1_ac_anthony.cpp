#include <bits/stdc++.h>

using namespace std;

int main() {
	int t, a, b, k;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d", &a, &b, &k);
		if (a == 0) {
			if (b > k) {
				printf("mustahil\n");
			} else {
				for (int i = 0; i < b; ++i) {
					printf("P");
				}
				printf("\n");
			}
		} else {
			if (b > 2 * k) {
				printf("mustahil\n");
			} else {
				int x = min(b, k);
				for (int i = 0; i < x; ++i) {
					printf("P");
				}
				printf("L");
				x = b - x;
				for (int i = 0; i < x; ++i) {
					printf("P");
				}
				printf("\n");
			}
		}
	}
	return 0;
}