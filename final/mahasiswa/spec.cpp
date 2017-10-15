#include <tcframe/spec.hpp>

using namespace tcframe;
using namespace std;

typedef long long ll;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N, K;
    vector<int> M;

    ll result;

    void InputFormat() {
        LINE(N, K);
        LINE(M % SIZE(N));
    }

    void OutputFormat() {
        LINE(result);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 10);
    }

    void Constraints() {
        CONS(eachElementBetween(M, 1, 100000));
        CONS(1 <= K && K <= N);
    }

    void Subtask1() {
        CONS(1 <= N && N <= 2);
    }

    void Subtask2() {
        CONS(1 <= N && N <= 100000);
    }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        return all_of(v.begin(), v.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
    vector<int> rand_ints(int count, int mod, int tgt_mod, int lo, int hi){
        vector<int> res;
        for (int i=1;i<count;i++){
            res.push_back(rnd.nextInt(lo,hi));
        }
        int tot = 0;
        for (int i:res) tot = (tot + i) % mod;
        res.push_back((tot - tgt_mod + mod) % mod);
        if (res[count-1] == 0) res[count-1] = mod;
        return res;
    }

protected:
    void SampleTestCase1() {
        Subtasks({1, 2});
        Input({"2 2",
              "10 12"});
        Output({"12"});
    }

    void SampleTestCase2() {
        Subtasks({1, 2});
        Input({"2 1",
              "10 12"});
    	Output({"22"});
    }

    void SampleTestCase3() {
        Subtasks({2});
        Input({"3 2",
              "3 2 1"});
    	Output({"3"});
    }

    void TestGroup1(){
        Subtasks({1, 2});
        CASE(N=1, K=1, M={1});
        CASE(N=1, K=1, M={100000});
        CASE(N=2, K=1, M={100000, 100000});
        CASE(N=2, K=2, M={100000, 100000});
        CASE(N=2, K=1, M={1, 100000});
        CASE(N=2, K=2, M={1, 100000});
        CASE(N=2, K=1, M={100000, 1});
        CASE(N=2, K=2, M={100000, 1});
        CASE(N=2, K=1, M={3126, 4687});
        CASE(N=2, K=2, M={4233, 5432});
    }


    void TestGroup2(){
        Subtasks({2});
        CASE(N=100000, K=45, M = rand_ints(N, K, 0, 1, 100000)); //dibagi habis
        CASE(N=100000, K=999, M = rand_ints(N, K, 0, 10000, 100000)); //dibagi habis
        CASE(N=100000, K=1, M = rand_ints(N, K, 0, 100000, 100000)); //overflow test
        CASE(N=100000, K=100000, M = rand_ints(N, K, 0, 100000, 100000)); //overflow test2
        CASE(N=rnd.nextInt(50000, 100000), K=674, M = rand_ints(N, K, 1, 1, 100000)); //sisa 1
        CASE(N=rnd.nextInt(50000, 100000), K=432, M = rand_ints(N, K, 431, 1, 100000)); //sisa K-1
        CASE(N=100000, K=99999, M = rand_ints(N, K, 2, 1, 1)); //sum(M)/K < max(M)

        //randoms
        CASE(N=rnd.nextInt(50000, 100000), K=rnd.nextInt(2000, N),
             M = rand_ints(N, K, rnd.nextInt(0, K), 1, 100));
        CASE(N=rnd.nextInt(50000, 100000), K=rnd.nextInt(2000, N),
             M = rand_ints(N, K, rnd.nextInt(0, K), 2000, N));
        CASE(N=rnd.nextInt(50000, 100000), K=rnd.nextInt(1, 100),
             M = rand_ints(N, K, rnd.nextInt(0, K), 50000, 100000));
    }
};
