/**
 * sokokaleb's AC solution to problem papan.
 *
 * Constraints: N, M = 1000
 * Complexity: O(NM) per testcase.
 * How: Bruteforce
 */

import java.io.*;
import java.util.*;

public class Solution1ACSokokaleb {
    static int T;
    static int N, K;
    static int[] height = new int[1005];

    static Reader reader = new Reader();
    static Writer writer = new Writer();

    static <T extends Comparable<T>> boolean inRange(final T o, final T a, final T b) {
        return a.compareTo(o) <= 0 && o.compareTo(b) <= 0;
    }

    public static void main(String[] args) throws IOException {
        T = reader.getInt();

        for (int tc = 0; tc < T; ++tc) {
            solve();
        }

        writer.flush();
    }

    static void solve() throws IOException {
        N = reader.getInt();
        K = reader.getInt();

        Arrays.fill(height, 0);
        for (int k = 0; k < K; ++k) {
            int pos, h;
            pos = reader.getInt();
            h = reader.getInt();

            height[pos] += h;

            for (int i = 1; i < h; ++i) {
                if (!inRange(pos - i, 1, N) && !inRange(pos + i, 1, N)) {
                    break ;
                }
                if (inRange(pos - i, 1, N)) {
                    height[pos - i] += h - i;
                }
                if (inRange(pos + i, 1, N)) {
                    height[pos + i] += h - i;
                }
            }
        }

        for (int i = 1; i <= N; ++i) {
            if (i > 1) {
                writer.print(" ");
            }
            writer.print(height[i]);
        }
        writer.println();
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

        void println() throws IOException {
            println("");
        }

        void flush() throws IOException {
            bw.flush();
        }
    }
}

