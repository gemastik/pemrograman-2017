#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

const int QUERY_ADD = 1;
const int QUERY_REMOVE = 2;
const int QUERY_ASK = 3;
const int MIN_X = 0;
const int MAX_X = 1000 * 1000 * 1000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N;
    vector<vector<int>> queries; // <type [, Xmin, Xmax]>

    vector<int> res;

    void InputFormat() {
        LINE(N);
        LINES(queries) % SIZE(N);
    }

    void OutputFormat() {
        LINES(res);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 10);
    }

    void Constraints() {
        CONS(validQueries());
    }

    void Subtask1() {
        CONS(1 <= N && N <= 1000);

    }

    void Subtask2() {
        CONS(1 <= N && N <= 100000);
    }

private:
    bool validQueries() {
        for (int i = 0; i < queries.size(); i++) {
            if (queries.size() < 1) return false;

            int type = queries[i][0];

            if (type == QUERY_ASK) {
                if (queries.size() != 1) return false;

            } else if ((type == QUERY_ADD) || (type == QUERY_REMOVE)) {
                if (queries.size() != 3) return false;
                int xMin = queries[i][1];
                int xMax = queries[i][2];

                if (xMin > xMax) return false;
                if (xMin < MIN_X) return false;
                if (xMax > MAX_X) return false;

            } else {
                // Invalid type
                return false;
            }
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
