#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    string S;
    int N, K;

    int res;

    void InputFormat() {
        LINE(S, N, K);
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
        CONS(validString());
        CONS(1 <= N && N <= 100);
        CONS(1 <= K && K <= 26);
    }

    void Subtask1() {
        CONS(S.size() == 2);
    }

    void Subtask2() {
        CONS(1 <= S.size() && S.size() <= 10);
    }

private:
    bool validString() {
        for (char c : S) {
            if (c < 'a' || c > 'z') return false;
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
