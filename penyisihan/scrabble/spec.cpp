#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

const int MAXN = 50;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    string S;
    int N, K;

    int res;

    void InputFormat() {
        LINE(S, N, K);
    }

    void OutputFormat() {
        LINE(res);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 5);
    }

    void Constraints() {
        CONS(validString());
        CONS(1 <= N && N <= MAXN);
        CONS(1 <= K && K <= 26);
    }

    void Subtask1() {
        CONS(S.size() == 2);
    }

    void Subtask2() {
        CONS(1 <= S.size() && S.size() <= 10);
    }

private:
    bool validString() {
        for (char c : S) {
            if (c < 'a' || c > 'a' + K - 1) return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void TestGroup1() {
        Subtasks({1, 2});

        CASE(N = MAXN, S = "aa", K = 1);
        CASE(N = MAXN, S = "za", K = 26);
        CASE(N = MAXN, S = "yf", K = 25);
        CASE(N = 7, S = "by", K = 26);
        CASE(N = 1, S = "kj", K = 18);
    }

    void TestGroup2() {
        Subtasks({1, 2});

        CASE(N = MAXN, S = "lr", K = 26);
        CASE(N = MAXN, S = "pp", K = 26);
        CASE(N = 15, S = "jg", K = 12);
        CASE(N = 5, S = "jj", K = 12);
        CASE(N = 1, S = "il", K = 12);
    }

    void TestGroup3() {
        Subtasks({2});

        CASE(N = MAXN, S = randomString(8, 20), K = 20);
        CASE(N = MAXN, S = randomString(9, 18), K = 26);
        CASE(N = MAXN, S = randomString(10, 15), K = 15);
        CASE(N = 17, S = randomString(10, 26), K = 26);
        CASE(N = 4, S = randomString(10, 10), K = 26);
    }

    void TestGroup4() {
        Subtasks({2});

        CASE(N = MAXN, S = "abcdefghij", K = 20);
        CASE(N = MAXN, S = "aaaaazaaaa", K = 26);
        CASE(N = MAXN, S = "aaaaaaaaaa", K = 1);
        CASE(N = 9, S = "g", K = 26);
        CASE(N = 1, S = randomString(9, 10), K = 15);
    }

    void TestGroup5() {
        Subtasks({2});
        
        CASE(N = MAXN, S = randomString(10, 10), K = 26);
        CASE(N = MAXN, S = randomString(10, 2), K = 12);
        CASE(N = MAXN, S = randomString(10, 3), K = 26);
        CASE(N = MAXN, S = randomString(9, 2), K = 26);
        CASE(N = MAXN, S = randomString(9, 5), K = 15);
    }

    void TestGroup6() {
        Subtasks({2});

        CASE(N = MAXN, S = "ababababa", K = 26);
        CASE(N = MAXN, S = "dawrvdawrv", K = 26);
        CASE(N = MAXN, S = "abracdabra", K = 26);
        CASE(N = 49, S = "kasurrusak", K = 26);
        CASE(N = 29, S = "itouryuiai", K = 26);
    }

    string randomString(int len, int k) {
        string res = "";
        for (int i = 0; i < len; ++i) {
            res += rnd.nextInt('a', k + 'a' - 1);
        }
        return res;
    }
};
