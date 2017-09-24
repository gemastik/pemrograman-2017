/**
 * sokokaleb's AC solution to problem pen, small.
 */

import java.io.*;
import java.util.*;

public class Solution2ACSokokaleb {
    static long N;
    static long ans = 0L;

    static Reader reader = new Reader();
    static Writer writer = new Writer();

    public static void main(String[] args) throws IOException {
        N = reader.getLong();
        for (int i = 0; i < N; ++i) {
            ans += reader.getLong();
        }
        for (int i = 0; i < N; ++i) {
            ans += reader.getLong();
        }

        writer.println(ans * N);
        writer.flush();
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

        long getLong() throws IOException {
            if (!st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            return Long.parseLong(st.nextToken());
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
