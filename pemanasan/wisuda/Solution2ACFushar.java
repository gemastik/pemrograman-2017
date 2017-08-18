import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Solution2ACFushar {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(in.readLine());
        for (int tc = 0; tc < T; tc++) {
            int N = Integer.parseInt(in.readLine());
            List<String> types = new ArrayList<>();
            List<Set<String>> members = new ArrayList<>();
            Set<String> allMembers = new HashSet<>();

            for (int i = 0; i < N; i++) {
                String[] line = in.readLine().split(" ");
                types.add(line[0]);
                int k = Integer.parseInt(line[1]);
                Set<String> member = new HashSet<>();

                for (int j = 2; j < line.length; j++) {
                    member.add(line[j]);
                    allMembers.add(line[j]);
                }
                members.add(member);
            }

            int res = allMembers.size();
            boolean outsider = false;
            for (int i = 0; i < N; i++) {
                Set<String> member = members.get(i);
                String type = types.get(i);

                if (type.equals("dibantu") && member.equals(allMembers)) {
                    outsider = true;
                    break;
                }
            }

            if (outsider) {
                res++;
            }
            System.out.println(res);
        }
    }
}

