/**
 * sokokaleb's AC solution to problem scrabble, large.
 *
 * Complexity: O(2^(|S| + 1) * 26^2 * N) per testcase.
 * How: DP, KMP
 */

import java.io.*;
import java.util.*;

public class Solution2ACSokokaleb {
    static String SS;
    static int[] S = new int[15];
    static int lenS, N, K;

    static final int MOD = 1000000007;

    static int[][][] twoStepTransition = new int[1 << 11][26][26];
    static int[][]   oneStepTransition = new int[1 << 11][26];
    static int finishState;

    static int[][] dp = new int[55][1 << 11];
    static int[] pkt = new int[105];

    static int[] ftable = new int[15];

    static void clear() {
        for (int i = 0; i < (1 << lenS); ++i) {
            for (int j = 0; j < K; ++j) {
                Arrays.fill(twoStepTransition[i][j], 0);
            }
            Arrays.fill(oneStepTransition[i], 0);
        }
        Arrays.fill(ftable, -1);
    }

    static int f(int col, int mask) {
        if (dp[col][mask] == -1) {
            int res;

            if (col == N + 1) {
                res = 0;
            } else if ((mask & finishState) == finishState) {
                int sisaCol = N - col;
                res = pkt[sisaCol << 1];
            } else {
                res = 0;
                for (int i = 0; i < K; ++i) {
                    for (int j = 0; j < K; ++j) {
                        int newMask = 0;
                        newMask = newMask | twoStepTransition[mask][i][j];
                        newMask = newMask | twoStepTransition[mask][j][i];
                        newMask = newMask | oneStepTransition[mask][i];
                        newMask = newMask | oneStepTransition[mask][j];
                        res += f(col + 1, newMask);
                        if (res >= MOD) res -= MOD;
                    }
                }
            }

            dp[col][mask] = res;
        }
        return dp[col][mask];
    }

    public static void computeFailTable() {
        ftable[0] = -1;
        int i = 0, j = -1;
        while (i < lenS) {
            while (j != -1 && S[i] != S[j]) {
                j = ftable[j];
            }
            ++i;
            ++j;
            ftable[i] = j;
        }
        return ;
    }

    public static void precomputeTransition() {
        for (int b = 0; b < lenS; ++b) {
            for (int nextC = 0; nextC < K; ++nextC) {
                for (int nextNextC = 0; nextNextC < K; ++nextNextC) {
                    int newPos = b;
                    while (newPos != -1 && S[newPos] != nextC) {
                        newPos = ftable[newPos];
                    }
                    ++newPos;
                    oneStepTransition[1 << b][nextC] = 1 << newPos;
                    if (newPos == lenS);
                    else {
                        while (newPos != -1 && S[newPos] != nextNextC) {
                            newPos = ftable[newPos];
                        }
                        ++newPos;
                    }
                    twoStepTransition[1 << b][nextC][nextNextC] = 1 << newPos;
                }
            }
        }

        for (int nextC = 0; nextC < K; ++nextC) {
            oneStepTransition[1 << lenS][nextC] = 1 << lenS;
            for (int nextNextC = 0; nextNextC < K; ++nextNextC) {
                twoStepTransition[1 << lenS][nextC][nextNextC] = 1 << lenS;
            }
        }

        int limit = 1 << (lenS + 1);
        for (int mask = 1; mask < limit; ++mask) {
            if ((mask & (mask - 1)) != 0);
            else continue ;

            for (int nextC = 0; nextC < K; ++nextC) {
                int res = 0;
                for (int b = 0; b < lenS + 1; ++b) {
                    if ((mask & (1 << b)) != 0) {
                        res = res | oneStepTransition[1 << b][nextC];
                    }
                }
                oneStepTransition[mask][nextC] = res;
                for (int nextNextC = 0; nextNextC < K; ++nextNextC) {
                    res = 0;
                    for (int b = 0; b < lenS + 1; ++b) {
                        if ((mask & (1 << b)) != 0) {
                            res = res | twoStepTransition[1 << b][nextC][nextNextC];
                        }
                    }
                    twoStepTransition[mask][nextC][nextNextC] = res;
                }
            }
        }

        return ;
    }

    static void solve() throws IOException {
        SS = reader.getString();
        N = reader.getInt();
        K = reader.getInt();

        lenS = SS.length();

        for (int i = 0; i < lenS; ++i) {
            S[i] = SS.charAt(i) - 'a';
        }

        computeFailTable();
        precomputeTransition();

        pkt[0] = 1;
        for (int i = 1; i <= 2 * N; ++i) {
            pkt[i] = (int) ((1L * pkt[i - 1] * K) % MOD);
        }

        finishState = 1 << lenS;

        for (int i = 0; i <= N + 1; ++i) {
            Arrays.fill(dp[i], -1);
        }
        writer.println(f(0, 1 << 0));

        clear();
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


