#include <bits/stdc++.h>

using namespace std;

void printFemale(int k = 1) {
	for (int i = 0; i < k; ++i) {
		printf("P");
	}
}

void printMale(int k = 1) {
	for (int i = 0; i < k; ++i) {
		printf("L");
	}
}

int main() {
	int t, a, b, k;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d", &a, &b, &k);
		int minPart = (int) ceil((double) b / k);
		if (a < minPart - 1 || a > (b + 1) * 2) {
			printf("mustahil\n");
		} else {
			if (a == minPart - 1) {
				for (int i = 0; i < minPart; ++i) {
					int x = min(b, k);
					printFemale(x);
					b -= x;
					printf("%c", "L\n"[i == minPart - 1]);
				}
			} else {
				for (int i = 0; i < minPart; ++i) {
					int x = min(b, k);
					b -= x;
					for (int j = 0; j < x; ++j) {
						if (j == 0) {
							printMale();
							a -= 1;
						}
						if (a > 2 * b) {
							if (a - 2 > 2 * b && j != 0) {
								printMale(2);
								a -= 2;
							} else {
								printMale();
								a -= 1;
							}
						}
						printFemale();
					}
				}
				printMale(a);
				printf("\n");
			}
		}
	}
	return 0;
}