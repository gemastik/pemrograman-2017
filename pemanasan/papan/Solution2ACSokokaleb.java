/**
 * sokokaleb's AC solution to problem papan.
 *
 * Constraints: N, M = 50000
 * Complexity: O(N + M) per testcase.
 * How: Line sweep
 */

import java.io.*;
import java.util.*;

public class Solution2ACSokokaleb {
    static int T;
    static int N, K;
    static int[] grad   = new int[50005];
    static int[] con    = new int[50005];

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
        K = reader.getInt();

        Arrays.fill(grad, 0);
        Arrays.fill(con, 0);
        for (int k = 0; k < K; ++k) {
            int pos, h;
            pos = reader.getInt();
            h = reader.getInt();

            int p, g, c;

            p = pos - h + 1;
            c = 1;
            g = +1;
            if (p < 1) {
                c += 1 - p;
                p = 1;
            }
            con[p] += c;
            grad[p] += g;

            grad[pos] += -2;

            p = pos + h;
            if (p <= N) {
                grad[p] += +1;
            }
        }

        Long currentHeight = 0;
        Long currentGrad = 0;
        for (int i = 1; i <= N; ++i) {
            if (i > 1) {
                writer.print(" ");
            }
            currentHeight += con[i] + currentGrad;
            currentGrad += grad[i];
            writer.print(currentHeight);
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


