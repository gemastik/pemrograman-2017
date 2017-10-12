#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
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


int main(int argc, char** argv) {
    FILE* tc_in = fopen(argv[1], "r");
    FILE* tc_out = fopen(argv[2], "r");
    FILE* tc_con = fopen(argv[3], "r");

    int T;
    fscanf(tc_in, "%d", &T);
    for (int i = 0; i < T; i++) {
        int N,M,K;

        fscanf(tc_in, "%d%d%d", &N, &M, &K);

        char verdict[50];
        char user_verdict[50];
        fscanf(tc_out, "%s", verdict);

        if (fscanf(tc_con, "%s", user_verdict) != 1) wa();
        if (strcmp(verdict, user_verdict) != 0) wa();
        if (verdict[0] == 'T') continue;

        vector<pair<int, pair<int,int> > > medals(M);
        for (int i=0;i<N;i++){
            int a,b,c;
            //dummy
            fscanf(tc_out, "%d%d%d", &a, &b, &c);
            if (fscanf(tc_con, "%d%d%d", &a, &b, &c) != 3) wa();\
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
    }
    return ac();
}
