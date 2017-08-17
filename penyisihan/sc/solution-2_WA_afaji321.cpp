/*
* Greedy: soal pertama pasti untuk si author. kalo soalnya > 2, masing2 perusahaan dapet 1.
* kalo soalnya 1, kasih ke perusahaan dengan kemunculan paling kecil di semua P
*/

#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstdio>
#include <iostream>
using namespace std;

int N;
int S[999];
int P[999][999];
int countP[999];
int sum[999];
set<int> comp;
set<int> init_set;

vector<pair<int,int> > v;
int kagi(){

        comp.clear();
        for (int i: init_set)
                comp.insert(i);

        for (int i=0;i<N;i++){
                if (S[i]==0) continue;
                for (int k=0;k<S[i];k++){
                        for (int j=0;j<countP[i];j++) {
                                if (comp.count(P[i][j])) continue;
                                comp.insert(P[i][j]);
                                break;
                        }
                }
        }
        return comp.size();
}
void solve() {
        cin>>N;
        init_set.clear();
        v.clear();
        memset(sum,0,sizeof(sum));
        int fullscore=0;
        for (int i=0;i<N;i++){
                cin>>S[i];
                fullscore+=S[i];
                S[i]--;

        }
        fullscore = min(fullscore, 100);

        for (int i=0;i<N;i++){
                cin>>countP[i];
                for (int j=0;j<countP[i];j++) {
                        cin>>P[i][j];
                        sum[P[i][j]]++;
                }
        }
        for (int i=0;i<N;i++){
                for (int j=0;j<countP[i];j++) {
                        if (S[i] == 0) break;
                        if (sum[P[i][j]] == 1) {
                                init_set.insert(P[i][j]);
                                S[i]--;
                        }
                }
        }

        int best = kagi();
        for (int i=0;i<500;i++){
                for (int j=0;j<N;j++)
                        random_shuffle(P[j], P[j] + countP[j]);
                best = max(best, kagi());
                if (N + best == fullscore) {
                        break;
                }
        }
        cout<<N + best <<endl;
}

int main() {
        int T;
        cin>>T;
        while(T--) solve();
}