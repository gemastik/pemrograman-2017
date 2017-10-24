#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int MAXN = 100001;
const int TRY = 50;
const double OO = 1e+20;
const double PI = acos(-1.0);
const double PI2 = 2*PI;
const double EPS = 1e-12;

struct Point{
  double x, y;
  double deg;
  double dist;

  Point() : x(0), y(0) {};
  Point(double _x, double _y) : x(_x), y(_y) {};
};

int T;
int N, K;
Point points[MAXN];

vector<double> rotPeriod;

bool eq(double a, double b) {
  return fabs(a - b) < EPS;
}

bool lesseq(double a, double b) {
  if (eq(a, b)) return true;
  return a < b;
}

// Ensure is within [0, 2*PI]
double normalize(double theta) {
  while (theta >= PI2) {
    theta -= PI2;
  }
  return theta;
}

double getPeakRadius(double rot) {
  double ans = OO;

  double lo = 0;
  double hi = PI2 / K;
  double period = PI2 / K;
  double cosPeriodDiv2 = cos(period/2);
  for (int i = 0; i < N; i++) {
    double pointDeg = points[i].deg - rot;
    while (!(lesseq(lo, pointDeg) && lesseq(pointDeg, hi))) {
      pointDeg += period;
      pointDeg = normalize(pointDeg);
    }

    double alpha = fabs(pointDeg - period/2);
    double innerRadius = points[i].dist * cos(alpha);
    double radius = innerRadius / cosPeriodDiv2;
    ans = min(ans, radius);
  }

  return ans;
}

double getPeakRadius(double _lo, double _hi) {
  double lo = _lo;
  double hi = _hi;
  for (int _ = 0; _ < TRY; _++) {
    double t1 = (lo + lo + hi) / 3;
    double t2 = (lo + hi + hi) / 3;

    if (getPeakRadius(t1) > getPeakRadius(t2)) {
      hi = t2;
    } else {
      lo = t1;
    }
  }

  double ans = max(getPeakRadius(_lo), getPeakRadius(_hi));
  return max(ans, getPeakRadius(lo));
}

double getBestRadius() {
  rotPeriod.clear();

  double lo = 0;
  double hi = PI2 / K;
  double period = PI2 / K;
  for (int i = 0; i < N; i++) {
    double worstRot = points[i].deg;
    while (!(lesseq(lo, worstRot) && lesseq(worstRot, hi))) {
      worstRot += period;
      worstRot = normalize(worstRot);
    }

    rotPeriod.push_back(worstRot);
  }

  rotPeriod.push_back(lo);
  rotPeriod.push_back(hi);

  sort(rotPeriod.begin(), rotPeriod.end());

  double bestRadius = 0;
  for (int i = 1; i < rotPeriod.size(); i++) {
    bestRadius = max(bestRadius, getPeakRadius(rotPeriod[i-1], rotPeriod[i]));
  }
  return bestRadius;
}

void solve() {
  scanf("%d %d", &N, &K);
  for (int i = 0; i < N; i++) {
    scanf("%lf %lf", &points[i].x, &points[i].y);
    points[i].deg = atan2(points[i].y, points[i].x);
    points[i].dist = sqrt(points[i].x * points[i].x + points[i].y * points[i].y);
  }

  double r = getBestRadius();
  printf("%.12lf\n", r);
}

int main() {
  scanf("%d", &T);
  for (int jt = 0; jt < T; jt++) {
    solve();
  }
}
