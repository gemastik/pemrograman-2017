#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

#define REP(i,n) for (int i = 0; i < n; i++)

using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;

    int R, C, N;
    vector<vector<int>> G;

    int res;

    void InputFormat() {
        LINE(R, C, N);
        GRID(G) % SIZE(R, C);
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
        CONS(2 <= R && R <= 50);
        CONS(1 <= C && C <= 50);
        CONS(validGrid());
    }

    void Subtask1() {
        CONS(N == 1);
    }

    void Subtask2() {
        CONS(1 <= N && N <= C);
    }

private:
    bool validGrid() {
        set<int> laptops;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                int c = G[i][j];

                if (!isValidCell(c)) return false;

                if (i == 0 && c) return false;

                if (-N <= c && c <= -1) {
                    if (!laptops.insert(c).second) return false;
                }
            }
        }
        return laptops.size() == N;
    }

    bool isValidCell(int c) {
        return -N <= c && c <= 9;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1, 2});
        Input({
            "3 1 1",
            "0",
            "3",
            "-1"
        });
        Output({"9"});
    }

    void SampleTestCase2() {
        Subtasks({1, 2});
        Input({
            "3 2 1",
            "0 0",
            "3 1",
            "-1 2"
        });
        Output({"17"});
    }

    void BeforeTestCase() {
        G.clear();
        N = 0;
    }

    void TestGroup1() {
        Subtasks({1, 2});

        // Short tables
        CASE(makeGrid(2, 1), putLaptop(1, 0));
        CASE(makeGrid(50, 1), putLaptop(49, 0));
        CASE(makeGrid(50, 50), putLaptop(49, 25));
        CASE(makeGrid(2, 50), putLaptop(1, 25));

        // Spiral cabling
        CASE(R = 5, C = 3, N = 1, G = {
            {0, 0, 0},
            {9, 9, 9},
            {0, 5, 9},
            {9, 3, 9},
            {-1, 0, 0},
        });

        // Tall tables
        CASE(R = 5, C = 3, N = 1, G = {
            {0, 0, 0},
            {9, 9, 9},
            {9, 9, 9},
            {9, 9, 9},
            {-1, 0, 0},
        });

        CASE(makeGrid(10, 10), randomCheckerboard(), closestToColokans(1));
        CASE(makeGrid(50, 50), randomCheckerboard(), furthestFromColokans(1));

        // Just randoms
        CASE(makeGrid(50, 50), randomBoard(), putLaptop(25, 25));
        CASE(makeGrid(50, 50), randomBoard(), putLaptop(49, 25));
    }

    void TestGroup2() {
        Subtasks({1, 2});

        CASE(makeGrid(50, 50), randomBoard(), putLaptop(25, 25));
        CASE(makeGrid(50, 50), randomBoard(), putLaptop(1, 0));
        CASE(makeGrid(50, 50), randomBoard(), putLaptop(1, 49));
        CASE(makeGrid(50, 50), randomBoard(), putLaptop(49, 0));
        CASE(makeGrid(50, 50), randomBoard(), putLaptop(49, 49));

        CASE(makeGrid(50, 50), randomCheckerboard(), putLaptop(25, 25));
        CASE(makeGrid(50, 50), randomCheckerboard(), putLaptop(49, 26));
        CASE(makeGrid(50, 50), maxCheckerboard(), putLaptop(49, 24));
        CASE(makeGrid(50, 50), maxCheckerboard(), putLaptop(49, 25));
        CASE(makeGrid(50, 50), maxCheckerboard(), putLaptop(49, 26));
    }

    void TestGroup3() {
        Subtasks({2});

        CASE(makeGrid(2, 2), putLaptop(1, 1), putLaptop(1, 0));
        CASE(makeGrid(50, 50), randomBoard(), closestToColokans(10));
        CASE(makeGrid(50, 50), maxCheckerboard(), furthestFromColokans(25));
        CASE(makeGrid(50, 50), randomCheckerboard(), closestToColokans(30));
        CASE(makeGrid(50, 50), randomCheckerboard(), furthestFromColokans(40));
        CASE(makeGrid(50, 50), maxCheckerboard(), closestToColokans(50));
        CASE(makeGrid(50, 50), maxCheckerboard(), furthestFromColokans(50));
        CASE(makeGrid(50, 50), randomBoard(), randomLaptops(25));
        CASE(makeGrid(50, 50), randomCheckerboard(), randomLaptops(25));
        CASE(makeGrid(50, 50), maxCheckerboard(), randomLaptops(25));
    }

private:
    void makeGrid(int r, int c) {
        R = r;
        C = c;
        REP(i, r) G.push_back(vector<int>(c));
    }

    void putLaptop(int r, int c) {
        G[r][c] = -(++N);
    }

    void randomCheckerboard() {
        REP(r, R) REP(c, C) {
            if (r && (r+c) % 2) G[r][c] = rnd.nextInt(10);
        }
    }

    void maxCheckerboard() {
        REP(r, R) REP(c, C) {
            if (r && (r+c) % 2) G[r][c] = 9;
        }
    }

    void randomBoard() {
        REP(r, R) REP(c, C) {
            if (r) G[r][c] = rnd.nextInt(10);
        }
    }

    void closestToColokans(int n) {
        G[1] = createRowOfLaptops(n);
    }

    void furthestFromColokans(int n) {
        G[R-1] = createRowOfLaptops(n);
    }

    vector<int> createRowOfLaptops(int n) {
        vector<int> row(C);
        REP(i, n) row[i] = 1;
        rnd.shuffle(row.begin(), row.end());

        vector<int> laptops(n);
        REP(i, n) laptops[i] = -i-1;
        rnd.shuffle(laptops.begin(), laptops.end());

        REP(i, C) if (row[i]) row[i] = laptops[N++];
        return row;
    }

    void randomLaptops(int n) {
        vector<int> grid((R-1)*C);
        REP(i, n) grid[i] = 1;
        rnd.shuffle(grid.begin(), grid.end());

        vector<int> laptops(n);
        REP(i, n) laptops[i] = -i-1;
        rnd.shuffle(laptops.begin(), laptops.end());

        REP(i, (R-1)*C) if (grid[i]) G[i/C+1][i%C] = laptops[N++];
    }
};
