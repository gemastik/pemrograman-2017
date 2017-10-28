#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
using namespace std;

int wa() {
    printf("WA\n");
    exit(0);
}

int ac() {
    printf("AC\n");
    exit(0);
}
const int MAXM = 20000;

bool read_sol(FILE* reader, int N, int M, int K) {
    char verdict[50];
    if (!fscanf(reader, "%s", verdict)) wa();
    if (strcmp(verdict,"mustahil") == 0) return 0;
    if (strcmp(verdict,"mungkin") != 0) wa();

    vector<pair<int, pair<int,int> > > medals(M);
    for (int i=0;i<N;i++){
        int a,b,c;
        if (fscanf(reader, "%d%d%d", &a, &b, &c) != 3) wa();
        if (a <= 0 || a > M) wa();
        if (b <= 0 || b > M) wa();
        if (c <= 0 || c > M) wa();
        if (a == b || a == c || b == c) wa();
        a--; b--; c--;
        medals[a].first++;
        medals[b].second.first++;
        medals[c].second.second++;
    }

    sort(medals.begin(), medals.end());
    reverse(medals.begin(), medals.end());
    int winners = 0;
    for (int i=0;i<M;i++){
        if (medals[i] == medals[0]) winners++;
    }
    if (winners != K) {
        wa();
    }

    return 1;
}

int main(int argc, char** argv) {
    FILE* tc_in = fopen(argv[1], "r");
    FILE* tc_out = fopen(argv[2], "r");
    FILE* tc_con = fopen(argv[3], "r");

    int T;
    fscanf(tc_in, "%d", &T);
    for (int i = 0; i < T; i++) {
        int N,M,K;

        fscanf(tc_in, "%d%d%d", &N, &M, &K);
        bool is_judge_valid = read_sol(tc_out, N, M, K);
        bool is_con_valid = read_sol(tc_con, N, M, K);

        if (is_con_valid == is_judge_valid) continue; //solusi juri dan peserta sama
        if (is_con_valid && !is_judge_valid) continue; // juri ga mungkin, tapi user mungkin; Perlu di warn ke Juri ga sih, biar kita aware? HOW?
        if (!is_con_valid && is_judge_valid) wa();

    }
    return ac();
}
