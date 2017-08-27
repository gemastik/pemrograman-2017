#include <tcframe/spec.hpp>
#include "VectorRandomizer.hpp"
using namespace tcframe;
using namespace tcrand;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N, M;
    vector<int> A, B, C;

    long long res;

    void InputFormat() {
        LINE(N, M);
        LINE(A % SIZE(N));
        LINE(B % SIZE(N));
        LINE(C % SIZE(M));
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
        CONS(1 <= N && N <= 100000);
        CONS(eachElementBetween(A, 0, 1000000));
        CONS(eachElementBetween(B, 0, 1000000));
        CONS(eachElementBetween(C, 0, 1000000));
    }

    void Subtask1() {
        CONS(1 <= M && M <= 1000);
    }

    void Subtask2() {
        CONS(1 <= M && M <= 100000);
    }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        return all_of(v.begin(), v.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {

    VectorRandomizer<int> rand_A, rand_B, rand_C;
    int C_ans;

    vector<int> P(int st, int ed){
        vector<int> res;
        for (int i=st;i<=ed;i++)res.push_back(i);
        return res;
    }

    vector<int> killer(int siz, int root, int placement=500){
        vector<int> res;
        siz-=101;
        for (int i=0;i<siz;i++) res.push_back(i * root);
        for (int i=0;i<100;i++) res.push_back(siz * root + i);
        res.push_back(placement * root + 1);
        return res;
    }

    void construct_C(){
        vector<int> tA = A;
        vector<int> tB = B;
        sort(tA.begin(), tA.end());
        sort(tB.begin(), tB.end());
        int NA = unique(tA.begin(), tA.end()) - tA.begin();
        int NB = unique(tB.begin(), tB.end()) - tB.begin();

        C = vector<int>(M);

        priority_queue<pair<long long, pair<int, int> > > pq;
        pq.push({-1LL * tA[0] * tB[0] , {0,0}});
        int curr = 0;
        long long loc = 0;
        int la=0,lb=0;
        long long marked[M];
        long long latest_mark = 0;
        int mark_step = 0;
        int mark_count = 0;
        memset(marked, -1, sizeof(marked));
        set<pair<int,int> > done;

        while(curr < C_ans && !pq.empty() && mark_count < M) {
            pair<int,int> pos = pq.top().second;

            pq.pop();
            if (pos.first >= NA || pos.second >= NB) continue;
            long long diff = ((long long)tA[pos.first] * tB[pos.second]) - ((long long)tA[0] * tB[0]);
            if (diff >= 1000000) break;

            loc = ((long long)tA[pos.first] * (long long)tB[pos.second]);

            if (marked[loc % M] == -1) {
                marked[loc % M] = loc;
                latest_mark = loc;
                mark_count++;
                mark_step = curr;
                la = pos.first; lb = pos.second;
            }

            if (!done.count({pos.first + 1, pos.second})) {
                done.insert({pos.first + 1, pos.second});
                pq.push({-1LL * tA[pos.first + 1] * tB[pos.second], {pos.first + 1, pos.second}});
            }

            if (!done.count({pos.first, pos.second + 1})) {
                done.insert({pos.first, pos.second + 1});
                pq.push({-1LL * tA[pos.first] * tB[pos.second + 1], {pos.first, pos.second + 1}});
            }

            curr++;
        }

        long long diff = ((long long)tA[la] * tB[lb]) - ((long long)tA[0] * tB[0]);
        long long exp_sol = marked[latest_mark % M];
        
        /*
        cerr<<" == "<<endl;
        cerr<<"expected solution: "<<exp_sol<<endl;
        cerr<<"sorted solution indexes "<<la<<", "<<lb<<endl;
        cerr<<"mark count: "<< mark_count <<endl;  
        cerr<<"mark step: "<< mark_step <<endl;  
        cerr<<tA[la]<<" "<<tB[lb]<<" vs "<<tA[0]<<" "<<tB[0]<<endl;
        */
        long ans_loc = ((long long)tA[la] * tB[lb]) % M;
        int offset =rnd.nextInt(0, 1000000 - diff - 1);
        //cerr<<offset<<endl;
        for (int i=0;i<M;i++){
            if (i == ans_loc) C[i] = offset;
            else if (marked[i] == -1) C[i] = rnd.nextInt(max(0, offset - 10000), offset);
            else C[i] =  rnd.nextInt(exp_sol - marked[i] + 1 , 1000000 - offset) + offset;
        }
    }    


protected:
    void BeforeTestCase() {
        C_ans = -1;
        A.clear();
        B.clear();
        C.clear();
        rand_A = VectorRandomizer<int>();
        rand_B = VectorRandomizer<int>();
        rand_C = VectorRandomizer<int>();
    }

    void AfterTestCase() {
        rand_A.engine( [&] {return rnd.nextInt(0,1000000);} );
        rand_B.engine( [&] {return rnd.nextInt(0,1000000);} );
        rand_C.engine( [&] {return rnd.nextInt(0,1000000);} );

        if (A.empty()) A = rand_A.length(N).next();
        if (B.empty()) B = rand_B.length(N).next();
        if (C_ans != -1) construct_C();
        if (C.empty()) C = rand_C.length(M).next();
    }


    void SampleTestCase1() {
        Subtasks({1, 2});
        Input({
            "4 2",
            "3 14 15 9",
            "26 53 58 97",
            "93 2"
        });
        Output({
            "161"
        });
    }

    void SampleTestCase2() {
        Subtasks({1, 2});
        Input({
            "4 3",
            "3 14 15 9",
            "26 53 58 97",
            "93 2 38"
        });
        Output({
            "171"
        });
    }


    void antiMarshall(int _M) {
        CASE(N = 25000, M = (_M/2)*2, rand_A.pool(killer(N, 2, 900)).unique(), rand_B.pool(killer(N, 2, 900)).unique(), C_ans = 3000000); 
        CASE(N = 30000, M = (_M/6)*6, rand_A.pool(killer(N, 2, 6000)).unique(), rand_B.pool(killer(N, 3, 3)).unique(), C_ans = 3000000); 
        CASE(N = 30000, M = (_M/6)*6, rand_A.pool(killer(N, 3, 20)).unique(), rand_B.pool(killer(N, 2, 3000)).unique(), C_ans = 1000000); 
        CASE(N = 50000, M = (_M/3)*3, rand_A.pool(killer(N, 3, 123)).unique(), rand_B.pool(killer(N, 3, 321)).unique(), C_ans = 5000000); 
        CASE(N = 60000, M = (_M/2)*2, rand_A.pool(killer(N, 2, 50000)).unique(), rand_B.pool(killer(N, 2, 2)).unique(), C_ans = 5000000);  

    }

    void killerCases(int _M) {
        CASE(N = 25000, M = (_M/2)*2 /*genap*/, rand_A.pool(killer(N, 2)).unique(), rand_B.pool(killer(N, 2)).unique(), C_ans = 3000000); //kalo ngeceknya cuman sampe index 1000
        CASE(N = 100000, M = _M, rand_A.pool(P(3000,1000000)).unique(), rand_B.pool(P(3000,1000000)).unique(), C_ans = 3000000); //kalo ngeceknya cuman sampe nilai A*B <= 1jt
        CASE(N = 100000, M = _M, rand_A.distinct_elements(10000), rand_B.distinct_elements(10000), C_ans = 12345); //kalo lupa di-unique
        CASE(N = 100000, M = _M, rand_A.pool(P(1,1000000)).unique(), rand_B.pool(P(0,99999)).unique(), C_ans = 1000000); //ada 0-nya
        CASE(N = 100000, M = _M, rand_A.pool(P(10000,200000)).unique(), rand_B.pool(P(10000,200000)).unique(), C_ans = 777777); 
    }

    void randomCases(int _M) {
        CASE(N = rnd.nextInt(10000, 100000), M = rnd.nextInt(500, _M), C_ans = rnd.nextInt(5, 100));
        CASE(N = rnd.nextInt(50000, 100000), M = rnd.nextInt(_M - 500, _M), C_ans = rnd.nextInt(5000, 100000), rand_A.pool(P(100,1000000)) , rand_B.pool(P(100, 1000000)));
        CASE(N = rnd.nextInt(50000, 100000), M = rnd.nextInt(_M - 500, _M));
        CASE(N = 100000, M = _M);
        CASE(N = 100000, M = _M, rand_A.pool(P(100,1000000)) , rand_B.pool(P(100, 1000000)) );

    }

    void TestGroup1() {
        Subtasks({1, 2});
        CASE(N = 1, M = 1, A = {1000000}, B = {1000000}, C = {1000000}); //edge case 1
        CASE(N = 100000, M = 1); //edge case 2
        CASE(N = 1, M = 1); //edge case 3
        CASE(rand_A.distinct_elements(1), rand_B.distinct_elements(1), N = 100000, M = 1000); //edge case 4
        CASE(rand_A.pool(P(0,0)), rand_B.pool(P(0,0)), N = 100000, M = 1000); //edge case 5
    }

    void TestGroup2() {
        Subtasks({1, 2});
        CASE(N = 50, M = 1000); //small random
        CASE(N = 100000, M = 997); //big random
        CASE(rand_A.distinct_elements(300), rand_B.distinct_elements(300), N = 100000, M = 997); //mepet2
        CASE(rand_A.distinct_elements(10), rand_B.distinct_elements(10), N = 88888, M = 888);
        CASE(rand_A.unique(), rand_B.unique(), N = 999, M = 999);
    }

    void TestGroup3() {
        Subtasks({1, 2});
        killerCases(997);
    }

    void TestGroup4() {
        Subtasks({1, 2});
        randomCases(1000);
    }

    void TestGroup5() {
        Subtasks({1, 2});
        antiMarshall(900);
    }


    void TestGroup6() {
        Subtasks({2});
        killerCases(98047);
    }

    void TestGroup7() {
        Subtasks({2});
        randomCases(100000);
    }

    void TestGroup8() {
        Subtasks({2});
        antiMarshall(99999);
    }


public:
    TestSpec(){
        tcrand::r_engine.seed(0);
    }
};
