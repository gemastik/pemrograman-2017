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

const auto MUSTAHIL = "mustahil";
const auto MAX_CONSECUTIVE_MALE = 2;
const auto MALE = 'L';
const auto FEMALE = 'P';
const set<char> PERMISSIBLE_CHARS = {'L', 'P'};

int T;
int A, B, K;
string ans;
string con_ans;

ifstream tc_in, tc_out, con_out;

using Constraint = function<bool(void)>;

const vector<Constraint> MUSTAHIL_CONSTRAINTS = {
    [] { return !!(con_out >> con_ans); },
    [] { return con_ans == MUSTAHIL; }
};

const vector<Constraint> NORMAL_CONSTRAINTS = {
    [] { return !!(con_out >> con_ans); },
    [] { return all_of(ALL(con_ans), [](const char& c) { return PERMISSIBLE_CHARS.count(c); }); },
    [] { return SIZE(con_ans) == A + B; },
    [] { return count(ALL(con_ans), MALE) == A; },
    [] { return count(ALL(con_ans), FEMALE) == B; },
    [] {
        // Check consecutive elements
        // LL
        // P... (k times at most) ...P
        using State = tuple<int, char, bool>;
        auto res = accumulate(ALL(con_ans), mt(0, '-', true), [](const State acc, char el) {
            int cnt;
            char last;
            bool res;
            tie(cnt, last, res) = acc;
            if (!res) {
                return mt(-1, ' ', false);
            }
            if (last == el) {
                ++cnt;
            } else {
                cnt = 1;
            }
            res = (el == MALE ? (cnt <= MAX_CONSECUTIVE_MALE) : (cnt <= K));
            return mt(cnt, el, res);
        });
        return _get(res, 2);
    }
};

int main(int argc, char** argv) {
    tc_in.open(argv[1]);
    tc_out.open(argv[2]);
    con_out.open(argv[3]);

    tc_in >> T;
    FORN (tc, 1, T) {
        tc_in >> A >> B >> K;
        tc_out >> ans;

        const auto& USED_CONSTRAINTS = (ans == MUSTAHIL ? MUSTAHIL_CONSTRAINTS : NORMAL_CONSTRAINTS);

        // If any of the constraint is not fulfilled...
        const auto failing_constraint = [] (const Constraint& c) { return !c(); };
        if (any_of(ALL(USED_CONSTRAINTS), failing_constraint)) {
            // you're wrong, then.
            return wa();
        }
    }
    return ac();
}
