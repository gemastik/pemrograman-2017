/**
 * sokokaleb's AC solution to problem string-game, hard.
 *
 * Complexity: O(MAX_L * 32 * 32 * 26 + T * 32^3 * log(N)) per satu file.
 * How: DP + Matrix multiplication
 */

import java.io.*;
import java.util.*;

public class Solution2ACSokokaleb {
    private static final int MOD = 1000000007;
    private static final int MAX_L = 10005;

    static String S;
    static int N, L;

    // state: current char, mask, length
    static int[][][] dp = new int[26][32][MAX_L];
    static int[][] countPerMask = new int[MAX_L][32];

    static void precompute() {
        for (int lastChar = 0; lastChar <= 25; ++lastChar) {
            dp[lastChar][0][1] = 1;
            countPerMask[1][lastChar] = 1;
        }

        // 10K * 26 * 32 * 26
        for (int len = 2; len <= 10000; ++len) {
            for (int cchar = 0; cchar <= 25; ++cchar) {
                for (int mask = 0; mask < 32; ++mask) {
                    for (int pakeChar = 0; pakeChar <= cchar; ++pakeChar) {
                        int nmask = (len & 1) == 0 ? (mask ^ (cchar - pakeChar)) : mask;
                        dp[cchar][mask][len] += dp[pakeChar][nmask][len - 1];
                        if (dp[cchar][mask][len] >= MOD) {
                            dp[cchar][mask][len] -= MOD;
                        }
                    }
                }
                for (int mask = 0; mask < 32; ++mask) {
                    int nmask = (len & 1) == 0 ? mask : (mask ^ (25 - cchar));
                    countPerMask[len][mask] += dp[cchar][nmask][len];
                    if (countPerMask[len][mask] >= MOD) {
                        countPerMask[len][mask] -= MOD;
                    }
                }
            }
        }

        for (int mask = 0; mask < 32; ++mask) {
            for (int pos = 1; pos <= 10000; ++pos) {
                countPerMask[pos][mask] += countPerMask[pos - 1][mask];
                if (countPerMask[pos][mask] >= MOD) {
                    countPerMask[pos][mask] -= MOD;
                }
            }
        }
    }

    static int getGrundy(String s) {
        int res = 0;
        for (int i = 1; i < s.length(); i += 2) {
            res ^= (int) (s.charAt(i) - s.charAt(i - 1));
        }
        return res;
    }

    static int[][] tmp = new int[32][32];

    static class Matrix {
        int[][] mat = new int[32][32];

        Matrix prepare(int L, int[] countPerMask) {
            for (int i = 0; i < 32; ++i) {
                for (int j = 0; j < 32; ++j) {
                    mat[i][j] = countPerMask[i ^ j];
                }
            }
            return this;
        }
        
        Matrix setIdentity() {
            for (int i = 0; i < 32; ++i) {
                for (int j = 0; j < 32; ++j) {
                    mat[i][j] = (i == j ? 1 : 0);
                }
            }
            return this;
        }

        Matrix multiply(final Matrix m) {
            for (int i = 0; i < 32; ++i) {
                Arrays.fill(tmp[i], 0);
            }
            
            for (int k = 0; k < 32; ++k) {
                for (int i = 0; i < 32; ++i) {
                    for (int j = 0; j < 32; ++j) {
                        tmp[i][j] += ((long) mat[i][k] * m.mat[k][j]) % MOD;
                        if (tmp[i][j] >= MOD) {
                            tmp[i][j] -= MOD;
                        }
                    }
                }
            }

            for (int i = 0; i < 32; ++i) {
                for (int j = 0; j < 32; ++j) {
                    mat[i][j] = tmp[i][j];
                }
            }
            return this;
        }

        Matrix powerTwo() {
            return this.multiply(this);
        }
    }

    static Matrix base = new Matrix();
    static Matrix res = new Matrix();

    static Matrix calculateMatrix(int L, int N) {
        base.prepare(L, countPerMask[L]);
        res.setIdentity();

        while (N > 0) {
            if ((N & 1) == 1) {
                res.multiply(base);
            }
            base.powerTwo();
            N >>= 1;
        }

        return res;
    }

    static void solve() throws IOException {
        N = reader.getInt(); L = reader.getInt();
        S = reader.getString() + "z";
        int targetGrundy = getGrundy(S);

        int ans = 0;
        Matrix res = calculateMatrix(L, N - 1);
        for (int i = 0; i < 32; ++i) {
            if (i != targetGrundy) {
                ans += res.mat[0][i];
                if (ans >= MOD) {
                    ans -= MOD;
                }
            }
        }
        writer.println(ans);
    }

    public static void main(String[] args) throws IOException {
        precompute();
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


