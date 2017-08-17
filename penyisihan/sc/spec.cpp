#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    const int MAX_COMPANIES = 50;
    int T;

    int N;
    vector<int> S;
    vector<int> P;
    vector<vector<int>> C;

    int res;

    void InputFormat() {
        LINE(N);
        LINE(S % SIZE(N));
        LINES(P, C) % SIZE(N);
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
        CONS(validCompanies());
    }

    void Subtask1() {
        CONS(1 <= N && N <= 10);
        CONS(eachElementBetween(S, 1, 2));
        CONS(eachElementBetween(P, 0, 2));
    }

    void Subtask2() {
        CONS(1 <= N && N <= 50);
        CONS(eachElementBetween(S, 1, 50));
        CONS(eachElementBetween(P, 0, 50));
    }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        return all_of(v.begin(), v.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }

    bool validCompanies() {
        for (int i = 0; i < N; i++) {
            if (P[i] != C[i].size()) return false;

            set<int> companies;
            for (int c : C[i]) {
                if (c < 1 || c > MAX_COMPANIES) return false;
                companies.insert(c);
            }

            if (companies.size() != C[i].size()) return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1, 2});
        Input({
            "3",
            "2 2 2",
            "1 42",
            "2 42 7",
            "0"
        });
        Output({
            "5"
        });
    }

    void SampleTestCase2() {
        Subtasks({1, 2});
        Input({
            "3",
            "2 2 1",
            "1 42",
            "1 42",
            "0"
        });
        Output({
            "4"
        });
    }

    void BeforeTestCase() {
        N = 0;
        S.clear();
        P.clear();
        C.clear();
    }

    void TestGroup1() {
        Subtasks({1, 2});

        // Small extremes
        CASE(N = 1, randomCase(1, 0, 10));
        CASE(N = 1, randomCase(1, 1, 10));
        CASE(N = 1, randomCase(1, 2, 10));
        CASE(N = 1, randomCase(2, 0, 10));
        CASE(N = 1, randomCase(2, 1, 10));
        CASE(N = 1, randomCase(2, 2, 10));

        // Random
        CASE(N = 3, randomCase(1, 2, 0, 2, 10), remapCompanies());
        CASE(N = 5, randomCase(1, 2, 0, 2, 10), remapCompanies());
        CASE(N = 7, randomCase(1, 2, 0, 2, 10), remapCompanies());
        CASE(N = 10, randomCase(1, 2, 0, 2, 10), remapCompanies());
    }

    void TestGroup2() {
        Subtasks({1, 2});

        // All in 1 company
        CASE(N = 10, randomCase(1, 1, 1));
        CASE(N = 10, randomCase(2, 1, 1));

        CASE(N = 10, antiForwardGreedy());
        CASE(N = 10, antiBackwardGreedy());
        CASE(N = 10, antiForwardGreedy(), remapCompanies());
        CASE(N = 10, antiBackwardGreedy(), remapCompanies());

        CASE(N = 10, antiForwardGreedy(), addNoise(25, 10), remapCompanies());
        CASE(N = 10, antiBackwardGreedy(), addNoise(25, 10), remapCompanies());
        CASE(N = 10, antiForwardGreedy(), addNoise(35, 10), remapCompanies());
        CASE(N = 10, antiBackwardGreedy(), addNoise(35, 10), remapCompanies());
    }

    void TestGroup3() {
        Subtasks({1, 2});

        // All made 1 problem
        CASE(N = 10, randomCase(1, 1, 0, 2, 10), remapCompanies());
        CASE(N = 10, randomCase(1, 1, 1, 2, 15), remapCompanies());
        CASE(N = 10, randomCase(1, 1, 2, 2, 15), remapCompanies());

        // All made 2 problem
        CASE(N = 10, randomCase(2, 2, 0, 2, 15), remapCompanies());
        CASE(N = 10, randomCase(2, 2, 1, 2, 15), remapCompanies());
        CASE(N = 10, randomCase(2, 2, 2, 2, 10), remapCompanies());

        // All jobless
        CASE(N = 10, randomCase(1, 0, 15), remapCompanies());
        CASE(N = 10, randomCase(2, 0, 15), remapCompanies());
    }

    void TestGroup4() {
        Subtasks({2});

        CASE(N = 20, randomCase(1, 3, 1, 5, 50), remapCompanies());
        CASE(N = 35, randomCase(1, 3, 1, 5, 50), remapCompanies());
        CASE(N = 50, randomCase(1, 3, 0, 5, 50), remapCompanies());
        CASE(N = 50, randomCase(3, 5, 0, 5, 50), remapCompanies());

        CASE(N = 50, randomCase(49, 50, 50), remapCompanies());
        CASE(N = 50, randomCase(50, 49, 50), remapCompanies());
        CASE(N = 50, randomCase(50, 50, 50), remapCompanies());

        // Anti backtracking
        CASE(N = 50, randomCase(2, 2, 50), remapCompanies());
        CASE(N = 50, randomCase(3, 5, 50), remapCompanies());
        CASE(N = 50, randomCase(3, 10, 50), remapCompanies());
    }

    void TestGroup5() {
        Subtasks({2});

        CASE(N = 50, only1OptimalSolutionForward(true));
        CASE(N = 50, only1OptimalSolutionBackward(true));
        CASE(N = 50, only1OptimalSolutionForward(true), remapCompanies());
        CASE(N = 50, only1OptimalSolutionBackward(true), remapCompanies());
        CASE(N = 50, only1OptimalSolutionForward(true), addNoise(10, 50), remapCompanies());
        CASE(N = 50, only1OptimalSolutionBackward(true), addNoise(10, 50), remapCompanies());

        CASE(N = 50, antiForwardGreedy());
        CASE(N = 50, antiBackwardGreedy());
        CASE(N = 50, antiForwardGreedy(), addNoise(15, 10), remapCompanies());
        CASE(N = 50, antiBackwardGreedy(), addNoise(15, 10), remapCompanies());
    }

    void TestGroup6() {
        Subtasks({2});

        CASE(N = 50, randomCase(1, 2, 0, 2, 50), remapCompanies());
        CASE(N = 50, randomCase(2, 2, 50), remapCompanies());
        CASE(N = 50, randomCase(2, 5, 50), remapCompanies());
        CASE(N = 50, randomCase(2, 10, 50), remapCompanies());

        CASE(N = 50, only1OptimalSolutionForward(false));
        CASE(N = 50, only1OptimalSolutionBackward(false));
        CASE(N = 50, only1OptimalSolutionForward(false), remapCompanies());
        CASE(N = 50, only1OptimalSolutionBackward(false), remapCompanies());
        CASE(N = 50, only1OptimalSolutionForward(false), addNoise(10, 50), remapCompanies());
        CASE(N = 50, only1OptimalSolutionBackward(false), addNoise(10, 50), remapCompanies());
    }

private:
    void randomCase(int sVal, int pVal, int nCompanyInvolved) {
        randomCase(sVal, sVal, pVal, pVal, nCompanyInvolved);
    }

    void randomCase(int minS, int maxS, int minP, int maxP, int nCompanyInvolved) {
        for (int i = 0; i < N; i++) {
            S.push_back(rnd.nextInt(minS, maxS));

            int nCompany = rnd.nextInt(minP, maxP);
            P.push_back(nCompany);
            C.push_back(getRandomCompanies(nCompany, nCompanyInvolved));
        }
    }

    void antiForwardGreedy() {
        S.push_back(2);
        P.push_back(2);
        C.push_back(vector<int>{1, N});

        for (int i = 1; i < N-1; i++) {
            S.push_back(2);
            P.push_back(2);
            C.push_back(vector<int>{i, i+1});
        }

        S.push_back(2);
        P.push_back(1);
        C.push_back(vector<int>{N-1});
    }


    void antiBackwardGreedy() {
        S.push_back(2);
        P.push_back(1);
        C.push_back(vector<int>{2});

        for (int i = 1; i < N-1; i++) {
            S.push_back(2);
            P.push_back(2);
            C.push_back(vector<int>{i+1, i+2});
        }

        S.push_back(2);
        P.push_back(2);
        C.push_back(vector<int>{1, N});
    }

    void only1OptimalSolutionForward(bool isFullCapacity) {
        for (int i = 0; i < N; i++) {
            if (isFullCapacity) {
                S.push_back(N - i);
            } else {
                S.push_back(2);
            }

            int nCompany = N - i;
            P.push_back(nCompany);

            vector<int> companies;
            for (int j = i+1; j <= N; j++) {
                companies.push_back(j);
            }
            C.push_back(companies);
        }
    }

    void only1OptimalSolutionBackward(bool isFullCapacity) {
        for (int i = 0; i < N; i++) {
            if (isFullCapacity) {
                S.push_back(i+1);
            } else {
                S.push_back(2);
            }

            int nCompany = i+1;
            P.push_back(nCompany);

            vector<int> companies;
            for (int j = 1; j <= i+1; j++) {
                companies.push_back(j);
            }
            C.push_back(companies);
        }
    }

    vector<int> getRandomCompanies(int size, int nCompanyInvolved) {
        set<int> companies;
        while (companies.size() < size) {
            int company = rnd.nextInt(1, nCompanyInvolved);
            companies.insert(company);
        }

        vector<int> result(companies.begin(), companies.end());
        return result;
    }

    // Randomly re-assign someone's company to other company
    void addNoise(int percentage, int nCompanyInvolved) {
        for (int i = 0; i < C.size(); i++) {
            for (int j = 0; j < C[i].size(); j++) {
                if (rnd.nextInt(1, 100) <= percentage) {
                    C[i][j] = rnd.nextInt(1, nCompanyInvolved);
                }
            }

            sort(C[i].begin(), C[i].end());
            C[i].erase(unique(C[i].begin(), C[i].end()), C[i].end());

            P[i] = C[i].size();
        }
    }

    // Randomly shuffles company ids
    void remapCompanies() {
        int mappedTo[MAX_COMPANIES + 1];
        for (int i = 1; i <= MAX_COMPANIES; i++) {
            mappedTo[i] = i;
        }

        rnd.shuffle(mappedTo + 1, mappedTo + MAX_COMPANIES + 1);

        for (int i = 0; i < C.size(); i++) {
            for (int j = 0; j < C[i].size(); j++) {
                C[i][j] = mappedTo[C[i][j]];
            }
        }
    }
};
