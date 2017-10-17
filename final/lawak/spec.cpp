#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

const int MAX_N = 50000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N, M;
    vector<int> Hmin; // Min humour percentage
    vector<int> Hmax; // Max humour percentage
    vector<int> U, V;
    int Q;
    vector<int> X, H; // node, humour

    vector<int> res;

    void InputFormat() {
        LINE(N, M);
        LINE(Hmin % SIZE(N));
        LINE(Hmax % SIZE(N));
        LINES(U, V) % SIZE(M);
        LINE(Q);
        LINES(X, H) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(res);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 10);
    }

    void Constraints() {
        CONS(eachElementBetween(Hmin, 0, 100));
        CONS(eachElementBetween(Hmax, 0, 100));
        CONS(eachElementLesseq(Hmin, Hmax));

        CONS(eachElementBetween(U, 1, N));
        CONS(eachElementBetween(V, 1, N));
        CONS(noSelfLoop());
        CONS(noDuplicatedEdge());

        CONS(eachElementBetween(X, 1, N));
        CONS(eachElementBetween(H, 0, 100));
    }

    void Subtask1() {
        CONS(1 <= N && N <= 1000);
        CONS(1 <= M && M <= 1000);
        CONS(1 <= Q && Q <= 1000);

    }

    void Subtask2() {
        CONS(1 <= N && N <= MAX_N);
        CONS(1 <= M && M <= MAX_N);
        CONS(1 <= Q && Q <= 50000);
    }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        return all_of(v.begin(), v.end(), [lo, hi](int a) {return lo <= a && a <= hi;});
    }

    bool eachElementLesseq(const vector<int>& v1, const vector<int>& v2) {
        if (v1.size() != v2.size()) return false;

        for (int i = 0; i < v1.size(); i++) {
            if (v1[i] > v2[i]) return false;
        }
        return true;
    }

    bool noSelfLoop() {
        for (int i = 0; i < U.size(); i++) {
            if (U[i] == V[i]) return false;
        }
        return true;
    }

    bool noDuplicatedEdge() {
        set<pair<int,int>> edges;
        for (int i = 0; i < U.size(); i++) {
            pair<int,int> edge = make_pair(U[i], V[i]);

            if (edges.count(edge) > 0) return false;
            edges.insert(edge);
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1, 2});
        Input({
            "5 5",
            "20 10 50 60 40",
            "80 50 90 80 60",
            "1 2",
            "1 3",
            "2 4",
            "2 5",
            "5 2",
            "3",
            "1 45",
            "2 45",
            "1 70"
        });
        Output({
            "5",
            "3",
            "3"
        });
    }

    void BeforeTestCase() {
        N = M = Q = 0;
        Hmin.clear();
        Hmax.clear();
        U.clear();
        V.clear();
        X.clear();
        H.clear();
    }

    void AfterTestCase() {
        shufflePairedVector(X, H);
        shufflePairedVector(U, V);
        remapNodeIndex();
    }

    void TestGroup1() {
        Subtasks({1, 2});

        // Random case
        CASE(N = 1000, M = 1000, Q = 1000, randomGraph(100, 150, 1), randomHumour(60, 80), smartRandomQuery());
        CASE(N = 1000, M = 1000, Q = 1000, randomGraph(100, 150, 1.2), randomHumour(60, 80), randomQuery());
        CASE(N = 1000, M = 1000, Q = 1000, randomGraph(12, 50, 1), wavingHumour(40, 60, 0.8), randomQuery());

        // Answers close to N
        CASE(N = 1000, M = 1000, Q = 1000, randomGraph(12, 50, 1), wavingHumour(70, 80, 0.9), smartRandomQuery());

        // Answers close to 2
        CASE(N = 1000, M = 1000, Q = 1000, randomGraph(12, 50, 1), wavingHumour(30, 70, 0.4), smartRandomQuery());

        // Small clusters
        CASE(N = 1000, M = 1000, Q = 1000, randomGraph(2, 15, 1), wavingHumour(30, 70, 0.7), smartRandomQuery());

        // Large clusters
        CASE(N = 1000, M = 1000, Q = 1000, randomGraph(100, 150, 1), wavingHumour(30, 40, 0.4), smartRandomQuery());
    }

    void TestGroup2() {
        Subtasks({2});

        // Random case
        CASE(N = 50000, M = 50000, Q = 50000, randomGraph(10000, 15000, 1), randomHumour(60, 80), smartRandomQuery());
        CASE(N = 50000, M = 50000, Q = 50000, randomGraph(1200, 5000, 1), wavingHumour(40, 60, 0.8), randomQuery());

        // Answers close to N
        CASE(N = 50000, M = 50000, Q = 50000, randomGraph(1200, 5000, 1), wavingHumour(70, 80, 0.9), smartRandomQuery());
    }

private:
    // Auxilliary data structure for test case generation
    vector<int> adjList[100001];

    void randomGraph(int minClusterSize, int maxClusterSize, double interClusterEdgeFrac) {
        U.clear();
        V.clear();
        set<pair<int,int>> edgeSet;

        // Generate cluster sizes
        vector<int> clusterSizes;
        int sizeLeft = N;
        while (sizeLeft > 0) {
            int sz = rnd.nextInt(minClusterSize, maxClusterSize);

            sz = min(sz, sizeLeft);
            clusterSizes.push_back(sz);

            sizeLeft -= sz;
        }

        int interClusterEdgeCount = (int)(interClusterEdgeFrac * clusterSizes.size() / N * M);
        int intraClusterEdgeCount = M - interClusterEdgeCount;

        // Inflate each cluster
        vector<vector<int>> nodeClusters;
        int newNodeIdx = 0;
        for (int i = 0; i < clusterSizes.size(); i++) {
            vector<int> nodes;
            for (int j = 0; j < clusterSizes[i]; j++) {
                nodes.push_back(newNodeIdx++);
            }
            nodeClusters.push_back(nodes);
        }

        // Attach edges to make each nodes within cluster strongly connected
        int intraClusterEdgeUsed = 0;
        for (int i = 0; i < nodeClusters.size(); i++) {
            for (int j = 0; j < nodeClusters[i].size(); j++) {
                int u = nodeClusters[i][j];
                int v = nodeClusters[i][(j+1) % nodeClusters[i].size()];

                edgeSet.insert(make_pair(u, v));
                intraClusterEdgeUsed++;

                if (intraClusterEdgeUsed == intraClusterEdgeCount) break;
            }
            if (intraClusterEdgeUsed == intraClusterEdgeCount) break;
        }
        // Spend the extra intraClusterEdge
        while (intraClusterEdgeUsed < intraClusterEdgeCount) {
            int clusterIdx = rnd.nextInt(0, clusterSizes.size()-1);
            int u = nodeClusters[clusterIdx][rnd.nextInt(0, nodeClusters[clusterIdx].size()-1)];
            int v = nodeClusters[clusterIdx][rnd.nextInt(0, nodeClusters[clusterIdx].size()-1)];

            if (edgeSet.count(make_pair(u, v)) == 0) {
                edgeSet.insert(make_pair(u, v));
                intraClusterEdgeUsed++;
            }
        }

        // Attach strongly connected components together
        int interClusterEdgeUsed = 0;
        if (interClusterEdgeFrac > 1 - 1e-8) {
            for (int i = 0; i < clusterSizes.size()-1; i++) {
                int next = rnd.nextInt(i+1, clusterSizes.size()-1);

                int c1 = i;
                int c2 = next;
                int u = nodeClusters[c1][rnd.nextInt(0, nodeClusters[c1].size()-1)];
                int v = nodeClusters[c2][rnd.nextInt(0, nodeClusters[c2].size()-1)];
                edgeSet.insert(make_pair(u, v));
                interClusterEdgeUsed++;
            }
        }
        while (interClusterEdgeUsed < interClusterEdgeCount) {
            int c1 = rnd.nextInt(0, clusterSizes.size()-1);
            int c2 = rnd.nextInt(0, clusterSizes.size()-1);
            if (c1 == c2) continue;

            if (c1 > c2) swap(c1, c2);

            int u = nodeClusters[c1][rnd.nextInt(0, nodeClusters[c1].size()-1)];
            int v = nodeClusters[c2][rnd.nextInt(0, nodeClusters[c2].size()-1)];
            if (edgeSet.count(make_pair(u, v)) == 0) {
                edgeSet.insert(make_pair(u, v));
                interClusterEdgeUsed++;
            }
        }

        // Dump all to U and V
        for (auto pii : edgeSet) {
            int u = pii.first;
            int v = pii.second;
            U.push_back(u+1);
            V.push_back(v+1);
        }

        // Construct auxilliary data structures
        for (int i = 0; i < N; i++) {
            adjList[i].clear();
        }
        for (int i = 0; i < M; i++) {
            int u = U[i] - 1;
            int v = V[i] - 1;
            adjList[u].push_back(v);
        }
    }

    void randomHumour(int minHumourRange, int maxHumourRange) {
        for (int i = 0; i < N; i++) {
            int humourRange = rnd.nextInt(minHumourRange, maxHumourRange);
            int hMin = rnd.nextInt(0, 100-humourRange-1);
            int hMax = hMin + humourRange;

            Hmin.push_back(hMin);
            Hmax.push_back(hMax);
        }
    }

    // The next node's humour range is roughly the shifted version of previous node
    void wavingHumour(int minHumourRange, int maxHumourRange, double overlapFrac) {
        bool visited[N];
        memset(visited, 0, sizeof(visited));

        for (int i = 0; i < N; i++) {
            Hmin.push_back(0);
            Hmax.push_back(0);
        }
        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                int humourRange = rnd.nextInt(minHumourRange, maxHumourRange);
                int hMin = rnd.nextInt(0, 100-humourRange-1);
                int hMax = hMin + humourRange;
                setWavingHumour(visited, i, hMin, hMax, minHumourRange, maxHumourRange, overlapFrac, true);
            }
        }
    }

    void randomQuery() {
        for (int i = 0; i < Q; i++) {
            int x = rnd.nextInt(0, N-1);

            int h = rnd.nextInt(Hmin[x], Hmax[x]);

            X.push_back(x+1);
            H.push_back(h);
        }
    }

    void smartRandomQuery() {
        while (X.size() < Q) {
            // Heuristic: pick the top 33% to ensure we still about 66% nodes left to be travelled
            int x = rnd.nextInt(0, N/3);

            for (int i = Hmin[x]; i <= Hmax[x]; i++) {
                X.push_back(x+1);
                H.push_back(i);

                if (X.size() == Q) break;
            }
        }
    }

    void setWavingHumour(bool visited[], int x, int prevHMin, int prevHMax, const int minHumourRange, const int maxHumourRange, const double overlapFrac, bool movingRight) {
        visited[x] = true;

        int shift = (int)(overlapFrac*(prevHMax - prevHMin + 1));
        int hMin, hMax;
        if (movingRight) {
            hMin = clampPercentage(prevHMin + shift);
        } else {
            hMin = clampPercentage(prevHMin - shift);
        }
        hMax = clampPercentage(hMin + rnd.nextInt(minHumourRange, maxHumourRange));

        Hmin[x] = hMin;
        Hmax[x] = hMax;

        bool nextMovingRight = (hMax > (1-overlapFrac)*100) ? true : false;
        for (int nextNode : adjList[x]) {
            if (!visited[nextNode]) {
                setWavingHumour(visited, nextNode, hMin, hMax, minHumourRange, maxHumourRange, overlapFrac, nextMovingRight);
            }
        }
    }

    int clampPercentage(int x) {
        if (x < 0) return 0;
        if (x > 100) return 100;
        return x;
    }

    // Useful to avoid "caching" solution
    void shufflePairedVector(vector<int> v1, vector<int> v2) {
        assert(v1.size() == v2.size());
        for (int i = 0; i < v1.size(); i++) {
            int a = rnd.nextInt(0, (int)v1.size()-1);
            int b = rnd.nextInt(0, (int)v1.size()-1);
            swap(v1[a], v1[b]);
            swap(v2[a], v2[b]);
        }
    }

    void remapNodeIndex() {
        int mappedTo[N];
        for (int i = 0; i < N; i++) {
            mappedTo[i] = i;
        }
        rnd.shuffle(mappedTo, mappedTo + N);

        for (int i = 0; i < U.size(); i++) {
            // Handling 1-based vs 0-based
            U[i] = mappedTo[U[i]-1] + 1;
            V[i] = mappedTo[V[i]-1] + 1;
        }
        for (int i = 0; i < X.size(); i++) {
            X[i] = mappedTo[X[i]-1] + 1;
        }
    }
};
