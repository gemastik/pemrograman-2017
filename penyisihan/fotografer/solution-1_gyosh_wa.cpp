/*
	reason for WA: not handling "mustahil" case
 */
#include <bits/stdc++.h>

using namespace std;

const char MALE = 'L';
const char FEMALE = 'P';

void impossibru() {
	// printf("mustahil\n");
}

void solve0(int B, int K) {
	if (B > K) {
		impossibru();
		return;
	}

	for (int i = 0; i < B; i++) {
		printf("%c", FEMALE);
	}
	printf("\n");
}

void solve1(int B, int K) {
	if (B > 2*K) {
		impossibru();
		return;
	}

	int left = min(B, K);
	int right = B - left;

	for (int i = 0; i < left; i++) {
		printf("%c", FEMALE);
	}
	printf("%c", MALE);
	for (int i = 0; i < right; i++) {
		printf("%c", FEMALE);
	}
	printf("\n");
}

int main() {
	int A, B, K;
	scanf("%d %d %d", &A, &B, &K);

	if (A == 0) {
		solve0(B, K);
	} else { // A == 1
		solve1(B, K);
	}
}