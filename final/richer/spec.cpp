#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

typedef long long ll;

const int MIN_RICHNESS = 1;
const int MAX_RICHNESS = 100000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N;
    vector<int> R; // Richness
    vector<int> P; // Parent

    ll res;

    void InputFormat() {
        LINE(N);
        LINE(P % SIZE(N-1));
        LINE(R % SIZE(N));
    }

    void OutputFormat() {
        LINE(res);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 10);
    }

    void Constraints() {
        CONS(eachElementBetween(R, MIN_RICHNESS, MAX_RICHNESS));
        CONS(isTree());
    }

    void Subtask1() {
        CONS(1 <= N && N <= 1000);
    }

    void Subtask2() {
        CONS(1 <= N && N <= 100000);
    }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        return all_of(v.begin(), v.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }

    bool isTree() {
        for (int i = 2; i <= N; i++) {
            if ((P[i-2] < 1) || (P[i-2] >= i)) return false;
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
