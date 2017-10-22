/**
 * sokokaleb's AC solution to problem richer, easy.
 *
 * Complexity: O(N^2 * log N)
 * How: DFS + BIT, no explicit LCA at all.
 */

import java.io.*;
import java.util.*;

public class Solution1ACSokokaleb {
    private static final int MAX_N = 2005;
    private static final int MAX_K = 100005;
    
    static int N;
    static int[] K = new int[MAX_N];
    static ArrayList<ArrayList<Integer>> adj = new ArrayList<>();

    static BitSet ancestors = new BitSet(MAX_N);

    static class FenwickTree {
        final int[] bit;
        
        FenwickTree() {
            bit = new int[100005];
        }

        void reset() {
            Arrays.fill(bit, 0);
        }

        void update(int x, int val) {
            x = 100001 - x;
            ++x;
            for (; x < MAX_K; x += (x & -x)) {
                bit[x] += val;
            }
        }

        int read(int x) {
            x = 100001 - x;
            int res = 0;
            ++x;
            for (; x > 0; x -= (x & -x)) {
                res += bit[x];
            }
            return res;
        }
    }

    static FenwickTree ft = new FenwickTree();

    static void prepare(int N) {
        adj.clear();
        for (int i = 0; i < N; ++i) {
            adj.add(new ArrayList<>());
        }
    }

    static long bfTwoBuddy(int u, int target) {
        long res = 0L;

        if (u < target) {
            int usedRichness = Math.max(K[u], K[target]);
            res += ft.read(usedRichness + 1);
        }

        for (int v : adj.get(u)) {
            res += bfTwoBuddy(v, target);
        }
        
        return res;
    }

    static long bfTwo(int u, int target) {
        if (u == target) {
            return 0L;
        }
        long res = 0L;

        int usedRichness = Math.max(K[u], K[target]);
        res += ft.read(usedRichness + 1);

        ft.update(K[u], 1);

        int nextAncestor = -1;
        for (int v : adj.get(u)) {
            if (ancestors.get(v)) {
                nextAncestor = v;
                continue ;
            } else {
                res += bfTwoBuddy(v, target);
            }
        }

        res += bfTwo(nextAncestor, target);

        ft.update(K[u], -1);
        return res;
    }

    static long bfOne(int u) {
        long res = 0L;
        ancestors.set(u, true);

        res += bfTwo(0, u);

        for (int v : adj.get(u)) {
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


