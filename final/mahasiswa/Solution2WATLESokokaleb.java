/**
 * sokokaleb's WA & TLE solution to problem mahasiswa, hard.
 * 
 * Why: Try all M[i] as solution. Not smart PQ-way.
 * Complexity: O(distinct(M) * sum(M)).
 */

import java.io.*;
import java.util.*;

public class Solution2WATLESokokaleb {

    static int N, K;
    static int[] M = new int[100005];

    static PriorityQueue<Integer> students = new PriorityQueue<>();
    static ArrayList<Integer> tmp = new ArrayList<>();
    static TreeSet<Integer> set = new TreeSet<>();

    static boolean can(int x, int K) {
        students.clear();
        tmp.clear();

        for (int i = 0; i < x; ++i) {
            students.add(0);
        }
        for (int i = N - 1; i >= 0; --i) {
            for (int j = 0; j < M[i]; ++j) {
                if (students.isEmpty()) {
                    return false;
                }
                int taken = students.poll() + 1;
                tmp.add(taken);
            }

            for (int taken : tmp) {
                if (taken < K) {
                    students.add(taken);
                }
            }
        }
        return true;
    }

    static void solve() throws IOException {
        N = reader.getInt(); K = reader.getInt();
        set.clear();
        int jum = 0;
        for (int i = 0; i < N; ++i) {
            M[i] = reader.getInt();
            set.add(M[i]);
            jum += M[i];
        }
        set.add(jum);

        Arrays.sort(M, 0, N - 1);

        long ans = N * K;
        for (int x : set) {
            if (can(x, K)) {
                ans = x;
                break ;
            }
        }

        writer.println(ans);
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


