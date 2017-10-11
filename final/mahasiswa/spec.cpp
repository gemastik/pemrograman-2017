#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

typedef long long ll;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N, K;
    vector<int> M;

    ll result;

    void InputFormat() {
        LINE(N, K);
        LINE(M % SIZE(N));
    }

    void OutputFormat() {
        LINE(result);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 10);
    }

    void Constraints() {
        CONS(eachElementBetween(M, 1, 100000));
        CONS(1 <= K && K <= N);
    }

    void Subtask1() {
        CONS(1 <= N && N <= 2);
    }

    void Subtask2() {
        CONS(1 <= N && N <= 100000);
    }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        return all_of(v.begin(), v.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void TestGroup1() {
        Subtasks({1, 2});
    }
};
