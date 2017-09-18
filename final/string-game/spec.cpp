#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int K;
    vector<string> words;

    string res;

    void InputFormat() {
        LINE(K);
        LINES(words) % SIZE(K);
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
        CONS(1 <= K && K <= 100000);
        CONS(eachElementNonDecreasing(words));
    }

    void Subtask1() {
        CONS(eachElementLengthBetween(words, 1, 1));
    }

    void Subtask2() {
        CONS(eachElementLengthBetween(words, 1, 8));
    }

private:
    bool eachElementLengthBetween(const vector<string>& v, int lo, int hi) {
        return all_of(v.begin(), v.end(), [lo, hi](string a) {return lo <= a.length() && a.length() <= hi;});
    }

    bool eachElementNonDecreasing(const vector<string>& v) {
        return all_of(v.begin(), v.end(), [](string a) {
            for (int i = 1; i < a.length(); i++) {
                if (a[i-1] > a[i]) return false;
            }
            return true;
        });
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void TestGroup1() {
        Subtasks({1, 2});
    }
};
