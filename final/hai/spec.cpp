#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

typedef long long ll;

constexpr ll MILLION = 1000 * 1000;
const ll MAX_HAI_LENGTH = MILLION * MILLION * MILLION; // 10^18

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N;
    vector<ll> hais;

    int res;

    void InputFormat() {
        LINE(N);
        LINES(hais) % SIZE(N);
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
        CONS(1 <= N && N <= 100000);
    }

    void Subtask1() {
        CONS(eachElementBetween(hais, 1, 100));
    }

    void Subtask2() {
        CONS(eachElementBetween(hais, 1, MAX_HAI_LENGTH));
    }

private:
    bool eachElementBetween(const vector<ll>& v, ll lo, ll hi) {
        return all_of(v.begin(), v.end(), [lo, hi](ll a) {return lo <= a && a <= hi;});
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void TestGroup1() {
        Subtasks({1, 2});
    }
};
