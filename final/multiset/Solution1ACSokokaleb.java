/**
 * sokokaleb's AC solution to problem multiset, easy.
 *
 * Complexity: O(N log N)
 * How: Map
 */

import java.io.*;
import java.util.*;

public class Solution1ACSokokaleb {
    private static final int MAX_N = 50005;
    private static final int MAX_X = 1000 * 1000 * 1000 + 5;

    static int N;
    static int T, L, R, K;

    static class Multiset {
        final static Map<Integer, Long> mset = new HashMap<>();
        final static TreeSet<Integer> mex = new TreeSet<>();

        static void reset() {
            mset.clear();
            mex.clear();
            for (int i = 1; i <= MAX_N; ++i) {
                mex.add(i);
            }
        }

        static void remove(int x, long k) {
            if (x > MAX_N || !mset.containsKey(x)) {
                return ;
            }

            long value = Math.max(mset.get(x) - k, 0L);
            if (value == 0L) {
                mset.remove(x);
                mex.add(x);
            } else {
                mset.put(x, value);
            }
        }

        static void add(int x, long k) {
            if (x > MAX_N) {
                return ;
            }

            boolean previouslyExists = mset.containsKey(x);
            long value = (mset.containsKey(x) ? mset.get(x) : 0L) + k;
            mset.put(x, value);

            if (!previouslyExists) {
                mex.remove(x);
            }
        }

        static int query() {
            return mex.ceiling(1);
        }
    }

    static void solve() throws IOException {
        Multiset.reset();

        N = reader.getInt();
        for (int qq = 0; qq < N; ++qq) {
            T = reader.getInt();
            L = reader.getInt();
            R = reader.getInt();
            K = reader.getInt();

            if (T == 1) {
                Multiset.add(L, K);
            } else if (T == 2) {
                Multiset.remove(L, K);
            }

            writer.println(Multiset.query());
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


