#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

template <typename T>
bool inRange(const T& o, const T& a, const T& b) { return a <= o && o <= b; }

using ll = long long;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;
    int N, M;
    vector<int> X, K;
    vector<ll> RES;

    void InputFormat() {
		LINE(N, M);
		LINES(X, K) % SIZE(M);
    }

    void OutputFormat() {
        LINE(RES);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 5);
    }

    void Constraints() {
		CONS(eachElementBetween(X, 1, N));
        CONS(eachElementBetween(K, 1, 50000));
    }

    void Subtask1() {
		CONS(inRange(N, 1, 1000));
		CONS(inRange(M, 1, 1000));
    }

    void Subtask2() {
		CONS(inRange(N, 1, 50000));
		CONS(inRange(M, 1, 50000));
    }

private:
    template <typename T>
    bool eachElementBetween(const vector<T>& A, const T& lo, const T& hi) {
        return all_of(A.begin(), A.end(), [lo, hi](const T& a) {return inRange(a, lo, hi);});
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1, 2});
        Input({
            "7 4",
            "4 3",
			"1 2",
			"5 1",
			"4 2"
        });
        Output({"2 2 3 5 4 1 0"});
    }

    void SampleTestCase2() {
        Subtasks({1, 2});
        Input({
            "2 2",
			"1 100",
			"2 100"
        });
        Output({"199 199"});
    }

    void TestGroup1() {
        Subtasks({1, 2});

        CASE(N = 1, M = 1, X = {1}, K = {42});
        CASE(N = 5, M = 5, X = {1, 2, 3, 4, 5}, K = {1, 1, 1, 1, 1});
        CASE(N = 500, M = 100, randomCase());
        CASE(N = 1000, M = 500, randomSmallTaburanCase());
        CASE(N = 1000, M = 1000, randomKillerCase());
    }

    void TestGroup2() {
        Subtasks({2});

        CASE(N = 100, M = 3000, randomSmallTaburanCase());
        CASE(N = 100, M = 50000, randomCase());
        CASE(N = 100, M = 50000, randomKillerCase());
        CASE(N = 100, M = 50000, randomSmallTaburanCase());
        CASE(N = 10000, M = 10000, randomCase());
    }

    void TestGroup3() {
        Subtasks({2});

        CASE(N = 50000, M = 50000, randomCase());
        CASE(N = 50000, M = 50000, randomCase());
        CASE(N = 50000, M = 50000, randomCase());
        CASE(N = 50000, M = 50000, randomSmallTaburanCase());
        CASE(N = 50000, M = 50000, randomSmallTaburanCase());
    }

    void TestGroup4() {
        Subtasks({2});

        CASE(N = 50000, M = 50000, randomKillerCase());
        CASE(N = 50000, M = 50000, randomKillerCase());
        CASE(N = 50000, M = 50000, randomKillerCase());
        CASE(N = 50000, M = 50000, randomKillerCase());
        CASE(N = 50000, M = 50000, maxCase());
    }

private:
    void randomCase() {
        X.clear();
        K.clear();
        for (int i = 0; i < M; i++) {
            int x = rnd.nextInt(N) + 1;
            int k = rnd.nextInt(50000) + 1;
            X.push_back(x);
            K.push_back(k);
        }
    }

    void randomKillerCase() {
        X.clear();
        K.clear();
        for (int i = 0; i < M; i++) {
            int x = rnd.nextInt(N) + 1;
            int k;

            if (i < M/4) {
                k = N/2 - rnd.nextInt(42);
            } else {
                k = N - rnd.nextInt(42);
            }
            X.push_back(x);
            K.push_back(k);
        }
    }

    void randomSmallTaburanCase() {
        X.clear();
        K.clear();
        for (int i = 0; i < M; i++) {
            int x = rnd.nextInt(N) + 1;
            int k;

            if (i < M/4) {
                k = rnd.nextInt(N) + 1;
            } else {
                k = rnd.nextInt(10) + 1;
            }
            X.push_back(x);
            K.push_back(k);
        }
    }

    void maxCase() {
        X.clear();
        K.clear();
        for (int i = 0; i < M; i++) {
            X.push_back(N/2);
            K.push_back(50000);
        }
    }
};

