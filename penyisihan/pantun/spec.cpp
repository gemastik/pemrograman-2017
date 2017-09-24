#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

const int MIN_VALUE = 1;
const int MAX_VALUE = 100;
const int MAX_INPUT_SIZE = 100000;

template<typename T>
inline bool inRange(const T& z, const T& lb, const T& ub) {
    return lb <= z && z <= ub;
}

class ProblemSpec : public BaseProblemSpec {
protected:

    int N;
    vector<int> A, B;
    long long ans;

    void InputFormat() {
        LINE(N);
        LINE(A % SIZE(N));
        LINE(B % SIZE(N));
    }

    void OutputFormat() {
        LINE(ans);
    }

    void Constraints() {
        CONS(all_of(A.begin(),
                    A.end(),
                    [](const int i) { return inRange(i, MIN_VALUE, MAX_VALUE); }
        ));
        CONS(all_of(B.begin(),
                    B.end(),
                    [](const int i) { return inRange(i, MIN_VALUE, MAX_VALUE); }
        ));
    }

    void Subtask1() {
        CONS(N == 1);
    }

    void Subtask2() {
        CONS(inRange(N, 1, MAX_INPUT_SIZE));
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1, 2});
        Input({
            "1",
            "3",
            "5"
        });
        Output({
            "8"
        });
    }

    void SampleTestCase2() {
        Subtasks({2});
        Input({
            "2",
            "1 2",
            "3 4"
        });
        Output({
            "20"
        });
    }

    void BeforeTestCase() {
        A.clear();
        B.clear();
    }

    void TestGroup1() {
        Subtasks({1, 2});
        // ¯\_(ツ)_/¯
        CASE(N = 1, A = {1}, B = {1});
        CASE(N = 1, A = {100}, B = {100});
        CASE(N = 1, A = {1}, B = {100});
        CASE(N = 1, A = {100}, B = {1});
    }

    void TestGroup2() {
        Subtasks({2});
        CASE(
                N = MAX_INPUT_SIZE,
                A = generateVectorWithRandomValue(MAX_VALUE, MAX_VALUE, N),
                B = generateVectorWithRandomValue(MAX_VALUE, MAX_VALUE, N)
        );
        CASE(
                N = MAX_INPUT_SIZE,
                A = generateVectorWithRandomValue(1, MAX_VALUE, N),
                B = generateVectorWithRandomValue(1, MAX_VALUE, N)
        );
        CASE(
                N = MAX_INPUT_SIZE,
                A = generateVectorWithRandomValue(1, MAX_VALUE, N),
                B = generateVectorWithRandomValue(MAX_VALUE, MAX_VALUE, N)
        );
        CASE(
                N = MAX_INPUT_SIZE,
                A = generateVectorWithRandomValue(MAX_VALUE, MAX_VALUE, N),
                B = generateVectorWithRandomValue(1, MAX_VALUE, N)
        );
    }

    vector<int> generateVectorWithRandomValue(int lb, int ub, int N) {
        vector<int> result = {};
        for (int i = 0; i < N; ++i) {
            result.push_back(rnd.nextInt(lb, ub));
        }
        return result;
    }
};
