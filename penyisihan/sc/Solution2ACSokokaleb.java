/**
 * sokokaleb's AC solution to problem sc.
 *
 * Constraints:
 * N = 50
 * 
 * Complexity:
 * O(flow * |E|) per testcase.
 * - E ~ V^2 ~ (100^2)
 * - flow ~ 50
 * Total = T * flow * |E| ~ 10 * 50 * 100^2 ~ 5 * 10^6
 *
 * How: Ford-fulkerson
 */

import java.io.*;
import java.util.*;

public class Solution2ACSokokaleb {
    static int T;
    static int N;
    static final int[] S = new int[55];

    static final Graph graph = new Graph();

    static final Reader reader = new Reader();
    static final Writer writer = new Writer();

    static final Set<Integer> pset = new TreeSet<>();

    public static void main(String[] args) throws IOException {
        T = reader.getInt();

        for (int tc = 0; tc < T; ++tc) {
            solve();
        }

        writer.flush();
    }

    static void solve() throws IOException {
        N = reader.getInt();
        graph.clear();

        int ans = 0;
        // source to person
        for (int i = 1; i <= N; ++i) {
            S[i] = reader.getInt();
            --S[i];
            ++ans;
            graph.addEdgeFromSource(i, S[i]);
        }
        // company to sink
        for (int i = 1; i <= 50; ++i) {
            graph.addEdgeToSink(i + 50, 1);
        }
        for (int i = 1; i <= N; ++i) {
            int Psize = reader.getInt();
            pset.clear();
            for (int j = 0; j < Psize; ++j) {
                pset.add(reader.getInt());
            }
            for (int p : pset) {
                graph.addEdge(i, p + 50, 1);
            }
        }

        int f;
        do {
            f = graph.flow();
            ans += f;
        } while (f > 0);

        writer.println(ans);
    }

    /*
     * Additional classes.
     */
    
    static class Graph {

        final int SOURCE = 0;
        final int SINK = 101;
        final List<List<Edge>> edges;

        Graph() {
            edges = new ArrayList<>();
            for (int i = 0; i < 102; ++i) {
                edges.add(new ArrayList<>());
            }
        }

        void clear() {
            for (int i = 0; i < 102; ++i) {
                edges.get(i).clear();
            }
        }

        void addEdge(int u, int v, int cap) {
            Edge uv = new Edge(null, u, v, cap, 0);
            Edge vu = new Edge(null, v, u, 0, 0);
            uv.inverse = vu;
            vu.inverse = uv;
            edges.get(u).add(uv);
            edges.get(v).add(vu);
        }

        void addEdgeFromSource(int v, int cap) {
            addEdge(SOURCE, v, cap);
        }

        void addEdgeToSink(int u, int cap) {
            addEdge(u, SINK, cap);
        }

        final BitSet visited = new BitSet(102);

        int flow(int u, int fl) {
            if (visited.get(u)) {
                return 0;
            }
            visited.set(u, true);
            if (u == SINK) {
                return fl;
            }
            for (Edge e : edges.get(u)) {
                if (e.flow < e.cap) {
                    int c = flow(e.v, Math.min(fl, e.cap - e.flow));
                    if (c > 0) {
                        e.flow += c;
                        e.inverse.flow -= c;
                        return c;
                    }
                }
            }
            return 0;
        }

        int flow() {
            visited.clear();
            return flow(SOURCE, Integer.MAX_VALUE);
        }
    }

    static class Edge {
        Edge inverse;
        final int u, v, cap;
        int flow;

        Edge(Edge inverse, int u, int v, int cap, int flow) {
            this.inverse = inverse;
            this.u = u;
            this.v = v;
            this.cap = cap;
            this.flow = flow;
        }
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
