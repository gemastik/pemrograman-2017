#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

template<typename T>
inline bool inRange(const T& z, const T& lb, const T& ub) { return lb <= z && z <= ub; }

const int MAX_N = 500;
const int SMALL_MAX_N = 12;
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
    vi LOOP_COST;

    string MUSTAHIL;

    void InputFormat() {
        LINE(N, M);
        LINE(LOOP_COST % SIZE(N));
        LINES(U, V, W) % SIZE(M);
    }

    void OutputFormat1() {
        LINE(ANS_COST, ANS_NUM_CIRCUIT);
        LINES(ANS_CIRCUITS_SIZE, ANS_CIRCUITS) % SIZE(ANS_NUM_CIRCUIT);
    }

    void OutputFormat2() {
        LINE(MUSTAHIL);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(inRange(T, 1, 5));
    }

    void Constraints() {
        CONS(inRange(N, 1, MAX_N));
        CONS(inRange(M, 0, MAX_M));
        CONS(LOOP_COST.size() == N);
        CONS(all_of(LOOP_COST.begin(), LOOP_COST.end(), [&](int w) { return inRange(w, 1, MAX_EDGE_COST); }));
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
