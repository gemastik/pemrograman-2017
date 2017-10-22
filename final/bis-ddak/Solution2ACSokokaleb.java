/**
 * sokokaleb's AC solution to problem bis-ddak, hard.
 *
 * Complexity: O(N^3) per testcase.
 * How: Hungarian algorithm, min-cost
 */

import java.io.*;
import java.util.*;

public class Solution2ACSokokaleb {
    private static final int MAX_N = 505;
    static int N, M;
    static int[][] arr = new int[MAX_N][MAX_N];
    static int[] lx = new int[MAX_N];
    static int[] ly = new int[MAX_N];
    static int[] prev = new int[MAX_N];
    static int[] slack = new int[MAX_N];

    static BitSet S = new BitSet(MAX_N);
    static BitSet T = new BitSet(MAX_N);

    private static final int MAX_VALUE = Integer.MAX_VALUE / 2;

    /*
     * KH-related methods -- BEGIN.
     */

    static int findMax(int[] arr, int l, int r) {
        int res = arr[l];
        while (l <= r) {
            res = Math.max(res, arr[l]);
            ++l;
        }
        return res;
    }

    static void init() {
        Arrays.fill(ly, 0, N, 0);
        for (int i = 0; i < N; ++i) {
            lx[i] = findMax(arr[i], 0, N - 1);
        }
        Arrays.fill(prev, 0, N, -1);
    }

    static boolean match(int u) {
        for (int v = 0; v < N; ++v) {
            if (!T.get(v)) {
                slack[v] = Math.min(slack[v], lx[u] + ly[v] - arr[u][v]);
            }
        }
        S.set(u, true);
        for (int v = 0; v < N; ++v) {
            if (lx[u] + ly[v] == arr[u][v] && !T.get(v)) {
                T.set(v, true);
                if (prev[v] == -1 || match(prev[v])) {
                    prev[v] = u;
                    return true;
                }
            }
        }
        return false;
    }

    static void update() {
        int delta = MAX_VALUE;
        for (int v = 0; v < N; ++v) {
            if (!T.get(v)) {
                delta = Math.min(delta, slack[v]);
            }
        }
        for (int i = 0; i < N; ++i) {
            if (T.get(i)) {
                ly[i] += delta;
            }
            if (S.get(i)) {
                lx[i] -= delta;
            }
        }
    }

    static int executeKH() {
        init();
        for (int i = 0; i < N; ++i) {
            while (true) {
                Arrays.fill(slack, 0, N, Integer.MAX_VALUE);
                S.clear();
                T.clear();
                if (match(i)) {
                    break ;
                }
                update();
            }
        }

        int result = 0;
        for (int i = 0; i < N; ++i) {
            result += lx[i] + ly[i];
        }
        return result;
    }

    /*
     * KH-related methods -- END.
     */

    /*
     * Tracing-related methods -- BEGIN.
     */

    static ArrayList<ArrayList<Integer>> circuits = new ArrayList<>();
    static int[] to = new int[MAX_N];
    static BitSet visited = new BitSet(MAX_N);

    static void dfs(int u, ArrayList<Integer> alis) {
        alis.add(u);
        visited.set(u, true);
        if (!visited.get(to[u])) {
            dfs(to[u], alis);
        }
    }

    static void trace() {
        circuits.clear();
        visited.clear();

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (lx[i] + ly[j] == arr[i][j]) {
                    to[i] = j;
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            if (!visited.get(i) && to[i] != i) {
                if (to[i] != i) {
                    ArrayList<Integer> alis = new ArrayList<>();
                    dfs(i, alis);
                    circuits.add(alis);
                }
            }
        }
    }

    /*
     * Tracing-related methods -- END.
     */

    static void prepare(int N) {
        for (int i = 0; i < N; ++i) {
            Arrays.fill(arr[i], -MAX_VALUE);
        }
    }

    static void solve() throws IOException {
        N = reader.getInt(); M = reader.getInt();
        prepare(N);
        for (int i = 0; i < N; ++i) {
            arr[i][i] = -reader.getInt();
        }
        for (int i = 0; i < M; ++i) {
            int u, v, w;
            u = reader.getInt(); v = reader.getInt(); w = reader.getInt();
            --u; --v;
            arr[u][v] = -w;
        }

        writer.print(-executeKH());
        trace();
        writer.println(" " + circuits.size());
        for (ArrayList<Integer> alis : circuits) {
            writer.print(alis.size());
            for (int bulumata : alis) {
                writer.print(" " + (bulumata + 1));
            }
            writer.println("");
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


