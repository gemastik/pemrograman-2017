#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

template<typename T>
inline bool inRange(const T& z, const T& lb, const T& ub) { return lb <= z && z <= ub; }

const int MAX_N = 500;
const int MAX_M = 50000;
const int MAX_EDGE_COST = 2000000000 / MAX_N;

class ProblemSpec : public BaseProblemSpec {
    using vi = vector<int>;

protected:
    int T;

    int N, M;
    vi U, V, W;

    int ANS_COST, ANS_NUM_CIRCUIT;
    vector<vi> ANS_CIRCUITS;
    vi ANS_CIRCUITS_SIZE;

    void InputFormat() {
        LINE(N, M);
        LINES(U, V, W) % SIZE(M);
    }

    void OutputFormat() {
        LINE(ANS_COST, ANS_NUM_CIRCUIT);
        LINES(ANS_CIRCUITS_SIZE, ANS_CIRCUITS) % SIZE(ANS_NUM_CIRCUIT);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(inRange(T, 1, 5));
    }

    void Constraints() {
        CONS(inRange(N, 1, MAX_N));
        CONS(inRange(M, 1, MAX_M));
        CONS(all_of(W.begin(), W.end(), [&](int w) { return inRange(w, 1, MAX_EDGE_COST); }));
        CONS(all_of(U.begin(), U.end(), [&](int u) { return inRange(u, 1, N); }));
        CONS(all_of(V.begin(), V.end(), [&](int v) { return inRange(v, 1, N); }));
    }

    void Subtask1() {
        CONS(inRange(N, 1, 10));
    }

    void Subtask2() {
        CONS(inRange(N, 1, MAX_N));
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
