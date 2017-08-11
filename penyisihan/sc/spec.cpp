#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N;
    vector<int> S;
    vector<int> P;
    vector<vector<int>> C;

    int res;

    void InputFormat() {
        LINE(N);
        LINE(S % SIZE(N));
        LINES(P, C) % SIZE(N);
    }

    void OutputFormat() {
        LINE(res);
    }

    void Constraints() {
        CONS(validCompanies());
    }

    void Subtask1() {
        CONS(1 <= N && N <= 10);
        CONS(eachElementBetween(S, 1, 2));
        CONS(eachElementBetween(P, 0, 2));
    }

    void Subtask2() {
        CONS(1 <= N && N <= 50);
        CONS(eachElementBetween(S, 1, 50));
        CONS(eachElementBetween(P, 0, 50));
    }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        return all_of(v.begin(), v.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }

    bool validCompanies() {
        for (int i = 0; i < N; i++) {
            if (P[i] != C[i].size()) return false;

            for (int c : C[i]) {
                if (c < 1 || c > 50) return false;
            }
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void TestGroup1() {
        Subtasks({1, 2});

    }

    void TestGroup2() {
        Subtasks({2});

    }
};
