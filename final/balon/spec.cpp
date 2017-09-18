#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

const int MIN_COORD = 0;
const int MAX_COORD = 1000000000;

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
    void TestGroup1() {
        Subtasks({1, 2});
    }
};
