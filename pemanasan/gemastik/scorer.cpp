#include <bits/stdc++.h>
using namespace std;

int wa() {
    cout << "WA" << endl;
    return 0;
}

int ac() {
    cout << "AC" << endl;
    return 0;
}

int main(int argc, char* argv[]) {
    FILE* tc_in = fopen(argv[1], "r");
    FILE* tc_out = fopen(argv[2], "r");
    FILE* con_out = fopen(argv[3], "r");

    int T;
    fscanf(tc_in, "%d", &T);

    for (int tc = 0; tc < T; tc++) {
        map<string, long long> G, C;
        int N;
        fscanf(tc_in, "%d", &N);
        for (int i = 0; i < N; i++) {
            char s[10];
            int g, c;
            fscanf(tc_in, "%s %d %d", s, &g, &c);
            G[s] = g;
            C[s] = c;
        }

        long long tc_res;
        fscanf(tc_out, "%lld", &tc_res);
        fscanf(tc_out, "%*s%*s%*s%*s%*s%*s");

        long long con_res;
        char a[10], b[10], c[10], d[10], e[10], f[10];
        if (fscanf(con_out, "%lld\n%s %s %s\n%s %s %s\n", &con_res, a, b, c, d, e, f) != 7) {
            return wa();
        }

        if (con_res != tc_res) {
            return wa();
        }

        string aa(a), bb(b), cc(c), dd(d), ee(e), ff(f);
        set<string> all = {aa, bb, cc, dd, ee, ff};
        if (all.size() != 6) {
            return wa();
        }

        long long total = G[aa] * G[bb] * G[cc] + C[dd] * C[ee] * C[ff];
        if (total != tc_res) {
            return wa();
        }
    }
    return ac();
}

