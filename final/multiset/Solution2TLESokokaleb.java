/**
 * sokokaleb's TLE solution to problem multiset, hard.
 *
 * Complexity: O(N^2)
 * How: Compressed tapi algonya tidak smart
 */

import java.io.*;
import java.util.*;

public class Solution2TLESokokaleb {
    private static final int MAX_N = 50005;
    private static final int MAX_X = 1000 * 1000 * 1000 + 5;

    static class CompressedSmartTapiTidakSmart {
        static final int[] limits = new int[MAX_N * 2];
        static final long[] count = new long[MAX_N * 2];
        static int numLimits = 1;

        static void reset() {
            numLimits = 0;
            Arrays.fill(count, 0L);
            addRange(1, MAX_X);
        }

        static void addRange(int l, int r) {
            limits[numLimits++] = l;
            limits[numLimits++] = r + 1;
        }

        static void compress() {
            // uniquify
            Arrays.sort(limits, 0, numLimits);
            int newNumLimits = 1;
            for (int i = 1; i < numLimits; ++i) {
                if (limits[i] != limits[newNumLimits - 1]) {
                    limits[newNumLimits++] = limits[i];
                }
            }
            numLimits = newNumLimits;
        }

        static int findRange(int x) {
            int lo = 0, hi = numLimits, mid;
            while (lo < hi) {
                mid = (lo + hi) >> 1;
                if (limits[mid] <= x) {
                    lo = ++mid;
                } else {
                    hi = mid;
                }
            }
            return lo - 1;
        }

        static void add(int l, int r, int k) {
            l = findRange(l);
            r = findRange(r + 1);
            for (; l < r; ++l) {
                count[l] += k;
            }
        }

        static int query() {
            for (int i = 0; i < numLimits; ++i) {
                if (count[i] == 0L) {
                    return limits[i];
                }
            }
            return 0;
        }
    }

    static class Query {
        int T, L, R, K;
    };

    static int N;
    static int O, L, R, K;
    static Query[] query = new Query[MAX_N];

    static {
        for (int i = 0; i < MAX_N; ++i) {
            query[i] = new Query();
        }
    }

    static void solve() throws IOException {
        CompressedSmartTapiTidakSmart.reset();

        N = reader.getInt();
        for (int qq = 0; qq < N; ++qq) {
            query[qq].T = reader.getInt();
            query[qq].L = reader.getInt();
            query[qq].R = reader.getInt();
            query[qq].K = reader.getInt();

            CompressedSmartTapiTidakSmart.addRange(query[qq].L, query[qq].R);
        }

        CompressedSmartTapiTidakSmart.compress();

        for (int qq = 0; qq < N; ++qq) {
            final Query q = query[qq];
            if (q.T == 2) {
                q.K = -q.K;
            }
            CompressedSmartTapiTidakSmart.add(q.L, q.R, q.K);
            writer.println(CompressedSmartTapiTidakSmart.query());
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


