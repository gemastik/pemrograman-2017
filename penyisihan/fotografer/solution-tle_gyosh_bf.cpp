#include <bits/stdc++.h>

using namespace std;

const char MALE = 'L';
const char FEMALE = 'P';

int arr[2001];
int solution[2001];
int A, B, K;
bool solutionFound;

void rek(int idx, int nA, int nB, int consecutiveA, int consecutiveB) {
  if (idx == A+B) {
    solutionFound = true;
    for (int i = 0; i < A+B; i++) {
      solution[i] = arr[i];
    }
  } else {
    if ((nA > 0) && (consecutiveA < 2)) {
      arr[idx] = 0;
      rek(idx+1, nA-1, nB, consecutiveA+1, 0);
    }

    if (solutionFound) return; // No need to continue searching

    if ((nB > 0) && (consecutiveB < K)) {
      arr[idx] = 1;
      rek(idx+1, nA, nB-1, 0, consecutiveB+1);
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int jt = 0; jt < T; jt++) {
    scanf("%d %d %d", &A, &B, &K);

    solutionFound = false;
    rek(0, A, B, 0, 0);

    if (solutionFound) {
      for (int i = 0; i < A+B; i++) {
        printf("%c", (solution[i] == 0) ? MALE : FEMALE);
      }
      printf("\n");
    } else {
      printf("mustahil\n");
    }
  }
}
