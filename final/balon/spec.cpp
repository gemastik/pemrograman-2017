#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

const int MIN_COORD = 0;
const int MAX_COORD = 1000000000;
const double PI = acos(-1.0);

typedef long long ll;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N, M;
    int baloonX, baloonY;
    vector<vector<int>> coords;

    double res;

    void InputFormat() {
        LINE(N, M);
        LINE(baloonX, baloonY);
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
        CONS(coords.size() == N);
        CONS(completeCoords());
        CONS(coordsBetween(MIN_COORD, MAX_COORD));
        CONS(baloonCenterIsNotOnPoint());
        CONS(MIN_COORD <= baloonX && baloonX <= MAX_COORD);
        CONS(MIN_COORD <= baloonY && baloonY <= MAX_COORD);
    }

    void Subtask1() {
        CONS(N == 1);
    }

    void Subtask2() {
        CONS(1 <= N && N <= 100000);
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
    bool baloonCenterIsNotOnPoint() {
        for (int i = 0; i < coords.size(); i++) {
            int x = coords[i][0];
            int y = coords[i][1];

            if ((x == baloonX) && (y == baloonY)) return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void BeforeTestCase() {
        coords.clear();
    }

    void TestGroup1() {
        Subtasks({1, 2});

        int baseX = 50;
        int baseY = 60;
        int delta = 40;

        // All 8 directions
        CASE(N = 1, M = 3, baloonX = baseX, baloonY = baseY, coords = getSingleCoord(baseX, baseY + delta));
        CASE(N = 1, M = 3, baloonX = baseX, baloonY = baseY, coords = getSingleCoord(baseX, baseY - delta));
        CASE(N = 1, M = 3, baloonX = baseX, baloonY = baseY, coords = getSingleCoord(baseX + delta, baseY));
        CASE(N = 1, M = 3, baloonX = baseX, baloonY = baseY, coords = getSingleCoord(baseX - delta, baseY));
        CASE(N = 1, M = 3, baloonX = baseX, baloonY = baseY, coords = getSingleCoord(baseX + delta, baseY + delta));
        CASE(N = 1, M = 3, baloonX = baseX, baloonY = baseY, coords = getSingleCoord(baseX + delta, baseY - delta));
        CASE(N = 1, M = 3, baloonX = baseX, baloonY = baseY, coords = getSingleCoord(baseX - delta, baseY + delta));
        CASE(N = 1, M = 3, baloonX = baseX, baloonY = baseY, coords = getSingleCoord(baseX - delta, baseY - delta));

        // Overflow trap
        int bigDelta = 900 * 1000 * 1000;
        CASE(N = 1, M = 3, baloonX = baseX, baloonY = baseY, coords = getSingleCoord(baseX + bigDelta, baseY + bigDelta));
    }

    void TestGroup2() {
        Subtasks({1, 2});

        int baseX = 50;
        int baseY = 60;
        int delta = 40;

        // Various polygon sides
        CASE(N = 1, M = 3, baloonX = baseX, baloonY = baseY, coords = getSingleCoord(baseX, baseY + delta));
        CASE(N = 1, M = 4, baloonX = baseX, baloonY = baseY, coords = getSingleCoord(baseX, baseY - delta));
        CASE(N = 1, M = 5, baloonX = baseX, baloonY = baseY, coords = getSingleCoord(baseX + delta, baseY));
        CASE(N = 1, M = 6, baloonX = baseX, baloonY = baseY, coords = getSingleCoord(baseX - delta, baseY));
        CASE(N = 1, M = 8, baloonX = baseX, baloonY = baseY, coords = getSingleCoord(baseX + delta, baseY + delta));
        CASE(N = 1, M = 9, baloonX = baseX, baloonY = baseY, coords = getSingleCoord(baseX + delta, baseY - delta));
        CASE(N = 1, M = 10, baloonX = baseX, baloonY = baseY, coords = getSingleCoord(baseX - delta, baseY + delta));
    }

    void TestGroup3() {
        Subtasks({2});

        for (int i = 3; i <= 10; i++) {
            CASE(N = 100, M = i, randomCase());
        }

        CASE(N = 50000, M = 3, randomCase());
        CASE(N = 50000, M = 10, randomCase());
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

        for (int i = 3; i <= 10; i++) {
            CASE(N = 1000, M = i, asteroidBeltCase(100000, 5));
        }
        CASE(N = 30000, M = 4, asteroidBeltCase(100000, 5));
    }

    void TestGroup6() {
        Subtasks({2});

        for (int i = 3; i <= 10; i++) {
            CASE(N = 1000, M = i, asteroidBeltCase(100000, 1000));
        }
        CASE(N = 30000, M = 4, asteroidBeltCase(100000, 1000));
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

    // Generate N+1 distinct random points, assign 1 of them as baloon coordinate
    void randomCase() {
        set<vector<int>> points;

        while (points.size() < N + 1) {
            vector<int> point;
            point.push_back(rnd.nextInt(0, MAX_COORD));
            point.push_back(rnd.nextInt(0, MAX_COORD));
            points.insert(point);
        }

        coords.clear();
        for (auto p : points) {
            coords.push_back(p);
        }

        baloonX = coords.back()[0];
        baloonY = coords.back()[1];
        coords.pop_back();
    }

    // (pA, pB, pC) must be phytagorean triplet
    void equiDistanceCase(ll pA, ll pB, ll pC) {
        assert(pA*pA + pB*pB == pC*pC);

        int baseX = rnd.nextInt(pC, MAX_COORD - pC);
        int baseY = rnd.nextInt(pC, MAX_COORD - pC);

        coords.clear();
        coords.push_back(getCoord(baseX, baseY + pC));

        coords.push_back(getCoord(baseX + pA, baseY + pB));
        coords.push_back(getCoord(baseX + pB, baseY + pA));

        coords.push_back(getCoord(baseX + pC, baseY));

        coords.push_back(getCoord(baseX - pB, baseY + pA));
        coords.push_back(getCoord(baseX - pA, baseY + pB));

        coords.push_back(getCoord(baseX - pC, baseY));

        coords.push_back(getCoord(baseX - pA, baseY - pB));
        coords.push_back(getCoord(baseX - pB, baseY - pA));

        coords.push_back(getCoord(baseX - pC, baseY));

        coords.push_back(getCoord(baseX - pB, baseY + pA));
        coords.push_back(getCoord(baseX - pA, baseY + pB));

        N = coords.size();
    }

    // Generate N points with distance to base coords roughly between [distance-noise, distance+noise]
    void asteroidBeltCase(int distance, int noise) {
        int baseX = rnd.nextInt(distance + noise, MAX_COORD - distance - noise);
        int baseY = rnd.nextInt(distance + noise, MAX_COORD - distance - noise);

        for (int i = 0; i < N; i++) {
            double rad = rnd.nextDouble(1.0) * 2*PI;

            int r = distance + rnd.nextInt(-noise, noise);
            int dx = (int)(distance * cos(rad));
            int dy = (int)(distance * sin(rad));

            int x = clamp(0, MAX_COORD, baseX + dx);
            int y = clamp(0, MAX_COORD, baseY + dy);
            coords.push_back(getCoord(x, y));
        }
    }

    void addCoordsNoise(int maxNoise) {
        for (int i = 0; i < coords.size(); i++) {
            coords[i][0] += rnd.nextInt(-maxNoise, maxNoise);
            coords[i][1] += rnd.nextInt(-maxNoise, maxNoise);

            // Normalize
            coords[i][0] = clamp(0, MAX_COORD, coords[i][0]);
            coords[i][1] = clamp(0, MAX_COORD, coords[i][1]);
        }
    }

    int clamp(int minValue, int maxValue, int value) {
        if (value < minValue) return minValue;
        if (value > maxValue) return maxValue;
        return value;
    }
};
