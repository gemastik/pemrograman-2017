/**
 * sokokaleb's AC solution to problem bis-ddak, hard.
 *
 * Complexity: O(distinct(M) * M) per testcase.
 * How: Greedy + BF
 */

import java.io.*;
import java.util.*;

public class Solution2WATLESokokaleb {    
    private static final int MAX_VALUE = Integer.MAX_VALUE / 2;
    private static final int MAX_N = 505;
    private static final int MAX_M = 50005;
    static int N, M;

    static class Edge implements Comparable<Edge> {
        int u, v, w;

        Edge (int u, int v, int w) {
            this.u = u;
            this.v = v;
            this.w = w;
        }

        @Override
        public int compareTo(Edge e) {
            if (w == e.w && v == e.v) {
                return Integer.compare(u, e.u);
            } else if (w == e.w) {
                return Integer.compare(v, e.v);
            } else {
                return Integer.compare(w, e.w);
            }
        }
    }

    static ArrayList<TreeSet<Edge>> adj = new ArrayList<>();
    static TreeSet<Integer> weightSet = new TreeSet<>();

    static void prepare(int N) {
        adj.clear();
        for (int i = 0; i < N; ++i) {
            adj.add(new TreeSet<>());
        }
        weightSet.clear();
        inCircuit.clear();
        result = 0;
    }

    static void addEdge(int u, int v, int w) {
        adj.get(u).add(new Edge(u, v, w));
        weightSet.add(w);
    }

    static BitSet inCircuit = new BitSet(MAX_N);
    static BitSet visited = new BitSet(MAX_N);
    static int result;
    
    static ArrayList<ArrayList<Integer>> circuits = new ArrayList<>();
    static int[] to = new int[MAX_N];

    static int dfs(int u, int maxW) {
        if (inCircuit.get(u)) return -1;
        if (visited.get(u)) return u;
        visited.set(u, true);

        for (Edge e : adj.get(u)) {
            if (e.w > maxW) return -1;
            int z = dfs(e.v, maxW);
            if (z != -1) {
                to[u] = e.v;
                inCircuit.set(u, true);
                result += e.w;

                if (u == z) {
                    return -1;
                }
                return z;
            }
        }

        return -1;
    }

    static int[] loopCost = new int[MAX_N];

    static int execute(int maxW) {
        visited.clear();
        visited.or(inCircuit);
        for (int i = 0; i < N; ++i) {
            if (!visited.get(i)) {
                dfs(i, maxW);
            }
        }

        int additionalResult = 0;

        for (int i = 0; i < N; ++i) {
            if (!inCircuit.get(i)) {
                to[i] = i;
                additionalResult += loopCost[i];
            }
        }

        return result + additionalResult;
    }

    static void dfsTrace(int u, ArrayList<Integer> alis) {
        alis.add(u);
        visited.set(u, true);
        if (!visited.get(to[u])) {
            dfsTrace(to[u], alis);
        }
    }

    static void trace() {
        circuits.clear();
        visited.clear();

        for (int i = 0; i < N; ++i) {
            if (!visited.get(i) && to[i] != i) {
                if (to[i] != i) {
                    ArrayList<Integer> alis = new ArrayList<>();
                    dfsTrace(i, alis);
                    circuits.add(alis);
                }
            }
        }
    }

    static void solve() throws IOException {
        N = reader.getInt(); M = reader.getInt();
        prepare(N);
        for (int i = 0; i < N; ++i) {
            int w = reader.getInt();
            loopCost[i] = w;
            addEdge(i, i, w);
        }
        for (int i = 0; i < M; ++i) {
            int u, v, w;
            u = reader.getInt(); v = reader.getInt(); w = reader.getInt();
            --u; --v;
            addEdge(u, v, w);
        }

        int ans = Integer.MAX_VALUE;
        for (int w : weightSet) {
            ans = Math.min(ans, execute(w));
        }

        trace();
        writer.println(ans + " " + circuits.size());
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


