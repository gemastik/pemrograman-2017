/*
  Pairing, subtask 1
 */
import java.io.*;
import java.util.Arrays;

public class Main {
  public static final int MAX_N = 1000000;

  private BufferedReader reader;
  private BufferedWriter writer;

  public Main() {
    reader = new BufferedReader(new InputStreamReader(System.in));
    writer = new BufferedWriter(new OutputStreamWriter(System.out));
  }

  public void solve() throws Exception {
    int nTestCase = Integer.parseInt(reader.readLine());
    for (int i = 0; i < nTestCase; i++) {
      solveOne();
    }
  }

  private void solveOne() throws Exception {
    String[] buff;

    buff = reader.readLine().split(" ");
    int N = Integer.parseInt(buff[0]);
    int M = Integer.parseInt(buff[1]);

    int[] A = new int[N];
    int[] B = new int[N];
    int[] C = new int[M];

    buff = reader.readLine().split(" ");
    for (int i = 0; i < N; i++) {
      A[i] = Integer.parseInt(buff[i]);
    }

    buff = reader.readLine().split(" ");
    for (int i = 0; i < N; i++) {
      B[i] = Integer.parseInt(buff[i]);
    }

    buff = reader.readLine().split(" ");
    for (int i = 0; i < M; i++) {
      C[i] = Integer.parseInt(buff[i]);
    }

    // minA[x] = min(A[i]), foreach x,i such that x = A[i] % M
    int[] minA = new int[M];
    Arrays.fill(minA, Integer.MAX_VALUE);
    for (int i = 0; i < N; i++) {
      int x = A[i] % M;
      minA[x] = Math.min(minA[x], A[i]);
    }

    // minB[x] = min(B[i]), foreach x,i such that x = B[i] % M
    int[] minB = new int[M];
    Arrays.fill(minB, Integer.MAX_VALUE);
    for (int i = 0; i < N; i++) {
      int x = B[i] % M;
      minB[x] = Math.min(minB[x], B[i]);
    }

    long answer = Long.MAX_VALUE;
    for (int a = 0; a < M; a++) {
      for (int b = 0; b < M; b++) {
        int aVal = minA[a];
        int bVal = minB[b];

        boolean hasDefinedA = aVal != Integer.MAX_VALUE;
        boolean hasDefinedB = bVal != Integer.MAX_VALUE;
        if (hasDefinedA && hasDefinedB) {
          int y = ((aVal % M) * (bVal % M)) % M;
          answer = Math.min(answer, (long)aVal*bVal + C[y]);
        }
      }
    }

    writer.write(Long.toString(answer));
    writer.write("\n");
    writer.flush();
  }

  public static void main(String[] args) throws Exception {
    Main solver = new Main();
    solver.solve();
  }
}
