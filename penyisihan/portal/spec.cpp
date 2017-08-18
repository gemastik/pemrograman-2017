#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int R, C, N;
    vector<vector<char>> G;

    int res;

    void InputFormat() {
        LINE(R, C, N);
        GRID(G) % SIZE(R, C);
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
        CONS(2 <= R && R <= 100);
        CONS(1 <= C && C <= 26);
        CONS(validGrid());
    }

    void Subtask1() {
        CONS(N == 1);
    }

    void Subtask2() {
        CONS(1 <= N && N <= C);
    }

private:
    bool validGrid() {
        set<char> portals;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                char c = G[i][j];

                if (!isAlphanumeric(c)) return false;

                if (i == 0 && c != '0') return false;

                if (c >= 'A' && c <= 'Z') {
                    if (c - 'A' >= N) return false;
                    if (portals.insert(c).second) return false;
                }
            }
        }
        return portals.size() == N;
    }

    bool isAlphanumeric(char c) {
        return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
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
