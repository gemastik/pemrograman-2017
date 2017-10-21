/**
 * sokokaleb's TLE solution to problem mahasiswa, hard.
 */

import java.io.*;
import java.util.*;

public class Solution2TLESokokaleb {

    static int N, K;
    static int[] M = new int[100005];

    static class PoolOfStudent {
        PriorityQueue<Integer> students;
        ArrayList<Integer> tmp;
        int exhaustedStudent;

        PoolOfStudent() {
            students = new PriorityQueue<>();
            tmp = new ArrayList<>();
            exhaustedStudent = 0;
        }

        void clear() {
            students.clear();
            tmp.clear();
            exhaustedStudent = 0;
        }

        void assign(int m, int K) {
            for (int i = 0; i < m; ++i) {
                int taken = -1;
                if (students.isEmpty()) {
                    taken = 1;
                } else {
                    taken = students.poll() + 1;
                }
                tmp.add(taken);
            }

            for (int taken : tmp) {
                if (taken < K) {
                    students.add(taken);
                } else {
                    ++exhaustedStudent;
                }
            }
            tmp.clear();
        }

        int getNumberOfStudents() {
            return exhaustedStudent + students.size();
        }
    }

    static PoolOfStudent poolOfStudent = new PoolOfStudent();

    static void solve() throws IOException {
        N = reader.getInt(); K = reader.getInt();
        for (int i = 0; i < N; ++i) {
            M[i] = reader.getInt();
        }

        Arrays.sort(M, 0, N - 1);

        poolOfStudent.clear();
        for (int i = N - 1; i >= 0; --i) {
            poolOfStudent.assign(M[i], K);
        }

        writer.println(poolOfStudent.getNumberOfStudents());
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


