/**
 * sokokaleb's AC solution to problem string-game, easy.
 *
 * Complexity: O(banyaknya string berbeda) per satu file.
 * How: DP
 */

import java.io.*;
import java.util.*;

public class Solution1ACSokokaleb {
    static String S;
    static int N, L;

    static final Map<String, Integer> dp = new HashMap<>();

    static StringBuilder sb;

    static int f(StringBuilder sb) {
        String currentString = sb.toString();
        if (dp.containsKey(currentString)) {
            return dp.get(currentString);
        }
        int res = 0;
        int mask = 0;

        for (int i = 0; i < sb.length(); ++i) {
            char bak = sb.charAt(i);
            char lim = (i == sb.length() - 1 ? 'z' : sb.charAt(i + 1));
            for (char now = bak; now <= lim; ++now) {
                if (now == bak) continue ;
                sb.setCharAt(i, now);
                mask |= 1 << f(sb);
            }
            sb.setCharAt(i, bak);
        }

        while (((mask >> res) & 1) > 0) ++res;
        dp.put(currentString, res);
        return res;
    }

    static int dfs(StringBuilder sb, int maxLength, int targetGrundy) {
        int res = 0;
        if (sb.length() > 0) {
            int g = f(sb);
            if ((g ^ targetGrundy) != 0) {
                ++res;
            }
        }

        if (sb.length() < maxLength) {
            int idx = sb.length();
            char first = (sb.length() == 0 ? 'a' : sb.charAt(sb.length() - 1));
            sb.append('a');
            for (char c = first; c <= 'z'; ++c) {
                sb.setCharAt(idx, c);
                res += dfs(sb, maxLength, targetGrundy);
            }
            sb.deleteCharAt(idx);
        }

        return res;
    }

    static void solve() throws IOException {
        N = reader.getInt(); L = reader.getInt();
        S = reader.getString();

        sb = new StringBuilder(S);
        int targetGrundy = f(sb);

        sb = new StringBuilder();
        writer.println(dfs(sb, L, targetGrundy));
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


