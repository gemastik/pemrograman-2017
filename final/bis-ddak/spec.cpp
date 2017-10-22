#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

template<typename T>
inline bool inRange(const T& z, const T& lb, const T& ub) { return lb <= z && z <= ub; }

const int MAX_N = 250;
const int SMALL_MAX_N = 12;
const int MAX_EDGE_COST = 2000000000 / MAX_N;

class ProblemSpec : public BaseProblemSpec {
    using vi = vector<int>;

protected:
    int T;

    int N, M;
    vi U, V, W;

    int ANS_COST, ANS_NUM_CIRCUIT;
    vector<vi> ANS_CIRCUITS;
    vi ANS_CIRCUITS_SIZE;
    vi LOOP_COST;

    string MUSTAHIL;

    void InputFormat() {
        LINE(N, M);
        LINE(LOOP_COST % SIZE(N));
        LINES(U, V, W) % SIZE(M);
    }

    void OutputFormat() {
        LINE(ANS_COST, ANS_NUM_CIRCUIT);
        LINES(ANS_CIRCUITS_SIZE, ANS_CIRCUITS) % SIZE(ANS_NUM_CIRCUIT);
    }
    
    void StyleConfig() {
        CustomScorer();
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(inRange(T, 1, 5));
    }

    void Constraints() {
        CONS(inRange(M, 0, N * (N - 1)));
        CONS(all_of(LOOP_COST.begin(), LOOP_COST.end(), [&](int w) { return inRange(w, 1, MAX_EDGE_COST); }));
        CONS(all_of(W.begin(), W.end(), [&](int w) { return inRange(w, 1, MAX_EDGE_COST); }));
        CONS(all_of(U.begin(), U.end(), [&](int u) { return inRange(u, 1, N); }));
        CONS(all_of(V.begin(), V.end(), [&](int v) { return inRange(v, 1, N); }));
        CONS(hasNoSelfLoop(U, V));
        CONS(allEdgesAreUnique(U, V));
    }

    void Subtask1() {
        CONS(inRange(N, 1, SMALL_MAX_N));
    }

    void Subtask2() {
        CONS(inRange(N, 1, MAX_N));
    }

private:
    bool hasNoSelfLoop(const vi& U, const vi& V) {
        for (int i = 0; i < U.size(); ++i) {
            if (U[i] == V[i]) {
                return false;
            }
        }
        return true;
    }

    bool allEdgesAreUnique(const vi& U, const vi& V) {
        set<pair<int, int>> edges_set;
        edges_set.clear();
        for (int i = 0; i < (int) U.size(); ++i) {
            const int& u = U[i];
            const int& v = V[i];
            if (edges_set.find(make_pair(u, v)) != edges_set.end()) {
                return false;
            }
            edges_set.insert(make_pair(u, v));
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
    using vi = vector<int>;

protected:
    void BeforeTestCase() {
        U.clear();
        V.clear();
        W.clear();
        LOOP_COST.clear();
        N = M = 0;
    }

    void AfterTestCase() {
        M = (int) U.size();
        shuffleEdges();
        shuffleIndices();
    }

    void SampleTestCase1() {
        Subtasks({1, 2});
        Input({
            "2 2",
            "9 10",
            "1 2 3",
            "2 1 4"
        });
        Output({
            "7 1",
            "2 1 2"
        });
    }

    void SampleTestCase2() {
        Subtasks({1, 2});
        Input({
            "3 6",
            "2 2 2",
            "1 2 1",
            "2 3 1",
            "3 1 1",
            "2 1 1",
            "3 2 1",
            "1 3 1"
        });
        Output({
            "3 1",
            "3 1 2 3"
        });
    }

    void SampleTestCase3() {
        Subtasks({1, 2});
        Input({
            "2 2",
            "1 2",
            "1 2 3",
            "2 1 4"
        });
        Output({
            "3 0"
        });
    }

    void SampleTestCase4() {
        Subtasks({1, 2});
        Input({
            "4 4",
            "2 2 2 2",
            "1 2 1",
            "2 1 1",
            "3 4 1",
            "4 3 1"
        });
        Output({
            "4 2",
            "2 3 4",
            "2 2 1"
        });
    }

    void TestGroup1() {
        Subtasks({1, 2});

        CASE( // use the loop
            N = 1,
            M = 0,
            LOOP_COST = {MAX_EDGE_COST},
            U = V = W = {}
        );
        CASE( // use the loops, with twist that the "lightest" edge not taken (greedy would fail)
            N = 2,
            M = 2,
            LOOP_COST = {2, 3},
            U = {1, 2},
            V = {2, 1},
            W = {1, 5}
        );
        CASE( // change the routes, with redundant edges
            N = 2,
            M = 2,
            LOOP_COST = {1, 6},
            U = {1, 2},
            V = {2, 1},
            W = {2, 4}
        );
        CASE( // triangle, ans: one loop, one circuit
            N = 3,
            M = 6,
            LOOP_COST = {2, 9, 8},
            U = {1, 1, 2, 2, 3, 3},
            V = {2, 3, 1, 3, 1, 2},
            W = {9, 9, 4, 4, 5, 3}
        );
        CASE( // triangle, all in circuit, with twist that the "lightest" edge(s) not taken
            N = 3,
            M = 6,
            LOOP_COST = {6, 6, 6},
            U = {1, 1, 2, 2, 3, 3},
            V = {2, 3, 1, 3, 1, 2},
            W = {1, 2, 2, 4, 4, 2}
        );
    }

    void TestGroup2() {
        Subtasks({1, 2});

        CASE( // triangle, all in circuit
            N = 3,
            M = 6,
            LOOP_COST = {6, 6, 6},
            U = {1, 1, 2, 2,   3, 3},
            V = {2, 3, 1, 3,   1, 2},
            W = {1, 1, 5, 1, 100, 5}
        );
        CASE(
            N = 4,
            M = 12,
            LOOP_COST = {2, 3, 3, 6},
            U = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4},
            V = {2, 3, 4, 1, 3, 4, 1, 2, 4, 1, 2, 3},
            W = {3, 4, 7, 3, 3, 2, 4, 3, 3, 2, 4, 5}
        );
        CASE(
            N = 4,
            M = 7,
            LOOP_COST = {3, 3, 3, 3},
            U = {1, 1, 1, 2, 2, 3, 4},
            V = {2, 3, 4, 3, 4, 4, 1},
            W = {2, 2, 2, 2, 2, 2, 6}
        );
        CASE(
            N = 4,
            M = 6,
            LOOP_COST = {MAX_EDGE_COST, MAX_EDGE_COST, MAX_EDGE_COST, MAX_EDGE_COST},
            U = {1, 1, 1, 2, 2, 3},
            V = {2, 3, 4, 3, 4, 4},
            W = {MAX_EDGE_COST, MAX_EDGE_COST, MAX_EDGE_COST, MAX_EDGE_COST, MAX_EDGE_COST, MAX_EDGE_COST}
        );
        CASE(
            N = 4,
            M = 6,
            LOOP_COST = {MAX_EDGE_COST, MAX_EDGE_COST, MAX_EDGE_COST, MAX_EDGE_COST},
            U = {1, 1, 1, 2, 2, 3},
            V = {2, 3, 4, 3, 4, 4},
            W = {2, 2, 2, 2, 2, 2}
        );
    }
    
    void TestGroup3() {
        Subtasks({1, 2});

        CASE(DAGCase(N = SMALL_MAX_N, true));
        CASE(DAGCase(N = SMALL_MAX_N, true, true));
        CASE(KecebongCase(N = SMALL_MAX_N, 1));
        CASE(KecebongCase(N = SMALL_MAX_N, 1, true));
        CASE(KecebongCase(N = SMALL_MAX_N, 2, true));
    }
    
    void TestGroup4() {
        Subtasks({1, 2});

        CASE(DAGCase(N = SMALL_MAX_N, true));
        CASE(DAGCase(N = SMALL_MAX_N, true, true));
        CASE(KecebongCase(N = SMALL_MAX_N, 1));
        CASE(KecebongCase(N = SMALL_MAX_N, 1, true));
        CASE(KecebongCase(N = SMALL_MAX_N, 2, true));
    }
    
    void TestGroup5() {
        Subtasks({2});

        CASE(DAGCase(N = MAX_N, false));
        CASE(DAGCase(N = MAX_N, false, true));
        CASE(KecebongCase(N = MAX_N, 1));
        CASE(KecebongCase(N = MAX_N, rnd.nextInt(2, (int) sqrt(MAX_N)), false));
        CASE(KecebongCase(N = MAX_N, rnd.nextInt(2, (int) sqrt(MAX_N)), true));
    }
    
    void TestGroup6() {
        Subtasks({2});

        CASE(DAGCase(N = MAX_N, false));
        CASE(DAGCase(N = MAX_N, false, true));
        CASE(KecebongCase(N = MAX_N, 1));
        CASE(KecebongCase(N = MAX_N, rnd.nextInt(2, (int) sqrt(MAX_N)), false));
        CASE(KecebongCase(N = MAX_N, rnd.nextInt(2, (int) sqrt(MAX_N)), true));
    }

private:
    void shuffleEdges() {
        for (int i = 0; i < M; ++i) {
            int x = rnd.nextInt(i + 1);
            swap(U[x], U[i]);
            swap(V[x], V[i]);
            swap(W[x], W[i]);
        }
    }

    void shuffleIndices() {
        vi indices;
        indices.assign(N, 0);
        for (int i = 0; i < N; ++i) {
            indices[i] = i + 1;
        }
        rnd.shuffle(indices.begin(), indices.end());

        for (int i = 0; i < M; ++i) {
            int& u = U[i];
            int& v = V[i];
            u = indices[u - 1];
            v = indices[v - 1];
        }
    }

    void addNoiseEdges(int N) {
        set<pair<int, int>> used_edges;
        for (int i = 0; i < (int) U.size(); ++i) {
            used_edges.insert(make_pair(U[i],V[i]));
        }

        vector<pair<int, int>> unused_edges;
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (i != j && used_edges.find(make_pair(i, j)) == used_edges.end()) {
                    unused_edges.emplace_back(i, j);
                }
            }
        }

        rnd.shuffle(unused_edges.begin(), unused_edges.end());

        M = (int) U.size();
        int limitEdges = min(N * (N - 1), (int) unused_edges.size());
        int limitM = M + rnd.nextInt((limitEdges - M) * 2 / 3, limitEdges - M);
        limitM = min(limitM, (int) unused_edges.size());
        for (int i = 0; i < limitM - M; ++i) {
            const int& u = unused_edges[i].first;
            const int& v = unused_edges[i].second;
            addEdgeWithRandomWeight(u, v);
        }
    }

    void assignRandomLoopCost(int N) {
        LOOP_COST.assign(N, 0);
        for (int i = 0; i < N; ++i) {
            LOOP_COST[i] = rnd.nextInt(1, MAX_EDGE_COST);
        }
    }

    void addEdgeWithRandomWeight(int u, int v) {
        addEdge(u, v, rnd.nextInt(1, MAX_EDGE_COST));
    }

    void addEdge(int u, int v, int w) {
        U.push_back(u);
        V.push_back(v);
        W.push_back(w);
    }

    void DAGCase(int N, bool complete = false, bool withNoise = false) {
        assignRandomLoopCost(N);

        if (complete) {
            for (int i = 1; i <= N; ++i) {
                for (int j = i + 1; j <= N; ++j) {
                    addEdgeWithRandomWeight(i, j);
                    ++M;
                }
            }
        } else {
            M = rnd.nextInt(N, N * (N - 1));
            M = min(M, N * (N - 1) / 2);
            vector<pair<int, int>> pairs;
            for (int i = 1; i <= N; ++i) {
                for (int j = i + 1; j <= N; ++j) {
                    pairs.push_back(make_pair(i, j));
                }
            }

            if (M == N * (N - 1) / 2) {
                M -= rnd.nextInt(M / 2);
            }

            for (int i = 0; i < min(M, (int) pairs.size()); ++i) {
                addEdgeWithRandomWeight(pairs[i].first, pairs[i].second);
            }
        }

        if (withNoise) {
            addNoiseEdges(N);
        }
    }

    /**
     * A -> B -> C -> D -> E
     *           ^         |
     *           |         v
     *           H <- G <- F
     */
    void KecebongCase(int N, int numKecebong = 1, bool withNoise = false) {
        assignRandomLoopCost(N);

        int nodesPerKecebong = N / numKecebong;

        int MAX_EDGE_COST_FOR_KECEBONG = sqrt(MAX_EDGE_COST);
        
        for (int kecebong = 1; kecebong <= numKecebong; ++kecebong) {
            int node = (kecebong - 1) * nodesPerKecebong + 1;
            int firstNode = node;
            for (int i = 0; i < nodesPerKecebong - 1; ++i) {
                addEdge(node, node + 1, rnd.nextInt(1, MAX_EDGE_COST_FOR_KECEBONG));
                ++node;
            }
            int u = rnd.nextInt(firstNode, node - 1);
            addEdge(node, u, rnd.nextInt(1, MAX_EDGE_COST_FOR_KECEBONG));
        }

        M = (int) U.size();

        if (withNoise) {
            addNoiseEdges(N);
        }
    }
};
