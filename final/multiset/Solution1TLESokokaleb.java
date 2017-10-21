/**
 * sokokaleb's TLE solution to problem multiset, easy.
 *
 * Why: O(N^2).
 */

import java.io.*;
import java.util.*;

public class Solution1TLESokokaleb {
    private static final int MAX_N = 50005;
    private static final int MAX_X = 1000 * 1000 * 1000 + 5;

    static int N;
    static int T, L, R, K;

    static long[] count = new long[MAX_N];

    static void solve() throws IOException {
        Arrays.fill(count, 0);

        N = reader.getInt();
        for (int qq = 0; qq < N; ++qq) {
            T = reader.getInt();
            L = reader.getInt();
            R = reader.getInt();
            K = reader.getInt();

            if (T == 1) {
                count[L] += K;
            } else {
                count[L] -= K;
                count[L] = Math.max(0L, count[L]);
            }
            int ans = 1;
            while (count[ans] > 0L) {
                ++ans;
            }

            writer.println(ans);
        }
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


