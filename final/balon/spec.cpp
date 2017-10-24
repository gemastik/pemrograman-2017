#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

const int MAX_N = 100;
const int MIN_COORD = -1000000;
const int MAX_COORD = 1000000;
const double PI = acos(-1.0);

typedef long long ll;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N, M;
    vector<vector<int>> coords;

    double res;

    void InputFormat() {
        LINE(N, M);
        LINES(coords) % SIZE(N);
    }

    void OutputFormat() {
        LINE(res);
    }

    void StyleConfig() {
        CustomScorer();
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 10);
    }

    void Constraints() {
        CONS(3 <= M && M <= 10);
        CONS(completeCoords());
        CONS(coordsBetween(MIN_COORD, MAX_COORD));
        CONS(noPointOnOrigin());
    }

    void Subtask1() {
        CONS(N == 1);
    }

    void Subtask2() {
        CONS(1 <= N && N <= MAX_N);
    }

private:
    bool completeCoords() {
        return all_of(coords.begin(), coords.end(), [](const vector<int> &coord) {
            return coord.size() == 2;
        });
    }
    bool coordsBetween(int lo, int hi) {
        return all_of(coords.begin(), coords.end(), [lo, hi](const vector<int> &coord) {
            return (lo <= coord[0]) && (coord[0] <= hi)
                && (lo <= coord[1]) && (coord[1] <= hi);
        });
    }
    bool noPointOnOrigin() {
        for (int i = 0; i < coords.size(); i++) {
            int x = coords[i][0];
            int y = coords[i][1];

            if ((x == 0) && (y == 0)) return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void BeforeTestCase() {
        coords.clear();
    }

    void SampleTestCase1() {
        Subtasks({1, 2});
        Input({
            "1 3",
            "2 4",
        });
        Output({
            "8.944271909999"
        });
    }

    void SampleTestCase2() {
        Subtasks({2});
        Input({
            "2 3",
            "2 2",
            "2 4"
        });
        Output({
            "5.656854249492"
        });
    }

    void SampleTestCase3() {
        Subtasks({2});
        Input({
            "4 4",
            "-2 -2",
            "2 -2",
            "-2 2",
            "2 2"
        });
        Output({
            "4"
        });
    }

    void TestGroup1() {
        Subtasks({1, 2});

        int delta = 40;

        // All 8 directions
        CASE(N = 1, M = 3, coords = getSingleCoord(0, delta));
        CASE(N = 1, M = 3, coords = getSingleCoord(0, -delta));
        CASE(N = 1, M = 3, coords = getSingleCoord(delta, 0));
        CASE(N = 1, M = 3, coords = getSingleCoord(-delta, 0));
        CASE(N = 1, M = 3, coords = getSingleCoord(delta, delta));
        CASE(N = 1, M = 3, coords = getSingleCoord(delta, -delta));
        CASE(N = 1, M = 3, coords = getSingleCoord(-delta, delta));
        CASE(N = 1, M = 3, coords = getSingleCoord(-delta, -delta));

        int bigDelta = MAX_COORD;
        CASE(N = 1, M = 3, coords = getSingleCoord(bigDelta, bigDelta));
    }

    void TestGroup2() {
        Subtasks({1, 2});

        int delta = 40;

        // Various polygon sides
        CASE(N = 1, M = 3, coords = getSingleCoord(0, delta));
        CASE(N = 1, M = 4, coords = getSingleCoord(0, -delta));
        CASE(N = 1, M = 5, coords = getSingleCoord(delta, 0));
        CASE(N = 1, M = 6, coords = getSingleCoord(-delta, 0));
        CASE(N = 1, M = 8, coords = getSingleCoord(delta, delta));
        CASE(N = 1, M = 9, coords = getSingleCoord(delta, -delta));
        CASE(N = 1, M = 10, coords = getSingleCoord(-delta, delta));
    }

    void TestGroup3() {
        Subtasks({2});

        for (int i = 3; i <= 10; i++) {
            CASE(N = 100, M = i, randomCase());
        }

        CASE(N = MAX_N, M = 3, randomCase());
        CASE(N = MAX_N, M = 10, randomCase());
    }

    void TestGroup4() {
        Subtasks({2});

        for (int i = 3; i <= 10; i++) {
            CASE(M = i, equiDistanceCase(20, 99, 101));
        }

        CASE(M = 6, equiDistanceCase(68, 285, 293), addCoordsNoise(2));
        CASE(M = 8, equiDistanceCase(68, 285, 293), addCoordsNoise(1));
    }

    void TestGroup5() {
        Subtasks({2});

        // Asteroid mepet2
        for (int i = 3; i <= 10; i++) {
            CASE(N = min(1000, MAX_N), M = i, asteroidBeltCase(MAX_COORD, 5));
        }
        CASE(N = MAX_N, M = 4, asteroidBeltCase(MAX_COORD, 5));
    }

    void TestGroup6() {
        Subtasks({2});

        // Asteroid renggang2
        for (int i = 3; i <= 10; i++) {
            CASE(N = min(1000, MAX_N), M = i, asteroidBeltCase(MAX_COORD, 2000));
        }
        CASE(N = MAX_N, M = 4, asteroidBeltCase(MAX_COORD, 2000));
    }

private:
    vector<int> getCoord(int x, int y) {
        vector<int> point;
        point.push_back(x);
        point.push_back(y);
        return point;
    }

    vector<vector<int>> getSingleCoord(int x, int y) {
        vector<vector<int>> result;

        result.push_back(getCoord(x, y));

        return result;
    }

    // Generate N distinct random points
    void randomCase() {
        set<vector<int>> points;

        while (points.size() < N) {
            vector<int> point;
            point.push_back(rnd.nextInt(MIN_COORD, MAX_COORD));
            point.push_back(rnd.nextInt(MIN_COORD, MAX_COORD));
            points.insert(point);
        }

        coords.clear();
        for (auto p : points) {
            coords.push_back(p);
        }
    }

    // (pA, pB, pC) must be phytagorean triplet
    void equiDistanceCase(ll pA, ll pB, ll pC) {
        assert(pA*pA + pB*pB == pC*pC);

        coords.clear();
        coords.push_back(getCoord(0, pC));

        coords.push_back(getCoord(pA, pB));
        coords.push_back(getCoord(pB, pA));

        coords.push_back(getCoord(pC, 0));

        coords.push_back(getCoord(-pB, pA));
        coords.push_back(getCoord(-pA, pB));

        coords.push_back(getCoord(-pC, 0));

        coords.push_back(getCoord(-pA, -pB));
        coords.push_back(getCoord(-pB, -pA));

        coords.push_back(getCoord(0, -pC));

        coords.push_back(getCoord(-pB, pA));
        coords.push_back(getCoord(-pA, pB));

        N = coords.size();
    }

    // Generate N points with distance to base coords roughly between [distance-noise, distance+noise]
    void asteroidBeltCase(int distance, int noise) {
        for (int i = 0; i < N; i++) {
            double rad = rnd.nextDouble(1.0) * 2*PI;

            int r = distance + rnd.nextInt(-noise, noise);
            int dx = (int)(distance * cos(rad));
            int dy = (int)(distance * sin(rad));

            int x = clamp(MIN_COORD, MAX_COORD, dx);
            int y = clamp(MIN_COORD, MAX_COORD, dy);
            coords.push_back(getCoord(x, y));
        }
    }

    void addCoordsNoise(int maxNoise) {
        for (int i = 0; i < coords.size(); i++) {
            coords[i][0] += rnd.nextInt(-maxNoise, maxNoise);
            coords[i][1] += rnd.nextInt(-maxNoise, maxNoise);

            // Normalize
            coords[i][0] = clamp(MIN_COORD, MAX_COORD, coords[i][0]);
            coords[i][1] = clamp(MIN_COORD, MAX_COORD, coords[i][1]);
        }
    }

    int clamp(int minValue, int maxValue, int value) {
        if (value < minValue) return minValue;
        if (value > maxValue) return maxValue;
        return value;
    }
};
