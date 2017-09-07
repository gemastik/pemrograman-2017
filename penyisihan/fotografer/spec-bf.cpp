#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

const int MAX_MALE = 1000;
const int MAX_FEMALE = 1000;
const int MAX_TOTAL_HUMAN = 20;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int A, B, K;
    string res;

    void InputFormat() {
        LINE(A, B, K);
    }

    void OutputFormat() {
        LINE(res); // "mustahil" if there is no solution
    }

    void StyleConfig() {
        CustomScorer();
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 2000);
    }

    void Constraints() {
        CONS(0 <= A && A <= MAX_MALE);
        CONS(1 <= B && B <= MAX_FEMALE);
        CONS(1 <= K && K <= B);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void TestGroup1() {
        for (int i = 0; i <= 10; i++) {
            for (int j = 1; j <= 10; j++) {
                for (int k = 1; k <= j; k++) {
                    CASE(A = i, B = j, K = k);
                }
            }
        }
    }
};
