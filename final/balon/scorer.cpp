#include <cstdio>
#include <cmath>

using namespace std;

const double EPS = 1e-8;

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
        double out, con;

        fscanf(tc_out, "%lf", &out);

        if (fscanf(tc_con, "%lf", &con) != 1) wa();

        // Check for abnormal value
        if (isnan(con) || isinf(con)) return wa();

        double abs_error = fabs(out - con);
        double rel_error = fabs(out - con) / out;

        if ((abs_error > EPS) && (rel_error > EPS)) {
            return wa();
        }
    }
    return ac();
}
