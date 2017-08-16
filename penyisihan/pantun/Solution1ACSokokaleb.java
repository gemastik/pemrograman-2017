/**
 * sokokaleb's AC solution to problem pen, small.
 */

import java.io.*;
import java.util.*;

public class Solution1ACSokokaleb {
    static int N;
    static int A, B;

    static Reader reader = new Reader();
    static Writer writer = new Writer();

    public static void main(String[] args) throws IOException {
        N = reader.getInt();
        A = reader.getInt();
        B = reader.getInt();

        writer.println(A + B);
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
