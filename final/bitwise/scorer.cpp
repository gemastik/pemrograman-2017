#include <cstdio>
using namespace std;

int wa() {
    printf("WA\n");
    return 0;
}

int ac() {
    printf("AC\n");
    return 0;
}

int main(int argc, char** argv) {
    FILE* tc_in = fopen(argv[1], "r");
    FILE* tc_out = fopen(argv[2], "r");
    FILE* tc_con = fopen(argv[3], "r");

    int T;
    fscanf(tc_in, "%d", &T);
    for (int i = 0; i < T; i++) {
        int out, con;

        fscanf(tc_out, "%d", &out);

        if (fscanf(tc_con, "%d", &con) != 1) return wa();
        if (out == -1 && con != -1) return wa();
        if (out == -1 && con == -1 && fscanf(tc_con, "%d", &con) == 1) return wa();// if bleber
        if (con <= -1) return wa();

        int N, t_A, t_B, t_C;
        int A = con;
        int B = con;
        int C = con;

        fscanf(tc_in, "%d%d%d%d", &N, &t_A, &t_B, &t_C);
        for (int i=0;i<N-1;i++){
            if (fscanf(tc_con, "%d", &con) != 1) return wa();
            if (con <= -1) return wa();
            A &= con;
            B |= con;
            C ^= con;
        }
        if (fscanf(tc_con, "%d", &con) == 1) return wa();//if bleber
        if (A != t_A || B != t_B || C != t_C) return wa();
    }
    return ac();
}
