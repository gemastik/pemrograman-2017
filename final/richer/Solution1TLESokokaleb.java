/**
 * sokokaleb's TLE solution to problem richer, easy.
 *
 * Complexity: O(N^3)
 * Why TLE: N^3
 */

import java.io.*;
import java.util.*;

public class Solution1TLESokokaleb {
    private static final int MAX_N = 1005;
    private static final int MAX_K = 100005;
    
    static int N;
    static int[] K = new int[MAX_N];
    static ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
    static int[] nextAncestor = new int[MAX_N];

    static BitSet ancestors = new BitSet(MAX_N);

    static void prepare(int N) {
        adj.clear();
        for (int i = 0; i < N; ++i) {
            adj.add(new ArrayList<>());
        }
    }

    static long bfThree(int u, int target, int usedRichness) {
        long res = 0L;

        if (u == target) {
            return res;
        }

        if (K[u] > usedRichness) {
            ++res;
        }

        res += bfThree(nextAncestor[u], target, usedRichness);

        return res;
    }

    static long bfTwoBuddy(int u, int target, int target2) {
        long res = 0L;

        if (u < target) {
            int usedRichness = Math.max(K[u], K[target]);
            res += bfThree(0, nextAncestor[target2], usedRichness);
        }

        for (int v : adj.get(u)) {
            res += bfTwoBuddy(v, target, target2);
        }
        
        return res;
    }

    static long bfTwo(int u, int target) {
        if (u == target) {
            return 0L;
        }
        long res = 0L;

        int usedRichness = Math.max(K[u], K[target]);
        res += bfThree(0, u, usedRichness);

        int nextAncestor = -1;
        for (int v : adj.get(u)) {
            if (ancestors.get(v)) {
                nextAncestor = v;
                continue ;
            } else {
                res += bfTwoBuddy(v, target, u);
            }
        }

        res += bfTwo(nextAncestor, target);

        return res;
    }

    static long bfOne(int u) {
        long res = 0L;
        ancestors.set(u, true);

        res += bfTwo(0, u);

        for (int v : adj.get(u)) {
            nextAncestor[u] = v;
            res += bfOne(v);
        }

        ancestors.set(u, false);
        return res;
    }

    static void solve() throws IOException {
        N = reader.getInt();
        prepare(N);
        for (int i = 1; i < N; ++i) {
            int p = reader.getInt() - 1;
            adj.get(p).add(i);
        }
        for (int i = 0; i < N; ++i) {
            K[i] = reader.getInt();
        }

        writer.println(bfOne(0));
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


