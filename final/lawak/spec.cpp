#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N, M;
    vector<int> P; // Humour percentage
    vector<int> U, V;
    int Q;
    vector<int> X, H; // node, humour

    vector<int> res;

    void InputFormat() {
        LINE(N, M);
        LINE(P % SIZE(N));
        LINES(U, V) % SIZE(M);
        LINE(Q);
        LINES(X, H) % SIZE(Q);
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
        CONS(eachElementBetween(P, 0, 100));
        CONS(eachElementBetween(U, 1, N));
        CONS(eachElementBetween(V, 1, N));
        CONS(noSelfLoop());

        CONS(eachElementBetween(X, 1, N));
        CONS(eachElementBetween(H, 0, 100));
    }

    void Subtask1() {
        CONS(1 <= N && N <= 1000);
        CONS(1 <= M && M <= 1000);
        CONS(1 <= Q && Q <= 1000);

    }

    void Subtask2() {
        CONS(1 <= N && N <= 50000);
        CONS(1 <= M && M <= 50000);
        CONS(1 <= Q && Q <= 100000);
    }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        return all_of(v.begin(), v.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }

    bool noSelfLoop() {
        for (int i = 0; i < U.size(); i++) {
            if (U[i] == V[i]) return false;
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
