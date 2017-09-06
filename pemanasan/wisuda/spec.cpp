#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

template <typename T>
bool inRange(const T& o, const T& a, const T& b) { return a <= o && o <= b; }

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N;
    vector<string> types;
    vector<int> K;
    vector<vector<string>> names;
    int res;

    void InputFormat() {
        LINE(N);
        LINES(types, K, names) % SIZE(N);
    }

    void OutputFormat() {
        LINE(res);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(64);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 5);
    }

    void Constraints() {
        CONS(eachElementBetween(K, 1, 10));
        CONS(validNames());
        CONS(namesAndKMatch());
        CONS(uniqueNamesInAPhoto());
    }

    void Subtask1() {
        CONS(N == 1);
    }

    void Subtask2() {
        CONS(1 <= N && N <= 100);
    }

private:
    template <typename T>
    bool eachElementBetween(const vector<T>& A, const T& lo, const T& hi) {
        return all_of(A.begin(), A.end(), [lo, hi](const T& a) {return inRange(a, lo, hi);});
    }

    bool validNames() {
        for (vector<string>& v : names) {
            for (string s : v) {
                if (!inRange((int) s.size(), 1, 8)) {
                    return false;
                }
                if (!all_of(s.begin(), s.end(), [](char c) { return inRange(c, 'a', 'z'); })) {
                    return false;
                }
            }
        }
        return true;
    }

    bool namesAndKMatch() {
        for (int i = 0; i < N; i++) {
            if (K[i] != names[i].size()) {
                return false;
            }
        }
        return true;
    }

    bool uniqueNamesInAPhoto() {
        for (vector<string>& v : names) {
            set<string> s(v.begin(), v.end());
            if (s.size() != v.size()) {
                return false;
            }
        }
        return true;
    }

};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1, 2});
        Input({
            "1",
            "selfie 2 ani budi"
        });
        Output({"2"});
    }

    void SampleTestCase2() {
        Subtasks({1, 2});
        Input({
            "1",
            "dibantu 1 ani"
        });
        Output({"2"});
    }

    void SampleTestCase3() {
        Subtasks({2});
        Input({
            "3",
            "dibantu 3 ani budi candra",
            "dibantu 1 budi",
            "selfie 3 ani candra budi"
        });
        Output({"4"});
    }

    void TestGroup1() {
        Subtasks({1, 2});

        CASE(
            N = 1,
            types = {"selfie"},
            K = {1},
            names = {{"dengklek"}}
        );
        CASE(
            N = 1,
            types = {"dibantu"},
            K = {1},
            names = {{"dengklek"}}
        );
        CASE(
            N = 1,
            types = {"selfie"},
            K = {4},
            names = {{"the", "hash", "slinging", "slasher"}}
        );
        CASE(
            N = 1,
            types = {"dibantu"},
            K = {6},
            names = {{"uvuvwe", "vwevwe", "onyete", "nyevwe", "ugwemu", "bwem"}} // dibantu oleh Ossas
        );
        CASE(
            N = 1,
            types = {"dibantu"},
            K = {10},
            names = {{"never", "gonna", "give", "you", "up", "neverr", "gonnaa", "let", "youu", "down"}} // copyright Rick Astley
        );
    }

    void TestGroup2() {
        Subtasks({2});

        CASE(
            N = 2,
            types = {"selfie", "selfie"},
            K = {1, 1},
            names = {{"dengklek"}, {"dengklek"}}
        );
        CASE(
            N = 2,
            types = {"selfie", "selfie"},
            K = {1, 1},
            names = {{"dengklek"}, {"ganesh"}}
        );
        CASE(
            N = 2,
            types = {"dibantu", "dibantu"},
            K = {1, 1},
            names = {{"dengklek"}, {"dengklek"}}
        );
        CASE(
            N = 2,
            types = {"dibantu", "dibantu"},
            K = {1, 1},
            names = {{"dengklek"}, {"ganesh"}}
        );
        CASE( // agak tricky
            N = 3,
            types = {"dibantu", "dibantu", "selfie"},
            K = {1, 1, 2},
            names = {{"kwak"}, {"kwok"}, {"kwok", "kwak"}}
        );
    }

    void TestGroup3() {
        Subtasks({2});

        CASE( // tricky parah
            N = 2,
            types = {"dibantu", "selfie"},
            K = {1, 2},
            names = {{"kwak"}, {"kwok", "kwak"}}
        );
        CASE( // tricky parah juga
            N = 3,
            types = {"dibantu", "selfie", "selfie"},
            K = {3, 2, 1},
            names = {{"kwak", "kwek", "kwok"}, {"kwek", "kwak"}, {"kwok"}}
        );

        CASE(N = 20, random(0, 10));
        CASE(N = 20, random(100, 10));
        CASE(N = 50, random(50, 50));
    }

    void TestGroup4() {
        Subtasks({2});

        CASE(N = 60, random(25, 10));
        CASE(N = 60, random(90, 60));
        CASE(N = 70, random(10, 70));
        CASE(N = 100, random(0, 100));
        CASE(N = 100, random(100, 10));
    }

    void TestGroup5() {
        Subtasks({2});

        CASE(N = 100, random(50, 100));
        CASE(N = 100, random(0, 10));
        CASE(N = 100, random(33, 33));
        CASE(N = 100, random(67, 33));
        CASE(N = 100, random(50, 33));
    }

private:
    void random(int selfieProb, int namesPoolSize) {

        vector<string> pool;
        set<string> st;
        for (int i = 0; i < namesPoolSize; i++) {
            string name;
            while (true) {
                name = "";
                int len = rnd.nextInt(8) + 1;
                for (int j = 0; j < len; j++) {
                    char c = 'a' + rnd.nextInt(26);
                    name += c;
                }
                if (!st.count(name)) {
                    break;
                }
            }
            pool.push_back(name);
            st.insert(name);
        }

        types.clear();
        K.clear();
        names.clear();
        for (int i = 0; i < N; i++) {
            types.push_back(rnd.nextInt(100) < selfieProb ? "selfie" : "dibantu");
            int k = rnd.nextInt(10) + 1;
            K.push_back(k);

            rnd.shuffle(pool.begin(), pool.end());
            vector<string> photo;
            for (int j = 0; j < k; j++) {
                photo.push_back(pool[j]);
            }
            names.push_back(photo);
        }

        if (namesPoolSize == 10) {
            int idx = rnd.nextInt(N);
            K[idx] = 10;
            names[idx] = pool;
        }
    }
};
