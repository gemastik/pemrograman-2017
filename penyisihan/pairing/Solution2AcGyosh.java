/*
  Pairing, subtask 2
 */
import java.io.*;
import java.util.*;

public class Solution2AcGyosh {
  public static final long MAX_VALUE = 1000 * 1000;

  private BufferedReader reader;
  private BufferedWriter writer;

  public Solution2AcGyosh() {
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

    ArrayList<Long> arrA = new ArrayList<Long>();
    buff = reader.readLine().split(" ");
    for (int i = 0; i < N; i++) {
      arrA.add(Long.parseLong(buff[i]));
    }

    ArrayList<Long> arrB = new ArrayList<Long>();
    buff = reader.readLine().split(" ");
    for (int i = 0; i < N; i++) {
      arrB.add(Long.parseLong(buff[i]));
    }

    ArrayList<Long> arrC = new ArrayList<Long>();
    buff = reader.readLine().split(" ");
    for (int i = 0; i < M; i++) {
      arrC.add(Long.parseLong(buff[i]));
    }

    arrA = getUniqueSorted(arrA);
    arrB = getUniqueSorted(arrB);

    long answer = getAnswer(arrA, arrB, arrC);

    writer.write(Long.toString(answer));
    writer.write("\n");
    writer.flush();
  }

  private ArrayList<Long> getUniqueSorted(ArrayList<Long> arr) {
    ArrayList<Long> result = new ArrayList<Long>(new HashSet<Long>(arr));
    Collections.sort(result);
    return result;
  }

  private Long getAnswer(ArrayList<Long> arrA, ArrayList<Long> arrB, ArrayList<Long> arrC) {
    long answer = Long.MAX_VALUE;

    int maxJ = arrB.size() - 1;
    for (int i = 0; i < arrA.size(); i++) {
      while ((maxJ > 0) && (arrA.get(i)*arrB.get(maxJ) - arrA.get(i)*arrB.get(0) > MAX_VALUE)) {
        maxJ--;
      }

      for (int j = 0; j <= maxJ; j++) {
        long y = arrA.get(i) * arrB.get(j);
        answer = Math.min(answer, y + arrC.get((int)(y % arrC.size())));
      }
    }

    return answer;
  }

  public static void main(String[] args) throws Exception {
    Solution2AcGyosh solver = new Solution2AcGyosh();
    solver.solve();
  }
}
