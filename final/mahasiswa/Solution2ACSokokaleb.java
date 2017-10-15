/**
 * sokokaleb's AC solution to problem mahasiswa, hard.
 */

import java.io.*;
import java.util.*;

public class Solution2ACSokokaleb {

    static int N, K;
	static int M;
	static long sumM;
	static int maxM;

    static void solve() throws IOException {
        N = reader.getInt(); K = reader.getInt();
		sumM = 0L;
		maxM = 0;
        for (int i = 0; i < N; ++i) {
            M = reader.getInt();
			sumM += M;
			maxM = Math.max(maxM, M);
        }

        writer.println(Math.max((sumM + K - 1) / K, maxM));
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


