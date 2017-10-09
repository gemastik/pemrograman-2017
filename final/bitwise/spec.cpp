#include <tcframe/spec.hpp>
#include <vector>
using namespace tcframe;
using namespace std;


int BIN_MILLION = (1<<20)-1;
int MAX_INT = numeric_limits<int>::max();

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N, A, B, C;

    vector<int> res;
    int res2; //-1 (impossible)

    void InputFormat() {
        // N , and, or, xor
        LINE(N, A, B, C);
    }

    void OutputFormat1() {
        LINES(res);
    }

    void OutputFormat2() {
        LINE(res2);
    }


    void StyleConfig() {
        CustomScorer();
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 20);
    }

    void Subtask1() {
        CONS(N == 2);
        CONS(0 <= A && A <= BIN_MILLION);
        CONS(0 <= B && B <= BIN_MILLION);
        CONS(0 <= C && C <= BIN_MILLION);
    }

    void Subtask2() {
        CONS(1 <= N && N <= 20000);
        CONS(0 <= A && A <= MAX_INT);
        CONS(0 <= B && B <= MAX_INT);
        CONS(0 <= C && C <= MAX_INT);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
    int smallRand(){
        return rnd.nextInt(0, BIN_MILLION);
    }

    int rand(){
        return rnd.nextInt(0, MAX_INT);
    }


protected:
    void SampleTestCase1() {
        Subtasks({1, 2});
        Input({
            "2 8 14 6"
        });
        // impossible
        Subtasks({1, 2});
        Input({
            "2 8 14 4"
        });
        Subtasks({2});
        Input({
            "3 8 14 4"
        });
    }

    void TestGroup1() {
        Subtasks({1, 2});
        CASE(N = 2, A = 0, B = 0, C = 0);
        CASE(N = 2, A = 0, B = 0, C = 1);
        CASE(N = 2, A = 0, B = 1, C = 0);
        CASE(N = 2, A = 0, B = 1, C = 1);
        CASE(N = 2, A = 1, B = 0, C = 0);
        CASE(N = 2, A = 1, B = 0, C = 1);
        CASE(N = 2, A = 1, B = 1, C = 0);
        CASE(N = 2, A = 1, B = 1, C = 1);

        CASE(N = 2, A = 0, B = 145661, C = 145661);
        CASE(N = 2, A = 0, B = 145661, C = 145660);

        CASE(N = 2, A = BIN_MILLION, B = BIN_MILLION, C = BIN_MILLION);
        CASE(N = 2, A = BIN_MILLION, B = 0, C = 0);
        CASE(N = 2, A = 0, B = BIN_MILLION, C = 0);
        CASE(N = 2, A = 0, B = 0, C = BIN_MILLION);
        /*
        p q -> A B C
        0 0 -> 0 0 0
            -> 0 0 1 (gagal)
            -> 0 1 0 (gagal)
        0 1 -> 0 1 1
            -> 1 0 0 (gagal)
            -> 1 0 1 (gagal)
            -> 1 1 0 (gagal)
        1 1 -> 1 1 1
        */
        CASE(N = 2, A = 0b1111000000, B = 0b1100110000, C = 0b1010101000); // all bit combinations
        CASE(N = 2, A = 0b1111000001, B = 0b1111110001, C = 0b1111110001); // success bit only
        CASE(N = 2, A = 0b1111000000, B = 0b1000000000, C = 0b0010111111); // fail bit only
        CASE(N = 2, A = 0b1101000001, B = 0b1111110001, C = 0b1111110001); // all success + 1 fail
    }

    void TestGroup2() {
        Subtasks({1, 2});
        for (int i = 0; i < 4; i++){
            CASE(N = 2, A = smallRand(), B = smallRand(), C = smallRand());
            CASE(N = 2, A = smallRand(), B = smallRand(), C = smallRand());
            CASE(N = 2, A = smallRand(), B = smallRand(), C = A ^ B);
            CASE(N = 2, A = smallRand(), C = smallRand(), B = A ^ C);
            CASE(N = 2, B = smallRand(), C = smallRand(), A = B ^ C);
        }
    }

    void TestGroup3() {
        Subtasks({2});
        //zonk
        CASE(N = 1, A = 321, B = 321, C = 321);
        CASE(N = 1, A = 321, B = 321, C = 53234);
        CASE(N = 1, A = 321, B = 5555, C = 321);
        CASE(N = 1, A = 43100, B = 321, C = 321);

        // N = 3
        CASE(N = 3, A = 0b1111000000, B = 0b1100110000, C = 0b1010101000); // all bit combinations
        CASE(N = 3, A = 0b1111000001, B = 0b1111110001, C = 0b1111110001); // success bit only
        CASE(N = 3, A = 0b1111000000, B = 0b1000000000, C = 0b0010111111); // fail bit only
        CASE(N = 3, A = 0b1101000001, B = 0b1111110001, C = 0b1111110001); // all success + 1 fail

        // genap
        CASE(N = 20000, A = 0b1111000000, B = 0b1100110000, C = 0b1010101000); // all bit combinations
        CASE(N = 20000, A = 0b1111000001, B = 0b1111110001, C = 0b1111110001); // success bit only
        CASE(N = 19998, A = 0b1111000000, B = 0b1000000000, C = 0b0010111111); // fail bit only
        CASE(N = 10004, A = 0b1101000001, B = 0b1111110001, C = 0b1111110001); // all success + 1 fail

        // ganjil gede
        CASE(N = 19999, A = 0b1111000000, B = 0b1100110000, C = 0b1010101000); // all bit combinations
        CASE(N = 19997, A = 0b1111000001, B = 0b1111110001, C = 0b1111110001); // success bit only
        CASE(N = 9999, A = 0b1111000000, B = 0b1000000000, C = 0b0010111111); // fail bit only
        CASE(N = 12345, A = 0b1101000001, B = 0b1111110001, C = 0b1111110001); // all success + 1 fail

        CASE(N = 20000, A = MAX_INT, B = MAX_INT, C = MAX_INT);
        CASE(N = 20000, A = MAX_INT, B = 0, C = 0);
        CASE(N = 20000, A = 0, B = MAX_INT, C = 0);
        CASE(N = 20000, A = 0, B = 0, C = MAX_INT);
    }

    void TestGroup4() {
        Subtasks({2});
        for (int i = 0; i < 2; i++){
            CASE(N = 3, A = rand(), B = rand(), C = rand());
            CASE(N = 3, A = rand(), B = rand(), C = rand());
            CASE(N = 3, A = rand(), B = rand(), C = A ^ B);
            CASE(N = 3, A = rand(), C = rand(), B = A ^ C);
            CASE(N = 3, B = rand(), C = rand(), C = B ^ C);
        }

        for (int i = 1; i <= 2; i++){
            CASE(N = (rnd.nextInt(20000, 39000)/2) + i, A = rand(), B = rand(), C = rand());
            CASE(N = (rnd.nextInt(20000, 39000)/2) + i, A = rand(), B = rand(), C = rand());
            CASE(N = (rnd.nextInt(20000, 39000)/2) + i, A = rand(), B = rand(), C = A ^ B);
            CASE(N = (rnd.nextInt(20000, 39000)/2) + i, A = rand(), C = rand(), B = A ^ C);
            CASE(N = (rnd.nextInt(20000, 39000)/2) + i, B = rand(), C = rand(), C = B ^ C);
        }
    }

     void TestGroup5() {
        Subtasks({2});

        CASE(N = 2, A = MAX_INT, B = MAX_INT, C = MAX_INT);
        CASE(N = 2, A = MAX_INT, B = 0, C = 0);
        CASE(N = 2, A = 0, B = MAX_INT, C = 0);
        CASE(N = 2, A = 0, B = 0, C = MAX_INT);
    }
};



