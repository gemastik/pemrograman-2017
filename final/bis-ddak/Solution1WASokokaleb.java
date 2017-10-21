/**
 * sokokaleb's WA solution to problem bis-ddak, easy.
 *
 * Complexity: O(3^N + N^2 * 2^N) per testcase.
 * Why: MAX_VALUE kurang max.
 */

import java.io.*;
import java.util.*;

public class Solution1WASokokaleb {
    static int N, M;
    static int[] loopCost = new int[12];

    static class Edge {
        int u, v, w;

        Edge() {}
        Edge(int u, int v, int w) {
            this.u = u;
            this.v = v;
            this.w = w;
        }
    }

    static int[][] adjacencyMatrix = new int[12][12];
    static final int MAX_VALUE = 4000000;

    static int[][][] dpTsp = new int[12][12][1 << 12];
    static int[] dpCircuit = new int[1 << 12];

    static int calculateDpTsp(int initialPos, int u, int mask) { // N^2 * 2^N
        int[][][] dp = dpTsp;

        if (dp[initialPos][u][mask] == -1) {
            int res = MAX_VALUE;

            if (mask == 0) {
                res = adjacencyMatrix[u][initialPos]; // balik ke posisi awal
            } else {
                for (int v = 0; v < N; ++v) {
                    if (v != u && adjacencyMatrix[u][v] < MAX_VALUE && ((mask >> v) & 1) != 0) {
                        res = Math.min(res, adjacencyMatrix[u][v] + calculateDpTsp(initialPos, v, mask ^ (1 << v)));
                    }
                }
            }

            dp[initialPos][u][mask] = res;
        }

        return dp[initialPos][u][mask];
    }

    static int calculateDpCircuit(int mask) { // 3^N
        int[] dp = dpCircuit;

        if (dp[mask] == -1) {
            int res = MAX_VALUE;
            int initialMask = mask;

            if (mask == 0) {
                res = 0;
            } else {
                int lowestBitPosition = 0;
                while (((mask >> lowestBitPosition) & 1) == 0) ++lowestBitPosition;
                mask ^= (1 << lowestBitPosition);

                // self-loop this node
                res = loopCost[lowestBitPosition] + calculateDpCircuit(mask);

                // try circuit
                for (int subMask = mask; subMask > 0; subMask = (subMask - 1) & mask) {
                    int resultDpTsp = calculateDpTsp(lowestBitPosition, lowestBitPosition, subMask);
                    int resultDpCircuit = calculateDpCircuit(mask ^ subMask);
                    res = Math.min(res, resultDpTsp + resultDpCircuit);
                }
            }

            dp[initialMask] = res;
            mask = initialMask;
        }

        return dp[mask];
    }

    static void prepare(int N, int M) {
        for (int i = 0; i < N; ++i) {
            loopCost[i] = MAX_VALUE;
            for (int j = 0; j < N; ++j) {
                adjacencyMatrix[i][j] = MAX_VALUE;
            }
        }

        for (int mask = 0; mask < (1 << N); ++mask) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    dpTsp[i][j][mask] = -1;
                }
            }
            dpCircuit[mask] = -1;
        }

        circuits.clear();
    }

    static void traceDpTsp(int initialPos, int u, int mask, ArrayList<Integer> result) {
        int[][][] dp = dpTsp;
        
        result.add(u);

        if (mask == 0) {
            return ;
        }

        for (int v = 0; v < N; ++v) {
            if (v != u && adjacencyMatrix[u][v] < MAX_VALUE && ((mask >> v) & 1) != 0) {
                if (dp[initialPos][u][mask] == adjacencyMatrix[u][v] + calculateDpTsp(initialPos, v, mask ^ (1 << v))) {
                    traceDpTsp(initialPos, v, mask ^ (1 << v), result);
                    return ;
                }
            }
        }
    }

    static ArrayList<ArrayList<Integer>> circuits = new ArrayList<>();

    static void traceDpCircuit(int mask) {
        int[] dp = dpCircuit;
        int initialRes = dp[mask];

        if (mask == 0) {
            return ;
        }

        int lowestBitPosition = 0;
        while (((mask >> lowestBitPosition) & 1) == 0) ++lowestBitPosition;
        mask ^= (1 << lowestBitPosition);

        // self-loop this node
        if (initialRes == loopCost[lowestBitPosition] + calculateDpCircuit(mask)) {
            traceDpCircuit(mask);
            return ;
        }

        // try circuit
        for (int subMask = mask; subMask > 0; subMask = (subMask - 1) & mask) {
            int resultDpTsp = calculateDpTsp(lowestBitPosition, lowestBitPosition, subMask);
            int resultDpCircuit = calculateDpCircuit(mask ^ subMask);

            if (initialRes == resultDpTsp + resultDpCircuit) {
                ArrayList<Integer> result = new ArrayList<>();
                traceDpTsp(lowestBitPosition, lowestBitPosition, mask, result);
                circuits.add(result);

                traceDpCircuit(mask ^ subMask);
                return ;
            }
        }
    }

    static void solve() throws IOException {
        N = reader.getInt(); M = reader.getInt();
        prepare(N, M);
        
        for (int i = 0; i < N; ++i) {
            loopCost[i] = reader.getInt();
        }
        for (int z = 0; z < M; ++z) {
            int u, v, w;
            u = reader.getInt(); v = reader.getInt(); w = reader.getInt();
            --u; --v;
            adjacencyMatrix[u][v] = Math.min(adjacencyMatrix[u][v], w);
        }

        int fullMask = (1 << N) - 1;
        int result = calculateDpCircuit(fullMask);
        traceDpCircuit(fullMask);
        writer.println(result + " " + circuits.size());
        for (List<Integer> circuit : circuits) {
            writer.print(circuit.size());
            for (int u : circuit) {
                writer.print(" " + (u + 1));
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


