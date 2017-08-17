/**
 * sokokaleb's AC solution to problem scrabble, large.
 *
 * Complexity: O(2^(|S| + 1) * 26^2 * N) per testcase.
 * How: DP, KMP
 */

import java.io.*;
import java.util.*;

public class Solution1ACSokokaleb {
    static String SS;
    static int[] S = new int[2];
    static int lenS, N, K;

    static final int MOD = 1000000007;

    static int[][][] dp = new int[55][27][27];
    static int[] pkt = new int[105];

    static int f(int col, int c1, int c2) {
        if (dp[col][c1][c2] == -1) {

            int res;
            if (col == N) {
                res = 0;
            } else {
                res = 0;
                for (int i = 0; i < K; ++i) {
                    for (int j = 0; j < K; ++j) {
                        if ((c1 == S[0] && i == S[1])
                                || (c1 == S[0] && j == S[1])
                                || (c2 == S[0] && i == S[1])
                                || (c2 == S[0] && j == S[1])
                                || (i == S[0] && j == S[1])
                                || (j == S[0] && i == S[1])) {
                            int sisaCol = N - col - 1;
                            res += pkt[sisaCol << 1];
                        } else {
                            res += f(col + 1, i, j);
                        }
                        if (res >= MOD) res -= MOD;
                    }
                }
            }

            dp[col][c1][c2] = res;
        }

        return dp[col][c1][c2];
    }

    static void solve() throws IOException {
        SS = reader.getString();
        N = reader.getInt();
        K = reader.getInt();

        lenS = SS.length();

        for (int i = 0; i < lenS; ++i) {
            S[i] = SS.charAt(i) - 'a';
        }

        pkt[0] = 1;
        for (int i = 1; i <= 2 * N; ++i) {
            pkt[i] = (int) ((1L * pkt[i - 1] * K) % MOD);
        }

        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j < K; ++j) {
                Arrays.fill(dp[i][j], -1);
            }
        }
        dp[0][26][26] = -1;
        writer.println(f(0, 26, 26));
    }

    public static void main(String[] args) throws IOException {
        int T = reader.getInt();

        for (int tc = 0; tc < T; ++tc) {
            solve();
        }

        writer.flush();
    }

    /*
     * Helper classes below.
     */

    static Reader reader = new Reader();
    static Writer writer = new Writer();

    static class Reader {
        final BufferedReader br;
        StringTokenizer st;
        
        Reader() {
            br = new BufferedReader(new InputStreamReader(System.in));
            st = new StringTokenizer("");
        }

        void checkToken() throws IOException {
            if (!st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
        }

        String getString() throws IOException {
            checkToken();
            return st.nextToken();
        }

        int getInt() throws IOException {
            checkToken();
            return Integer.parseInt(st.nextToken());
        }
    }

    static class Writer {
        final BufferedWriter bw;

        Writer() {
            bw = new BufferedWriter(new OutputStreamWriter(System.out));
        }

        void print(Object s) throws IOException {
            bw.write(s.toString());
        }

        void println(Object s) throws IOException {
            print(s);
            print("\n");
        }

        void flush() throws IOException {
            bw.flush();
        }
    }
}


