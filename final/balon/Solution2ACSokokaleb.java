/**
 * sokokaleb's AC solution to problem balon, hard.
 *
 * Complexity: O(N log N) per testcase.
 * How: binary search the answer, line-sweep
 */

import java.io.*;
import java.util.*;

public class Solution2ACSokokaleb {
    private static final int LOOP_LIMIT = 55;
    private static final int MAX_N = 50005;
    static int N, M;

    static double tanA, cosA, sinA;

    static class Point {
        int x, y;
        double r, baseAngle;
        double min, max;

        void calculateThings() {
            r = Math.hypot(x, y);
            max = r / cosA;
            min = r;
            baseAngle = Math.atan2(y, x);
        }
    }

    static Point[] points = new Point[MAX_N];

    static {
        for (int i = 0; i < MAX_N; ++i) {
            points[i] = new Point();
        }
    }

    static class Event implements Comparable<Event> {
        double x;
        int idx;
        int type;

        @Override
        public int compareTo(final Event e) {
            if (Math.abs(x - e.x) < EPS) {
                return Integer.compare(type, e.type);
            }
            return Double.compare(x, e.x);
        }
    }

    static Event[] events = new Event[MAX_N * 8];
    static int numEvents;
    static int numIncluded;
    static final BitSet bs = new BitSet(MAX_N);

    static {
        for (int i = 0; i < MAX_N * 8; ++i) {
            events[i] = new Event();
        }
    }

    static double LEFT_LIMIT, RIGHT_LIMIT;
    static double BASE_ANGLE;
    static final double EPS = 1e-10;

    static double normalize(double x) {
        while (x > RIGHT_LIMIT + EPS) {
            x -= BASE_ANGLE;
        }
        while (x < LEFT_LIMIT - EPS) {
            x += BASE_ANGLE;
        }
        return x;
    }

    static void addEvent(double l, double r, int idx) {
        l = normalize(l);
        r = normalize(r);

        if (l - EPS < r) {
            events[numEvents].x = l;
            events[numEvents].idx = idx;
            events[numEvents].type = 0;
            ++numEvents;

            events[numEvents].x = r;
            events[numEvents].idx = idx;
            events[numEvents].type = 1;
            ++numEvents;
        } else {
            events[numEvents].x = l;
            events[numEvents].idx = idx;
            events[numEvents].type = 0;
            ++numEvents;
            events[numEvents].x = RIGHT_LIMIT;
            events[numEvents].idx = idx;
            events[numEvents].type = 1;
            ++numEvents;

            events[numEvents].x = LEFT_LIMIT;
            events[numEvents].idx = idx;
            events[numEvents].type = 0;
            ++numEvents;
            events[numEvents].x = r;
            events[numEvents].idx = idx;
            events[numEvents].type = 1;
            ++numEvents;
        }
    }

    static boolean can(double x) {
        numEvents = 0;
        for (int i = 0; i < N; ++i) {
            final Point p = points[i];
            if (x > p.max) {
                return false;
            }
        }

        bs.clear();
        numIncluded = 0;
        for (int i = 0; i < N; ++i) {
            final Point p = points[i];

            if (x < p.min) {
                ++numIncluded;
                continue ;
            }

            double angle;
            angle = Math.acos(x * cosA / p.r);
            angle = Math.abs(angle);

            addEvent(p.baseAngle - angle, p.baseAngle + angle, i);
        }

        if (numIncluded == N) {
            return true;
        }

        Arrays.sort(events, 0, numEvents);

        for (int i = 0; i < numEvents; ++i) {
            final Event e = events[i];
            if (e.type == 1) {
                bs.set(e.idx, false);
                --numIncluded;
            } else {
                bs.set(e.idx, true);
                ++numIncluded;
            }

            if (numIncluded == N) {
                return true;
            }
        }

        return false;
    }

    static void solve() throws IOException {
        N = reader.getInt(); M = reader.getInt();
        
        BASE_ANGLE = Math.toRadians(360. / M);
        RIGHT_LIMIT = Math.toRadians(360. / M / 2.0);
        LEFT_LIMIT = -RIGHT_LIMIT;

        tanA = Math.tan(BASE_ANGLE / 2.0);
        cosA = Math.cos(BASE_ANGLE / 2.0);
        sinA = Math.sin(BASE_ANGLE / 2.0);

        for (int i = 0; i < N; ++i) {
            points[i].x = reader.getInt();
            points[i].y = reader.getInt();
            points[i].calculateThings();
        }

        double lo = 0.0, hi = 4000000.0, mid;
        for (int loop = 0; loop <= LOOP_LIMIT; ++loop) {
            mid = (lo + hi) * .5;

            if (can(mid)) {
                lo = mid;
            } else {
                hi = mid;
            }
        }

        writer.println(String.format("%.10f", lo));
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


