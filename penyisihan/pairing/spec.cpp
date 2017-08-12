#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N, M;
    vector<int> A, B, C;

    long long res;

    void InputFormat() {
        LINE(N, M);
        LINE(A % SIZE(N));
        LINE(B % SIZE(N));
        LINE(C % SIZE(M));
    }

    void OutputFormat() {
        LINE(res);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 5);
    }

    void Constraints() {
        CONS(1 <= N && N <= 100000);
        CONS(eachElementBetween(A, 0, 1000000));
        CONS(eachElementBetween(B, 0, 1000000));
        CONS(eachElementBetween(C, 0, 1000000));
    }

    void Subtask1() {
        CONS(1 <= M && M <= 1000);
    }

    void Subtask2() {
        CONS(1 <= M && M <= 100000);
    }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        return all_of(v.begin(), v.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1, 2});
        Input({
            "4 2",
            "3 14 15 9",
            "26 53 58 97",
            "93 2"
        });
        Output({
            "161"
        });
    }

    void SampleTestCase2() {
        Subtasks({1, 2});
        Input({
            "4 3",
            "3 14 15 9",
            "26 53 58 97",
            "93 2 38"
        });
        Output({
            "171"
        });
    }

    void TestGroup1() {
        Subtasks({1, 2});

    }

    void TestGroup2() {
        Subtasks({2});

    }
};
