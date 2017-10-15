#include <tcframe/spec.hpp>
#include <vector>
using namespace tcframe;
using namespace std;


int MAX_INT = numeric_limits<int>::max();

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N, M, K;
    string S;
    vector<int> gold, silver, bronze;

    void InputFormat() {
        LINE(N, M, K);
    }

    void OutputFormat1() {
        LINE(S);
    }

    void OutputFormat2() {
        LINE(S);
        LINES(gold, silver, bronze) % SIZE(N);
    }


    void StyleConfig() {
        CustomScorer();
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 10);
    }

    void Constraints() {
        CONS(1 <= N && N <= 20000);
        CONS(3 <= M && M <= 20000);
        CONS(K <= N);
    }

    void Subtask1() {
        CONS(K == 2);
    }

    void Subtask2() {
        CONS(1 <= K && K <= M);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1, 2});
        Input({
            "3 3 2"
        });
        Output({"mustahil"});
    }
    void SampleTestCase2() {
       Subtasks({1, 2});
        Input({
            "5 10 2"
        });
        Output({
            "mungkin",
            "1 9 10",
            "1 9 10",
            "2 6 7",
            "2 6 7",
            "5 9 10"
        });
    }
    void SampleTestCase3(){
        Subtasks({2});
        Input({
            "4 3 3"
        });
        Output({"mustahil"});
    }

    void SampleTestCase4() {
        Subtasks({2});
        Input({
            "8 6 3"
        });
        Output({
            "mungkin",
            "1 2 6",
            "1 2 6",
            "2 3 6",
            "2 3 6",
            "3 1 6",
            "3 1 6",
            "4 5 6",
            "5 4 6"
        });
    }

    void TestGroup1() {
        Subtasks({1, 2});
        CASE(N = 2, M = 3, K = 2);
        CASE(N = 3, M = 5, K = 2);
        CASE(N = 5, M = 3, K = 2);
        CASE(N = 3, M = 4, K = 2);
        CASE(N = 6, M = 3, K = 2);
        CASE(N = 19999, M = 3, K = 2);
        CASE(N = 19999, M = 4, K = 2);
        CASE(N = 19999, M = 20000, K = 2);
        CASE(N = 20000, M = 3, K = 2);
        CASE(N = 20000, M = 20000, K = 2);
    }

    void TestGroup2() {
        Subtasks({2});
        CASE(N = 1, M = 3, K = 1);
        CASE(N = 20000, M = 20000, K = 1);
        CASE(N = 3, M = 3, K = 3); // sisa = 0
        CASE(N = 9901, M = 100, K = 99); // sisa = 1, possible
        CASE(N = 19999, M = 19999, K = 10000); // impossible
        CASE(N = 19998, M = 19999, K = 10000); // possible
        CASE(N = 1500, M = 500, K = 500); // possible
        CASE(N = 1503, M = 501, K = 500); // impossible
        CASE(N = 1502, M = 501, K = 500); // possible
        CASE(N = 1562, M = 521, K = 500); // possible
    }

    void TestGroup3() {
        Subtasks({2});
        //gede2 semua
        CASE(N = 20000, M = 20000, K = 19997);
        CASE(N = 19865, M = 20000, K = 1337);
        CASE(N = 19777, M = 20000, K = 999);
        CASE(N = 18900, M = 20000, K = 12345);
        CASE(N = 15000, M = 20000, K = 200);
        CASE(N = 20000, M = 3, K = 3);
        CASE(N = 19000, M = 20, K = 19);
        CASE(N = 18766, M = 50, K = 45);
        CASE(N = 19997, M = 4, K = 3);
        CASE(N = 19993, M = 7, K = 6);
    }
};



