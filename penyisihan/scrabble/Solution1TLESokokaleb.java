/**
 * sokokaleb's AC solution to problem scrabble, large.
 *
 * Complexity: O(2^(|S| + 1) * 26^2 * N) per testcase.
 * How: DP, KMP
 */

import java.io.*;
import java.util.*;

public class Solution1TLESokokaleb {
    static String SS;
    static int[] S = new int[2];
    static int lenS, N, K;

    static final int MOD = 1000000007;

    static final int[][] area = new int[2][55];

    static int dfs(int r, int c) {
        if (c == N) {
            // verify kolom
            for (int j = 0; j < c; ++j) {
                if ((area[0][j] == S[0] && area[1][j] == S[1])
                        || (area[1][j] == S[0] && area[0][j] == S[1])) {
                    return 1;
                }
                if (j > 0) {
                    int aa = area[0][j - 1];
                    int bb = area[1][j - 1];
                    int cc = area[0][j];
                    int dd = area[1][j];

                    if ((aa == S[0] && cc == S[1])
                            || (aa == S[0] && dd == S[1])
                            || (bb == S[0] && cc == S[1])
                            || (bb == S[0] && dd == S[1])) {
                        return 1;
                    }
                }
            }
            return 0;
        }

        int res = 0;
        for (int i = 0; i < K; ++i) {
            area[r][c] = i;
            res += dfs(r ^ 1, c + r);
            if (res >= MOD) res -= MOD;
        }

        return res;
    }

    static void solve() throws IOException {
        SS = reader.getString();
        N = reader.getInt();
        K = reader.getInt();

        lenS = SS.length();

        for (int i = 0; i < lenS; ++i) {
            S[i] = SS.charAt(i) - 'a';
        }

        writer.println(dfs(0, 0));
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


