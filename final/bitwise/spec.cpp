#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N, A, B, C;

    vector<int> res;

    void InputFormat() {
        LINE(N, A, B, C);
    }

    void OutputFormat() {
        LINES(res);
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
        CONS(0 <= A && A <= numeric_limits<int>::max());
        CONS(0 <= B && B <= numeric_limits<int>::max());
        CONS(0 <= C && C <= numeric_limits<int>::max());
    }

    void Subtask1() {
        CONS(N == 2);
    }

    void Subtask2() {
        CONS(N == 100000);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void TestGroup1() {
        Subtasks({1, 2});
    }
};
