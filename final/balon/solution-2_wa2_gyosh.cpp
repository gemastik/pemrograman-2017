/*
Reason: printing nan
 */
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

int T;

int main() {
  scanf("%d", &T);
  for (int jt = 0; jt < T; jt++) {
    printf("%lf\n", std::numeric_limits<double>::quiet_NaN());
  }
}
