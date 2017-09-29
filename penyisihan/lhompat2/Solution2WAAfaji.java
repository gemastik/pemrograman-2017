import java.io.*;
import java.util.*;



public class Solution2WAAfaji {
    static int grid[][];
    static int shortest[][];
    static int R,C,N;
    static int mx[] = {-1,-1,0,0};
    static int my[] = {0,0,1,-1};
    static class MyMap extends HashMap<Long, Long> {}
    static MyMap dp[][];

    static Cell mp(int a,int b, int c) {
        return new Cell(a, b, c);
    }

    static int move(int x,int y, int a, int b) {
        int A = Math.max(grid[x][y],0);
        int B = Math.max(grid[a][b],0);
        return Math.abs(A - B) + 1;
    }

    static void dijkstra(int idx, int x, int y) {
        PriorityQueue<Cell> pq =
                new PriorityQueue<Cell>();

        pq.add(mp(1, x, y));
        boolean vis[][] = new boolean[R][C];
        while (pq.size() > 0) {
            int cost = pq.peek().cost;
            int curX = pq.peek().x;
            int curY = pq.peek().y;
            pq.poll();
            if (vis[curX][curY]) continue;
            vis[curX][curY] = true;

            if (curX == 0) {
                shortest[idx][curY] = cost;
            }

            for (int i=0;i<4;i++){
                int nx = curX + mx[i];
                int ny = curY + my[i];
                if (nx < 0 || ny < 0 || nx >= R || ny >= C || vis[nx][ny]) continue;
                int nc = cost + move(curX, curY, nx, ny);
                pq.add(mp(nc, nx, ny));
            }
        }
    }

    static long wow(int pos, int n, long maks){
        if (n == N){
            return maks;
        }
        if (pos == C){
            return 0;   
        }
        if (dp[pos][n].containsKey(maks))
            return dp[pos][n].get(maks);

        long res = wow(pos + 1, n, maks)
                         + wow(pos + 1, n + 1, Math.max(maks, shortest[n+1][pos]));


        res %= 1000000007;
        dp[pos][n].put(maks, res);
        return res;

    }
    static void solve() throws IOException {
        R = reader.getInt();
        C = reader.getInt();
        N = reader.getInt();

        grid = new int[R][C];
        shortest = new int[N + 1][C];

        for (int i=0;i<R;i++)
            for (int j=0;j<C;j++)
                grid[i][j] = reader.getInt();

        for (int i=0;i<R;i++)
            for (int j=0;j<C;j++)
                if  (grid[i][j] < 0) {
                    dijkstra(-grid[i][j], i,j);
                }

        dp = new MyMap[C][N];
        for (int i=0;i<C;i++)
            for (int j=0;j<N;j++)
                dp[i][j] = new MyMap();

        writer.println(wow(0,0,0));
    }

    public static void main(String arghhhhh[]) throws IOException {
        int T = reader.getInt();

        for (int tc = 0; tc < T; ++tc) {
            solve();
        }

        writer.flush();

    }    

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

class Cell implements Comparable{
    public int cost;
    public int x;
    public int y;
    public Cell(int a, int b, int c){
        cost = a; x = b; y = c;
    }

    @Override
    public int compareTo(Object o){
        return  cost - ((Cell)o).cost;
    }

}
