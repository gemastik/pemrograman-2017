#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

const int MAX_N = 50000;
const int MAX_Q = 50000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int N, M;
    vector<int> Hmin; // Min humour percentage
    vector<int> Hmax; // Max humour percentage
    vector<int> U, V;
    int Q;
    vector<int> X, H; // node, humour

    vector<string> res;

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

    void Constraints() {
        CONS(1 <= N && N <= MAX_N);
        CONS(1 <= M && M <= MAX_N);
        CONS(1 <= Q && Q <= MAX_Q);

        CONS(eachElementLesseq(Hmin, Hmax));

        CONS(eachElementBetween(U, 1, N));
        CONS(eachElementBetween(V, 1, N));
        CONS(noSelfLoop());
        CONS(noDuplicatedEdge());

        CONS(eachElementBetween(X, 1, N));
        CONS(eachElementBetween(H, 0, 100));
    }

    void Subtask1() {
        CONS(eachElementBetween(Hmin, 0, 0));
        CONS(eachElementBetween(Hmax, 100, 100));
    }

    void Subtask2() {
        CONS(eachElementBetween(Hmin, 0, 100));
        CONS(eachElementBetween(Hmax, 0, 100));
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
            "6 6",
            "0 0 0 0 0 0",
            "100 100 100 100 100 100",
            "1 2",
            "1 3",
            "2 4",
            "4 5",
            "5 2",
            "3 6",
            "3",
            "1 50",
            "2 30",
            "3 10"
        });
        Output({
            "Ya",
            "Ya",
            "Tidak"
        });
    }

    void SampleTestCase2() {
        Subtasks({2});
        Input({
            "5 5",
            "50 10 80 25 80",
            "99 90 90 90 95",
            "1 2",
            "1 3",
            "2 4",
            "4 5",
            "5 2",
            "3",
            "1 85",
            "2 50",
            "5 85"
        });
        Output({
            "Ya",
            "Tidak",
            "Ya"
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

        // Many singletons
        CASE(N = 5, M = 1, Q = 20, U.push_back(1), V.push_back(2), easyHumour(), randomQuery());

        CASE(N = 1000, M = 1000, Q = 1000, randomGraph(1, 2, 1), easyHumour(), randomQuery());
        CASE(N = 1000, M = 1000, Q = 1000, randomGraph(1, 2, 1.2), easyHumour(), randomQuery());
        CASE(N = 1000, M = 1000, Q = 1000, randomGraph(1, 3, 1.2), easyHumour(), randomQuery());
        CASE(N = 50000, M = 50000, Q = 50000, randomGraph(1, 3, 1.2), easyHumour(), randomQuery());

        // Anti brute force DFS + find cycle + break
        // Starfish case already filled the humours... but let's replace them with easyHumour
        CASE(N = 50000, M = 50000, Q = 50000, starFishCase(1, 1, 1, 2, 2, 0, 1, 0.2), easyHumour(), randomQuery()); // ------O
        CASE(N = 49900, M = 49900, Q = 50000, starFishCase(3, 1, 3, 5, 10, 2, 2, 0.2), easyHumour(), randomQuery()); // ------O and ------
        CASE(N = 49900, M = 49900, Q = 50000, starFishCase(2, 4, 4, 2, 10, 1, 2, 0.2), easyHumour(), randomQuery()); // 3 armed starfish and -------
    }

    void TestGroup2() {
        Subtasks({2});

        // Many singletons
        CASE(N = 5, M = 1, Q = 20, U.push_back(1), V.push_back(2), randomHumour(60, 80), randomQuery());

        // Random case
        CASE(N = 1000, M = 1000, Q = 1000, randomGraph(1, 2, 1), randomHumour(60, 80), smartRandomQuery());
        CASE(N = 1000, M = 1000, Q = 1000, randomGraph(1, 2, 1.2), randomHumour(20, 30), randomQuery());
        CASE(N = 1000, M = 1000, Q = 1000, randomGraph(1, 3, 1.2), randomHumour(20, 30), smartRandomQuery());
        CASE(N = 50000, M = 50000, Q = 50000, randomGraph(1, 3, 1.2), randomHumour(20, 30), smartRandomQuery());

        // Anti brute force DFS + find cycle + break
        CASE(N = 50000, M = 50000, Q = 50000, starFishCase(1, 1, 1, 2, 2, 0, 1, 0.2), randomQuery()); // ------O
        CASE(N = 49900, M = 49900, Q = 50000, starFishCase(3, 1, 3, 5, 10, 2, 2, 0.2), randomQuery()); // ------O and ------
        CASE(N = 49900, M = 49900, Q = 50000, starFishCase(2, 4, 4, 2, 10, 1, 2, 0.2), randomQuery()); // 3 armed starfish and -------
    }

private:
    // Auxilliary data structure for test case generation
    vector<int> adjList[MAX_N];

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
            if (nodeClusters[i].size() == 1) continue;

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

            if ((u != v) && (edgeSet.count(make_pair(u, v)) == 0)) {
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
            if ((u != v) && (edgeSet.count(make_pair(u, v)) == 0)) {
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

        constructAuxDataStructure();
    }

    /*
    Create graph with this shape:
             /__
       \    /
    -------O
      /     \__
             \
     */
    void starFishCase(int n, int minArmCount, int maxArmCount, int cycleMinSize, int cycleMaxSize, int numWithoutCycle, double cycleEdgesFactor, double armBranchingFactor) {
        U.clear();
        V.clear();
        set<pair<int,int>> edgeSet;
        int nodeLeft = N;
        int edgeLeft = M;

        // Generate cycle sizes
        vector<int> cycleSizes;
        int sizeLeft = N;
        for (int i = 0; i < n; i++) {
            if (i < numWithoutCycle) {
                cycleSizes.push_back(1);
            } else {
                cycleSizes.push_back(rnd.nextInt(cycleMinSize, cycleMaxSize));
            }
            nodeLeft -= cycleSizes.back();
            assert(nodeLeft >= 0); // If this line fails, please adjust the paramters to that N nodes is enough for all starfishes
        }

        // Generate arm counts
        vector<int> armCounts;
        int totalArmCount = 0;
        for (int i = 0; i < n; i++) {
            armCounts.push_back(rnd.nextInt(minArmCount, maxArmCount));
            totalArmCount += armCounts.back();
        }

        // Assign edges to be used on cycles
        vector<int> cycleEdges;
        for (int i = 0; i < n; i++) {
            int maxEdgesOnCycle = cycleSizes[i] * (cycleSizes[i]-1);
            int sz = min((int)(cycleEdgesFactor * cycleSizes[i]), maxEdgesOnCycle);

            edgeLeft -= sz;
            assert(edgeLeft >= 0); // If this line fails, please adjust the paramters to that M edges is enough for all starfishes

            cycleEdges.push_back(sz);
        }

        // Construct starfishes
        int nextNodeIdx = 0;
        int armNodeCount = nodeLeft / totalArmCount; // We will deduct the excess nodeLeft/edgeLeft after creating all starfishes
        for (int i = 0; i < n; i++) {
            vector<int> cycleNodes;
            for (int j = 0; j < cycleSizes[i]; j++) {
                cycleNodes.push_back(nextNodeIdx++);
            }

            // Create minimalist edges to form cycle
            int cycleEdgeUsed = 0;
            if (cycleNodes.size() > 1) {
                for (int j = 0; j < cycleNodes.size(); j++) {
                    int u = cycleNodes[j];
                    int v = cycleNodes[(j+1) % cycleNodes.size()];

                    edgeSet.insert(make_pair(u, v));
                    cycleEdgeUsed++;
                }
            }
            // Spend the remaining edges budgeted for this cycle
            while (cycleEdgeUsed < cycleEdges[i]) {
                int u = cycleNodes[rnd.nextInt(0, cycleNodes.size()-1)];
                int v = cycleNodes[rnd.nextInt(0, cycleNodes.size()-1)];

                if ((u != v) && (edgeSet.count(make_pair(u, v)) == 0)) {
                    edgeSet.insert(make_pair(u, v));
                    cycleEdgeUsed++;
                }
            }

            // Create arms
            for (int arm = 0; arm < armCounts[i]; arm++) {
                int mainArmNodeCount = (int)((1.0 - armBranchingFactor) * armNodeCount);
                int branchedArmNodeCount = armNodeCount - mainArmNodeCount;
                vector<int> armNodes;
                for (int j = 0; j < mainArmNodeCount; j++) {
                    armNodes.push_back(nextNodeIdx++);
                    nodeLeft--;
                }
                for (int j = 1; j < mainArmNodeCount; j++) {
                    edgeSet.insert(make_pair(armNodes[j-1], armNodes[j]));
                    edgeLeft--;
                }
                // Connect arm to cycle
                edgeSet.insert(make_pair(armNodes.back(), cycleNodes[rnd.nextInt(0, cycleNodes.size()-1)]));
                edgeLeft--;

                // Spend branched arms
                for (int j = 0; j < branchedArmNodeCount; j++) {
                    nodeLeft--;
                    int nodeIdx = nextNodeIdx++;

                    edgeSet.insert(make_pair(nodeIdx, armNodes[rnd.nextInt(0, armNodes.size()-1)]));
                    edgeLeft--;
                }
            }

            // Set humour
            int humourBeam = rnd.nextInt(40, 60);
            int maxHmin = (100 - humourBeam) / 2;
            int minHmax = 100 - maxHmin;
            for (int j = 0; j < cycleSizes[i] + armNodeCount*armCounts[i]; j++) {
                int hMin = rnd.nextInt(0, maxHmin);
                int hMax = rnd.nextInt(minHmax, 100);
                Hmin.push_back(hMin);
                Hmax.push_back(hMax);
            }
        }

        // Deduct excess edges
        M -= edgeLeft;
        N -= nodeLeft;
        fprintf(stderr, "[%d %d] ", N, M);

        // Dump all to U and V
        for (auto pii : edgeSet) {
            int u = pii.first;
            int v = pii.second;
            U.push_back(u+1);
            V.push_back(v+1);
        }

        constructAuxDataStructure();
    }

    void randomHumour(int minHumourRange, int maxHumourRange) {
        Hmin.clear();
        Hmax.clear();
        for (int i = 0; i < N; i++) {
            int humourRange = rnd.nextInt(minHumourRange, maxHumourRange);
            int hMin = rnd.nextInt(0, 100-humourRange-1);
            int hMax = hMin + humourRange;

            Hmin.push_back(hMin);
            Hmax.push_back(hMax);
        }
    }

    void easyHumour() {
        Hmin.clear();
        Hmax.clear();
        for (int i = 0; i < N; i++) {
            Hmin.push_back(0);
            Hmax.push_back(100);
        }
    }

    // The next node's humour range is roughly the shifted version of previous node
    void wavingHumour(int minHumourRange, int maxHumourRange, double overlapFrac) {
        Hmin.clear();
        Hmax.clear();
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
            // Heuristic: pick the top 33% nodes to ensure we still about 66% nodes left to be travelled
            int x = rnd.nextInt(0, N/3);

            for (int i = Hmin[x]; i <= Hmax[x]; i++) {
                X.push_back(x+1);
                H.push_back(i);

                if (X.size() == Q) break;
            }
        }
    }

    // Construct auxilliary data structures used for generating humour/queries
    void constructAuxDataStructure() {
        for (int i = 0; i < N; i++) {
            adjList[i].clear();
        }
        for (int i = 0; i < M; i++) {
            int u = U[i] - 1;
            int v = V[i] - 1;
            adjList[u].push_back(v);
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
