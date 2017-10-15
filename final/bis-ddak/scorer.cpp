#include <bits/stdc++.h>

#define __INIT_CC__ ios::sync_with_stdio(false); \
    cin.tie(0);

#ifdef __WIN32__
    char getchar_unlocked() {return getchar();}
#endif

#define FOR(_i,_n,_m) for(int (_i)=(_n),_t=(_m);_i<(_t);++(_i))
#define FORN(_i,_n,_m) for(int (_i)=(_n),_t=(_m);_i<=(_t);++(_i))
#define FORD(_i,_n,_m) for(int (_i)=(_n),_t=(_m);_i>=(_t);--(_i))
#define RESET(_a,_value) memset(_a,_value,sizeof(_a))
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define ff first
#define ss second
#define mp make_pair
#define SIZE(_a) (int)_a.size()
#define VSORT(_a) sort(_a.begin(),_a.end())
#define SSORT(_a,_val) sort(_a,_a+(_val))
#define ALL(_a) _a.begin(),_a.end()
#define mt make_tuple
#define _get(_tuple,_i) get<_i>(_tuple)
#define eb emplace_back
 
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using ll = long long;
using ull = unsigned long long;
using pll = pair<ll,ll>;
using vpll = vector<pll>;
using vll = vector<ll>;
using pdd = pair<double,double>;
using vpdd = vector<pdd>;
template <typename T> using uset = unordered_set<T>;
template <typename T> using umultiset = unordered_multiset<T>;
template <typename K, typename V> using umap = unordered_map<K, V>;
template <typename K, typename V> using umultimap = unordered_multimap<K, V>;

const int dr[] = { 1, 0,-1, 0, 1, 1,-1,-1};
const int dc[] = { 0, 1, 0,-1, 1,-1,-1, 1};
const double eps = 1e-9;
const int INF = 0x7FFFFFFF;
const ll INFLL = 0x7FFFFFFFFFFFFFFFLL;
const double pi = acos(-1);

template <typename T> T take(queue<T> &O) {T tmp=O.front();O.pop();return tmp;}
template <typename T> T take(stack<T> &O) {T tmp=O.top();O.pop();return tmp;}
template <typename T> T take(priority_queue<T> &O) {T tmp=O.top();O.pop();return tmp;}
template <typename T>
inline bool inRange(const T& z, const T& a, const T& b){return a <= z && z <= b;}

void OPEN(const string& in = "input.txt", const string& out = "output.txt")
{
    freopen(in.c_str(), "r", stdin);
    freopen(out.c_str(), "w", stdout);
    return ;
}

//using sokokaleb's template v4.0

int wa() {
    cout << "WA" << endl;
    return 0;
}

int ac() {
    cout << "AC" << endl;
    return 0;
}

constexpr int MAX_N = 505;

int T;
int N, M;
int loop_cost[MAX_N];
int cozt[MAX_N][MAX_N];

int tc_ans_cost;
int con_ans_cost;
bitset<MAX_N> in_circuit;

ifstream tc_in, tc_out, con_out;

using Constraint = function<bool(void)>;

void check(const Constraint& c) {
    if (!c()) {
        wa();
        exit(0);
    }
}

void check(const bool& x) {
    if (!x) {
        wa();
        exit(0);
    }
}

void resetVars() {
    FORN (i, 1, MAX_N - 1) {
        FORN (j, 1, MAX_N - 1) {
            cozt[i][j] = -1;
        }
    }
}

template <typename T>
void read(T& x) {
    if (!(con_out >> x)) {
        wa();
        exit(0);
    }
}

int main(int argc, char** argv) {
    tc_in.open(argv[1]);
    tc_out.open(argv[2]);
    con_out.open(argv[3]);

    tc_in >> T;
    FORN (tc, 1, T) {
        resetVars();

        tc_in >> N >> M;
        FORN (i, 1, N) {
            tc_in >> loop_cost[i];
        }
        FORN (i, 1, M) {
            int u, v, w;
            tc_in >> u >> v >> w;
            cozt[u][v] = w;
        }

        tc_out >> tc_ans_cost;
        read(con_ans_cost);

        check(tc_ans_cost == con_ans_cost);

        in_circuit.reset();

        int num_circuit;
        read(num_circuit);

        check(inRange(num_circuit, 0, N / 2));
        
        FOR (c, 0, num_circuit) {
            int x;
            read(x);
            check(inRange(x, 2, N));
            int lst = -1;
            int fi = -1;
            FOR (i, 0, x) {
                int u;
                read(u);
                check(!in_circuit.test(u));
                in_circuit.set(u, 1);
                if (fi == -1) fi = u;
                if (lst != -1) {
                    check(u != lst);
                    check(cozt[lst][u] != -1);
                    con_ans_cost -= cozt[lst][u];
                }
                lst = u;
            }
            check(lst != fi);
            check(cozt[lst][fi] != -1);
            con_ans_cost -= cozt[lst][fi];
        }
        
        FORN (i, 1, N) {
            if (!in_circuit.test(i)) {
                con_ans_cost -= loop_cost[i];
            }
        }

        check(con_ans_cost == 0);

        // exhaust the tc's input for this tc
        int x;
        tc_in >> x;
        for (int z = 0, _ = x; z < _; ++z) {
            tc_in >> x;
            for (int i = 0, __ = x; i < __; ++i) {
                tc_in >> x;
            }
        }
    }

    string lol;
    if (con_out >> lol) {
        return wa();
    }
    return ac();
}
