#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int Tc;

    int N;
    vector<int> T;
    vector<int> C;
    vector<int> indegree;
    vector<vector<int>> incomingNodes;

    string res;

    void InputFormat() {
        LINE(N);
        LINES(T, C, indegree, incomingNodes) % SIZE(N);
    }

    void OutputFormat() {
        LINE(res);
    }

    void MultipleTestCasesConfig() {
        Counter(Tc);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= Tc && Tc <= 10);
    }

    void Constraints() {
        CONS(eachElementBetween(T, 1, 100000));
        CONS(eachElementBetween(C, 1, 100000));
        CONS(validIncomingNodes());
        CONS(dagConnected());
    }

    void Subtask1() {
        CONS(1 <= N && N <= 18);
    }

    void Subtask2() {
        CONS(1 <= N && N <= 500);
    }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        return all_of(v.begin(), v.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }

    bool validIncomingNodes() {
        for (int i = 0; i < N; i++) {
            // Consistency check
            if (indegree[i] != incomingNodes[i].size()) return false;

            // Uniqueness check
            set<int> uniqueNodes(incomingNodes[i].begin(), incomingNodes[i].end());
            if (uniqueNodes.size() != incomingNodes[i].size()) return false;

            // Validity check
            if (!eachElementBetween(incomingNodes[i], 0, N-1)) return false;
        }
        return true;
    }

    bool dagConnected() {
        return true; // TODO
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void TestGroup1() {
        Subtasks({1, 2});
    }
};
