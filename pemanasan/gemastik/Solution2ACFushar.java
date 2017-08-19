import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Solution2ACFushar {
    static final int MAX = 50000;
    static final Student[] students = new Student[MAX];
    static int T, N;

    static int[] ids = new int[12];
    static int M;

    static long resBeauty, resCuteness;
    static String[] resNames = new String[6];
    static boolean[] used = new boolean[MAX];

    static class Student {
        String name;
        int cuteness;
        int beauty;

        public Student(String name, int cuteness, int beauty) {
            this.name = name;
            this.cuteness = cuteness;
            this.beauty = beauty;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        T = Integer.parseInt(in.readLine());
        for (int tc = 0; tc < T; tc++) {
            N = Integer.parseInt(in.readLine());
            for (int i = 0; i < N; i++) {
                String[] line = in.readLine().split(" ");
                students[i] = new Student(line[0], Integer.parseInt(line[1]), Integer.parseInt(line[2]));
            }

            Integer[] allIds = new Integer[N];
            for (int i = 0; i < N; i++) {
                        allIds[i] = i;
            }
            boolean[] isRelevant = new boolean[N];

            Arrays.sort(allIds, (id1, id2) -> Integer.compare(students[id2].cuteness, students[id1].cuteness));
            for (int i = 0; i < 6; i++) {
                isRelevant[allIds[i]] = true;
            }

            Arrays.sort(allIds, (id1, id2) -> Integer.compare(students[id2].beauty, students[id1].beauty));
            for (int i = 0; i < 6; i++) {
                isRelevant[allIds[i]] = true;
            }

            M = 0;
            for (int i = 0; i < N; i++) {
                if (isRelevant[i]) {
                    ids[M] = i;
                    used[M] = false;
                    M++;
                }
            }

            resCuteness = resBeauty = 0;
            go(0, 1, 1, new String[6]);

            System.out.printf("%d%n", resCuteness + resBeauty);
            System.out.printf("%s %s %s%n", resNames[0], resNames[1], resNames[2]);
            System.out.printf("%s %s %s%n", resNames[3], resNames[4], resNames[5]);
        }
    }

    static void go(int cur, long curCuteness, long curBeauty, String[] curNames) {
        if (cur == 6) {
            if (curCuteness + curBeauty > resCuteness + resBeauty) {
                resCuteness = curCuteness;
                resBeauty = curBeauty;
                for (int i = 0; i < 6; i++) {
                    resNames[i] = curNames[i];
                }
            }
            return;
        }
        for (int i = 0; i < M; i++) {
            if (used[i]) {
                continue;
            }
            used[i] = true;
            curNames[cur] = students[ids[i]].name;
            long newCuteness = curCuteness * (cur < 3 ? students[ids[i]].cuteness : 1L);
            long newBeauty = curBeauty * (cur >= 3 ? students[ids[i]].beauty : 1L);
            go(cur+1, newCuteness, newBeauty, curNames);
            used[i] = false;
        }
    }
}

