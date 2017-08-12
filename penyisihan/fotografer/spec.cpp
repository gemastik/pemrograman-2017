#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

const int MAX_MALE = 1000;
const int MAX_FEMALE = 1000;

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
        CONS(1 <= T && T <= 20);
    }

    void Constraints() {
        CONS(1 <= B && B <= MAX_FEMALE);
        CONS(1 <= K && K <= B);
    }

    void Subtask1() {
        CONS(0 <= A && A <= 1);
    }

    void Subtask2() {
        CONS(0 <= A && A <= MAX_MALE);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1, 2});
    }

    // Exhaustive for small
    void TestGroup1() {
        Subtasks({1, 2});

        // Combination of A = [0, 2], B = [1, 4], K = [1, B]
        CASE(A = 0, B = 1, K = 1);
        CASE(A = 0, B = 2, K = 1);
        CASE(A = 0, B = 2, K = 2);
        CASE(A = 0, B = 3, K = 1);
        CASE(A = 0, B = 3, K = 2);
        CASE(A = 0, B = 3, K = 3);
        CASE(A = 0, B = 4, K = 1);
        CASE(A = 0, B = 4, K = 2);
        CASE(A = 0, B = 4, K = 3);
        CASE(A = 0, B = 4, K = 4);
        CASE(A = 1, B = 1, K = 1);
        CASE(A = 1, B = 2, K = 1);
        CASE(A = 1, B = 2, K = 2);
        CASE(A = 1, B = 3, K = 1);
        CASE(A = 1, B = 3, K = 2);
        CASE(A = 1, B = 3, K = 3);
        CASE(A = 1, B = 4, K = 1);
        CASE(A = 1, B = 4, K = 2);
        CASE(A = 1, B = 4, K = 3);
        CASE(A = 1, B = 4, K = 4);

    }

    // Corners for small
    void TestGroup2() {
        Subtasks({1, 2});

        // Mustahil
        CASE(A = 0, B = MAX_FEMALE, K = 1);

        // Large cases
        CASE(A = 0, B = MAX_FEMALE, K = MAX_FEMALE);
        CASE(A = 0, B = MAX_FEMALE, K = MAX_FEMALE - 1);
        CASE(A = 1, B = MAX_FEMALE, K = MAX_FEMALE);
        CASE(A = 1, B = MAX_FEMALE, K = (MAX_FEMALE + 1) / 2);
        CASE(A = 1, B = MAX_FEMALE, K = MAX_FEMALE - 1);
        CASE(A = 1, B = MAX_FEMALE - 1, K = MAX_FEMALE - 1);
        CASE(A = 1, B = MAX_FEMALE - 1, K = MAX_FEMALE / 2);
        CASE(A = 1, B = MAX_FEMALE - 1, K = MAX_FEMALE / 2 - 1);

        // Misc.
        CASE(A = 1, B = 4, K = 2);
        CASE(A = 1, B = 5, K = 2); // mustahil
        CASE(A = 1, B = 5, K = 3);
        CASE(A = 1, B = 5, K = 4);

        // Random
        CASE(A = 1, B = rnd.nextInt(0, MAX_FEMALE), K = rnd.nextInt(0, B));
        CASE(A = 1, B = rnd.nextInt(0, MAX_FEMALE), K = rnd.nextInt(0, B));
    }

    // Exhaustive for large, pt. 1
    void TestGroup3() {
        Subtasks({2});

        // Combination of A = [3, 6], B = [2, 6], K = [2, B]
        CASE(A = 3, B = 2, K = 2);
        CASE(A = 3, B = 3, K = 2);
        CASE(A = 3, B = 3, K = 3);
        CASE(A = 3, B = 4, K = 2);
        CASE(A = 3, B = 4, K = 3);
        CASE(A = 3, B = 4, K = 4);
        CASE(A = 3, B = 5, K = 2);
        CASE(A = 3, B = 5, K = 3);
        CASE(A = 3, B = 5, K = 4);
        CASE(A = 3, B = 5, K = 5);
        CASE(A = 3, B = 6, K = 2);
        CASE(A = 3, B = 6, K = 3);
        CASE(A = 3, B = 6, K = 4);
        CASE(A = 3, B = 6, K = 5);
        CASE(A = 3, B = 6, K = 6);
        CASE(A = 4, B = 2, K = 2);
        CASE(A = 4, B = 3, K = 2);
        CASE(A = 4, B = 3, K = 3);
        CASE(A = 4, B = 4, K = 2);
        CASE(A = 4, B = 4, K = 3);
    }

    // Exhaustive for large, pt. 2
    void TestGroup4() {
        Subtasks({2});

        CASE(A = 4, B = 4, K = 4);
        CASE(A = 4, B = 5, K = 2);
        CASE(A = 4, B = 5, K = 3);
        CASE(A = 4, B = 5, K = 4);
        CASE(A = 4, B = 5, K = 5);
        CASE(A = 4, B = 6, K = 2);
        CASE(A = 4, B = 6, K = 3);
        CASE(A = 4, B = 6, K = 4);
        CASE(A = 4, B = 6, K = 5);
        CASE(A = 4, B = 6, K = 6);
        CASE(A = 5, B = 2, K = 2);
        CASE(A = 5, B = 3, K = 2);
        CASE(A = 5, B = 3, K = 3);
        CASE(A = 5, B = 4, K = 2);
        CASE(A = 5, B = 4, K = 3);
        CASE(A = 5, B = 4, K = 4);
        CASE(A = 5, B = 5, K = 2);
        CASE(A = 5, B = 5, K = 3);
        CASE(A = 5, B = 5, K = 4);
        CASE(A = 5, B = 5, K = 5);
    }

    // Exhaustive for large, pt. 3
    void TestGroup5() {
        Subtasks({2});

        CASE(A = 5, B = 6, K = 2);
        CASE(A = 5, B = 6, K = 3);
        CASE(A = 5, B = 6, K = 4);
        CASE(A = 5, B = 6, K = 5);
        CASE(A = 5, B = 6, K = 6);
        CASE(A = 6, B = 2, K = 2);
        CASE(A = 6, B = 3, K = 2);
        CASE(A = 6, B = 3, K = 3);
        CASE(A = 6, B = 4, K = 2);
        CASE(A = 6, B = 4, K = 3);
        CASE(A = 6, B = 4, K = 4);
        CASE(A = 6, B = 5, K = 2);
        CASE(A = 6, B = 5, K = 3);
        CASE(A = 6, B = 5, K = 4);
        CASE(A = 6, B = 5, K = 5);
        CASE(A = 6, B = 6, K = 2);
        CASE(A = 6, B = 6, K = 3);
        CASE(A = 6, B = 6, K = 4);
        CASE(A = 6, B = 6, K = 5);
        CASE(A = 6, B = 6, K = 6);
    }

    // Corners for large
    void TestGroup6() {
        Subtasks({2});

        CASE(A = MAX_MALE, B = MAX_MALE, K = 1);
        CASE(A = MAX_MALE, B = MAX_MALE, K = 1);
        CASE(A = MAX_MALE, B = MAX_MALE, K = 2);
        CASE(A = MAX_MALE, B = MAX_MALE / 2 + 1, K = 1); // LPLPLPLPLLP...
        CASE(A = MAX_MALE - 1, B = MAX_MALE / 2 + 1, K = 1);
        CASE(A = MAX_MALE, B = MAX_MALE / 2, K = 1); // LPLPLLPLLP...
        CASE(A = MAX_MALE - 1, B = MAX_MALE / 2, K = 1);
        CASE(A = MAX_MALE, B = MAX_MALE / 2 - 1, K = 1); // LLPLLPLLP...
        CASE(A = MAX_MALE - 1, B = MAX_MALE / 2 - 1, K = 1);
        CASE(A = MAX_MALE, B = MAX_MALE / 2 - 2, K = 1); // Muschtahil
        CASE(A = MAX_MALE, B = MAX_MALE, K = MAX_MALE);
        CASE(A = MAX_MALE, B = 1, K = 1);

        // Nonsense, copied-from-above-then-modified cases below
        CASE(A = MAX_MALE - 1, B = MAX_MALE / 2 + 1, K = 1); // LPLPLPLPLLP...
        CASE(A = MAX_MALE - 2, B = MAX_MALE / 2 + 1, K = 1);
        CASE(A = MAX_MALE - 1, B = MAX_MALE / 2, K = 1); // LPLPLLPLLP...
        CASE(A = MAX_MALE - 2, B = MAX_MALE / 2, K = 1);
        CASE(A = MAX_MALE - 1, B = MAX_MALE / 2 - 1, K = 1); // LLPLLPLLP...
        CASE(A = MAX_MALE - 2, B = MAX_MALE / 2 - 1, K = 1);

        // Large cases?
        CASE(A = MAX_MALE / 100, B = MAX_FEMALE, K = 100); // LPPP...{100 P}..PLPPP...
        CASE(A = MAX_MALE / 100, B = MAX_FEMALE - 5, K = 100); // LPPP...{100 P}..PLPPP...
    }
};
