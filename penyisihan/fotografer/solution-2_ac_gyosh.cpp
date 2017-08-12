#include <bits/stdc++.h>

using namespace std;

const char MALE = 'L';
const char FEMALE = 'P';

/*
  1. Spread all the A in pairs
  2. Fill in the gap, starting from "slotA" as even as possible
  3. Continue to fill for "slotB", as even as possible too
  4. Continue to fill for "slotC", as even as possible too
  5. Construct the string, then validate

  slotA = first priority for filling, to ensure all "AA" is separated
  slotB = second priority for filling, located in first & last of sequence
  slotC = last priority for filling, in between all "AA"

  Even case:
  _____ [A_____A] _____ [A_____A] _____ [A_____A] _____
                  slotA           slotA
  slotB                                           slotB
          slotC           slotC           slotC

  Odd case:
  _____ [A_____A] _____ [A_____A] _____ [A] _____
                  slotA           slotA
  slotB                                     slotB
          slotC           slotC
 */
int T;
int A, B, K;
vector<int> slotA, slotB, slotC;
char result[1000005];

int ceilDiv(int x, int y) {
  return (x + y - 1) / y;
}

int fillSlot(int femaleLeft, int K, vector<int> &slot) {
  if (femaleLeft == 0) return 0;

  int femaleUsed = 0;
  for (int i = 0; i < K; i++) {
    for (int j = 0; j < slot.size(); j++) {
      slot[j]++;
      femaleUsed++;

      if (femaleUsed == femaleLeft) return femaleUsed;
    }
  }
  return femaleUsed;
}

void constructOutputResult() {
  int p = 0;

  for (int i = 0; i < slotB[0]; i++) {
    result[p++] = FEMALE;
  }

  // Alternating C, A, C, A, ...
  for (int i = 0; i < slotA.size()+slotC.size(); i++) {
    int pa = 0;
    int pc = 0;

    result[p++] = MALE;
    if (i % 2 == 0) {
      // slotC
      for (int j = 0; j < slotC[pc]; j++) {
        result[p++] = FEMALE;
      }
      pc++;
    } else {
      // slotA
      for (int j = 0; j < slotA[pa]; j++) {
        result[p++] = FEMALE;
      }
      pa++;
    }
  }

  result[p++] = MALE;
  for (int i = 0; i < slotB[1]; i++) {
    result[p++] = FEMALE;
  }

  result[p++] = 0;
}

bool isValidResult() {
  int len = strlen(result);
  if (len != A + B) return false;

  char lastChar = ' ';
  int cnt = 0;
  for (int i = 0; i < len; i++) {
    if (result[i] == lastChar) {
      cnt++;
    } else {
      if ((lastChar == MALE) && (cnt > 2)) return false;
      if ((lastChar == FEMALE) && (cnt > K)) return false;

      lastChar = result[i];
      cnt = 1;
    }
  }
  if ((lastChar == MALE) && (cnt > 2)) return false;
  if ((lastChar == FEMALE) && (cnt > K)) return false;
  return true;
}

void solve() {
  scanf("%d %d %d", &A, &B, &K);

  slotA.clear();
  slotB.clear();
  slotC.clear();

  if (A == 0) {
    if (B > K) {
      printf("mustahil\n");
    } else {
      for (int i = 0; i < B; i++) {
        printf("%c", FEMALE);
      }
      printf("\n");
    }

    return;
  }

  // Prep
  for (int i = 0; i < ceilDiv(A, 2) - 1; i++) {
    slotA.push_back(0);
  }

  slotB.push_back(0);
  slotB.push_back(0);

  for (int i = 0; i < A/2; i++) {
    slotC.push_back(0);
  }

  // Fill
  int femaleLeft = B;

  femaleLeft -= fillSlot(femaleLeft, K, slotA);
  femaleLeft -= fillSlot(femaleLeft, K, slotB);
  femaleLeft -= fillSlot(femaleLeft, K, slotC);

  // Construct output
  constructOutputResult();

  if (isValidResult()) {
    printf("%s\n", result);
  } else {
    printf("mustahil\n");
  }
}

int main() {
  scanf("%d", &T);
  for (int jt = 0; jt < T; jt++) {
    solve();
  }
}
