#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

typedef long long ll;

const int MIN_RICHNESS = 1;
const int MAX_RICHNESS = 100000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N;
    vector<int> R; // Richness
    vector<int> P; // Parent

    ll res;

    void InputFormat() {
        LINE(N);
        LINE(P % SIZE(N-1));
        LINE(R % SIZE(N));
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
        CONS(eachElementBetween(R, MIN_RICHNESS, MAX_RICHNESS));
        CONS(isTree());
    }

    void Subtask1() {
        CONS(2 <= N && N <= 1000);
    }

    void Subtask2() {
        CONS(2 <= N && N <= 100000);
    }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        return all_of(v.begin(), v.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }

    bool isTree() {
        for (int i = 2; i <= N; i++) {
            if ((P[i-2] < 1) || (P[i-2] >= i)) return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1, 2});
        Input({
            "6",
            "1 1 1 4 4",
            "3 6 1 4 2 1"
        });
        Output({
            "4"
        });
    }

    /*
    Note: the larger a node's index, the deeper it is
     */

    void BeforeTestCase() {
        N = 0;
        R.clear();
        P.clear();
    }

    void TestGroup1() {
        Subtasks({1, 2});

        CASE(linearTree(500), randomRichness());
        CASE(kAryTree(500, 2, 10), randomRichness());
        CASE(kAryTree(500, 4, 30), randomRichness());
        CASE(randomTree(500), ascRichness());
        CASE(randomTree(500), descRichness());
        CASE(randomTree(1000), randomRichness());
        CASE(chevronTree(1000, 2), randomRichness());
    }

    void TestGroup2() {
        Subtasks({2});

        CASE(linearTree(50000), descRichness()); // Overflow trap
        CASE(linearTree(50000), randomRichness());
        CASE(kAryTree(50001, 50000, 0), randomRichness()); // Shallow tree
        CASE(kAryTree(100000, 3, 50), randomRichness()); // Deep tree
        CASE(randomTree(100000), randomRichness());
        CASE(chevronTree(100000, 2), randomRichness());
    }

    void linearTree(int n) {
        N = n;
        P.clear();
        for (int i = 2; i <= N; i++) {
            P.push_back(i-1);
        }
    }

    void randomTree(int n) {
        N = n;
        P.clear();
        for (int i = 2; i <= N; i++) {
            int parIdx = rnd.nextInt(1, (int)floor(sqrt(i)));
            P.push_back(parIdx);
        }
    }

    void kAryTree(int n, int k, int holePercentage) {
        N = n;
        P.clear();

        vector<int> child[n];
        int nextIdx = 1;
        for (int i = 0; i < n; i++) {
            bool hadKid = false;
            for (int j = 0; j < k; j++) {
                bool lastChanceToHaveKid = !hadKid && (j == k-1);
                if ((nextIdx < n) && ((rnd.nextInt(1, 100) > holePercentage) || lastChanceToHaveKid)) {
                    hadKid = true;
                    child[i].push_back(nextIdx);
                    nextIdx++;
                }
            }
        }

        for (int i = 0; i < n-1; i++) {
            P.push_back(0);
        }
        for (int i = 0; i < n; i++) {
            for (int c : child[i]) {
                P[c-1] = i+1;
            }
        }
    }

    void chevronTree(int n, int noisePercentage) {
        N = n;
        P.clear();

        int lastChild1 = 1;
        int lastChild2 = 1;
        for (int i = 2; i <= N; i++) {
            if (rnd.nextInt(1, 100) <= noisePercentage) {
                // Add noise
                P.push_back(rnd.nextInt(1, i-1));
            } else {
                // Add node to chevron's edge
                if (rnd.nextInt(1, 2) == 1) {
                    P.push_back(lastChild1);
                    lastChild1 = i;
                } else {
                    P.push_back(lastChild2);
                    lastChild2 = i;
                }
            }
        }
    }

    void randomRichness() {
        R.clear();
        for (int i = 0; i < N; i++) {
            R.push_back(rnd.nextInt(MIN_RICHNESS, MAX_RICHNESS));
        }
    }

    void ascRichness() {
        randomRichness();
        sort(R.begin(), R.end());
    }

    void descRichness() {
        ascRichness();
        reverse(R.begin(), R.end());
    }
};
