#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

constexpr int MAX_N = 1000000000;
constexpr int MAX_L = 10000;

template<typename T>
inline bool inRange(const T& z, const T& lb, const T& ub) { return lb <= z && z <= ub; }

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N, L;
    string S;

    int ANS;

    void InputFormat() {
        LINE(N, L);
        LINE(S);
    }

    void OutputFormat() {
        LINE(ANS);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(inRange(T, 1, 10));
    }

    void Constraints() {
        CONS(S.length() <= L);
        CONS(eachElementNonDecreasing({S}));
        CONS(eachElementLengthBetween({S}, 1, L));
    }

    void Subtask1() {
        CONS(N == 2);
        CONS(inRange(L, 1, 6));
    }

    void Subtask2() {
        CONS(inRange(N, 2, MAX_N));
        CONS(inRange(L, 1, MAX_L));
    }

private:
    bool eachElementLengthBetween(const vector<string>& v, int lo, int hi) {
        return all_of(v.begin(), v.end(), [&](string a) { return inRange((int) a.length(), lo, hi); });
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

        CASE(N = 2, L = 1, S = "a");
        CASE(N = 2, L = 1, S = "l");
        CASE(N = 2, L = 1, S = "o");
        CASE(N = 2, L = 1, S = "t");
        CASE(N = 2, L = 1, S = "z");
        CASE(N = 2, L = 2, S = "a");
        CASE(N = 2, L = 3, S = "l");
        CASE(N = 2, L = 4, S = "o");
        CASE(N = 2, L = 5, S = "t");
        CASE(N = 2, L = 6, S = "z");
    }

    void TestGroup2() {
        Subtasks({1, 2});

        CASE(N = 2, L = 6, S = "aaaaaa");
        CASE(N = 2, L = 6, S = "asu");
        CASE(N = 2, L = 5, S = "alot");
        CASE(N = 2, L = 6, S = "yyyyyy");
        CASE(N = 2, L = 6, S = "abcde");
        CASE(N = 2, L = 6, S = "uvwxyz");
        CASE(N = 2, L = 6, S = "aamnzz");
        CASE(N = 2, L = 6, S = "zzzzzz");
        CASE(N = 2, L = 4, S = "zzz");
        CASE(N = 2, L = 6, S = "afkpuy");
    }

    void TestGroup3() {
        Subtasks({2});

        CASE(N = 3,         L = 10000,     S = "z");
        CASE(N = 3,         L =  9999,     S = "a");
        CASE(N = 3,         L =  9998,     S = "y");
        CASE(N = 3,         L =  9997,     S = "n");
        CASE(N = 3,         L =  9996,     S = "annoy");
        CASE(N = MAX_N,     L =     5,     S = "annoy");
        CASE(N = MAX_N,     L =     5,     S = generateString(5, 1));
        CASE(N = MAX_N,     L =    15,     S = generateString(15, 0));
        CASE(N = MAX_N,     L =   300,     S = generateString(250, 13));
        CASE(N = MAX_N,     L =  1337,     S = generateString(1010, 15));
    }

    void TestGroup4() {
        Subtasks({2});

        CASE(N = rnd.nextInt(MAX_N >> 1, MAX_N), L = rnd.nextInt(MAX_L - 500, MAX_L), S = generateString(rnd.nextInt(9000, L), 0));
        CASE(N = rnd.nextInt(MAX_N >> 1, MAX_N), L = rnd.nextInt(MAX_L - 500, MAX_L), S = generateString(rnd.nextInt(9000, L), 0));
        CASE(N = rnd.nextInt(MAX_N >> 1, MAX_N), L = rnd.nextInt(MAX_L - 500, MAX_L), S = generateString(rnd.nextInt(9000, L), 0));
        CASE(N = rnd.nextInt(MAX_N >> 1, MAX_N), L = rnd.nextInt(MAX_L - 500, MAX_L), S = generateString(rnd.nextInt(9000, L), 0));
        CASE(N = rnd.nextInt(MAX_N >> 1, MAX_N), L = rnd.nextInt(MAX_L - 500, MAX_L), S = generateString(rnd.nextInt(9000, L), 0));
        CASE(N = rnd.nextInt(MAX_N >> 1, MAX_N), L = rnd.nextInt(MAX_L - 500, MAX_L), S = generateString(rnd.nextInt(9000, L), 10));
        CASE(N = rnd.nextInt(MAX_N >> 1, MAX_N), L = rnd.nextInt(MAX_L - 500, MAX_L), S = generateString(rnd.nextInt(9000, L), 6));
        CASE(N = rnd.nextInt(MAX_N >> 1, MAX_N), L = rnd.nextInt(MAX_L - 500, MAX_L), S = generateString(rnd.nextInt(9000, L), 9));
        CASE(N = rnd.nextInt(MAX_N >> 1, MAX_N), L = rnd.nextInt(MAX_L - 500, MAX_L), S = generateString(rnd.nextInt(9000, L), 5));
        CASE(N = rnd.nextInt(MAX_N >> 1, MAX_N), L = rnd.nextInt(MAX_L - 500, MAX_L), S = generateString(rnd.nextInt(9000, L), 4));
    }

private:
    string generateString(int targetLength, int targetGrundy) {
        int petak = targetLength + 1;

        vector<int> piles = {};
        int banyak_ganjil = petak >> 1;
        while (!generatePiles(targetGrundy, 0 /* total sum */, min(banyak_ganjil, 10), piles));
        vector<int> positions = {};

        set<int> used_position;

        while (positions.size() < piles.size()) {
            int pos;
            do {
                pos = rnd.nextInt(banyak_ganjil) * 2 + 1;
            } while (used_position.find(pos) != used_position.end());

            used_position.insert(pos);
            positions.push_back(pos);
        }

        vector<int> increments = {};
        increments.resize(petak);
        fill(increments.begin(), increments.end(), 0);
        for (int i = 0; i < piles.size(); ++i) {
            increments[positions[i]] = piles[i];
        }

        int tsum = 0;
        for (const auto& num : piles) {
            tsum += num;
        }

        int banyak_genap = petak - banyak_ganjil;
        for (int i = 0; i < 25 - tsum; ++i) {
            int pos = rnd.nextInt(banyak_genap) * 2;
            ++increments[pos];
        }

        char c = 'a';
        string res = "";
        increments.pop_back();
        for (const int& i : increments) {
            c += i;
            res.push_back(c);
        }
        return res;
    }

    bool generatePiles(int target, int sum, int depth_left, vector<int>& piles) {
        if (sum > 25) {
            return 0;
        }
        if (sum > 0 && target == 0) {
            return sum <= 25;
        }
        if (depth_left == 0) {
            return 0;
        }
        vector<int> pool = {};
        for (int i = 0; i < 32; ++i) {
            pool.push_back(i);
        }
        rnd.shuffle(pool.begin(), pool.end());
        for (const auto& num : pool) {
            if (generatePiles(target ^ num, sum + num, depth_left - 1, piles)) {
                piles.push_back(num);
                return 1;
            }
        }
    }
};
