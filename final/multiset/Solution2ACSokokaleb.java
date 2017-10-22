/**
 * sokokaleb's AC solution to problem multiset, hard.
 *
 * Complexity: O(N log N)
 * How: Segment tree
 */

import java.io.*;
import java.util.*;

public class Solution2ACSokokaleb {
    private static final int MAX_N = 50005;
    private static final int MAX_X = 1000 * 1000 * 1000 + 5;

    static class Node {
        long down = 0L, up = 0L;
        long lowest = 0L;

        void apply(final Node p) {
            up -= p.down;
            down -= Math.min(0, up);
            up -= Math.min(0, up);
            up += p.up;

            lowest = Math.max(0L, lowest - p.down);
            lowest += p.up;
        }

        void join(final Node leftNode, final Node rightNode) {
            lowest = Math.min(leftNode.lowest, rightNode.lowest);
        }
    }

    static class CompressedSegmentTree {
        static final int[] limits = new int[MAX_N * 2];
        static int numLimits = 1;
        static final Node[] nodes = new Node[MAX_N * 8];
        static final Node propagatedNode = new Node();

        static {
            for (int i = 0; i < MAX_N * 8; ++i) {
                nodes[i] = new Node();
            }
        }

        static void reset() {
            reset(1, 0, numLimits - 1);
            numLimits = 0;
            addRange(1, MAX_X);
        }

        static void reset(int node, int l, int r) {
            nodes[node].down = 0L;
            nodes[node].up = 0L;
            nodes[node].lowest = 0L;

            if (l == r) {
                return ;
            }
            
            int mid = (l + r) >> 1, A = node << 1, B = A | 1;
            reset(A, l, mid);
            reset(B, mid + 1, r);
        }

        static void addRange(int l, int r) {
            limits[numLimits++] = l;
            limits[numLimits++] = r + 1;
        }

        static void compress() {
            // uniquify
            Arrays.sort(limits, 0, numLimits);
            int newNumLimits = 1;
            for (int i = 1; i < numLimits; ++i) {
                if (limits[i] != limits[newNumLimits - 1]) {
                    limits[newNumLimits++] = limits[i];
                }
            }
            numLimits = newNumLimits;
        }

        static int findRange(int x) {
            int lo = 0, hi = numLimits, mid;
            while (lo < hi) {
                mid = (lo + hi) >> 1;
                if (limits[mid] <= x) {
                    lo = ++mid;
                } else {
                    hi = mid;
                }
            }
            return lo - 1;
        }

        static void tryPropagate(final Node O, final Node A, final Node B) {
            if (O.up != 0L || O.down != 0L) {
                A.apply(O);
                B.apply(O);
                O.up = 0L;
                O.down = 0L;
            }
        }

        static void add(int l, int r, int k) {
            propagatedNode.up = 0;
            propagatedNode.down = 0;
            if (k < 0) {
                propagatedNode.down = -k;
            } else {
                propagatedNode.up = k;
            }
            add(1, 0, numLimits - 1, findRange(l), findRange(r + 1) - 1, propagatedNode);
        }

        static void add(int node, int l, int r, int a, int b, final Node pNode) {
            if (a <= l && r <= b) {
                nodes[node].apply(pNode);
                return ;
            }

            int mid = (l + r) >> 1, A = node << 1, B = A | 1;

            tryPropagate(nodes[node], nodes[A], nodes[B]);

            if (mid >= a) {
                add(A, l, mid, a, b, pNode);
            }
            if (mid + 1 <= b) {
                add(B, mid + 1, r, a, b, pNode);
            }

            nodes[node].join(nodes[A], nodes[B]);
        }

        static int query() {
            if (nodes[0].lowest != 0) {
                return 0;
            }
            return query(1, 0, numLimits - 1);
        }

        static int query(int node, int l, int r) {
            if (l == r) {
                return limits[l];
            }

            int mid = (l + r) >> 1, A = node << 1, B = A | 1;
            tryPropagate(nodes[node], nodes[A], nodes[B]);

            final Node leftNode = nodes[A];

            if (leftNode.lowest == 0) {
                return query(A, l, mid);
            }
            return query(B, mid + 1, r);
        }
    }

    static class Query {
        int T, L, R, K;
    };

    static int N;
    static int O, L, R, K;
    static Query[] query = new Query[MAX_N];

    static {
        for (int i = 0; i < MAX_N; ++i) {
            query[i] = new Query();
        }
    }

    static void solve() throws IOException {
        CompressedSegmentTree.reset();

        N = reader.getInt();
        for (int qq = 0; qq < N; ++qq) {
            query[qq].T = reader.getInt();
            query[qq].L = reader.getInt();
            query[qq].R = reader.getInt();
            query[qq].K = reader.getInt();

            CompressedSegmentTree.addRange(query[qq].L, query[qq].R);
        }

        CompressedSegmentTree.compress();

        for (int qq = 0; qq < N; ++qq) {
            final Query q = query[qq];
            if (q.T == 2) {
                q.K = -q.K;
            }
            CompressedSegmentTree.add(q.L, q.R, q.K);
            writer.println(CompressedSegmentTree.query());
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


