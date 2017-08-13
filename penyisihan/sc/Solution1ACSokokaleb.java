/**
 * sokokaleb's AC solution to problem sc.
 *
 * Constraints: N = 10
 * Complexity: O(3^N) per testcase.
 * How: Bruteforce
 */

import java.io.*;
import java.util.*;

public class Solution1ACSokokaleb {
    static int T;
    static int N;
    static int[] Psize = new int[10];
    static int[][] P = new int[10][10];
    static int[] S = new int[10];
    static Set<Integer> Pset = new HashSet<>();

    static Reader reader = new Reader();
    static Writer writer = new Writer();

    public static void main(String[] args) throws IOException {
        T = reader.getInt();

        for (int tc = 0; tc < T; ++tc) {
            solve();
        }

        writer.flush();
    }

    static void solve() throws IOException {
        N = reader.getInt();
        for (int i = 0; i < N; ++i) {
            S[i] = reader.getInt();
        }
        for (int i = 0; i < N; ++i) {
            Psize[i] = reader.getInt();
            for (int j = 0; j < Psize[i]; ++j) {
                P[i][j] = reader.getInt();
            }
        }

        Pset.clear();
        writer.println(solve(0) + N);
    }

    static int solve(int pos) {
        if (pos == N) {
            return Pset.size();
        }
        int res = 0;

        // take 0
        res = Math.max(res, solve(pos + 1));
        // take 1 == tekwan???
        if (S[pos] > 1) {
            for (int i = 0; i < Psize[pos]; ++i) {
                if (!Pset.contains(P[pos][i])) {
                    Pset.add(P[pos][i]);
                    res = Math.max(res, solve(pos + 1));
                    Pset.remove(P[pos][i]);
                }
            }
        }
        
        return res;
    }

    /*
     * Helper classes below.
     */

    static class Reader {
        final BufferedReader br;
        StringTokenizer st;
        
        Reader() {
            br = new BufferedReader(new InputStreamReader(System.in));
            st = new StringTokenizer("");
        }

        int getInt() throws IOException {
            if (!st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
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
