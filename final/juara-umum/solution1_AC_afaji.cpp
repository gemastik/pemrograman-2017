#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#define ll long long
#define read(x) scanf("%d",&x);
#define readll(x) cin>>x;
#define FOR(x,a,b) for(int x=a;x<b;x++)
#define MP make_pair
#define PB push_back
#define pii pair<int,int>
#define readN(N,X) for(int i=0;i<N;i++) cin>>X[i];
#define pff pair<double,double>
using namespace std;

int N,M,K;
vector<int> a,b,c;

void done(){
	if (a.size() < N) {
		cout<<"mustahil"<<endl;
		return;
	} else {
		cout<<"mungkin"<<endl;
		for (int i=0;i<N;i++)
			cout<<a[i]+1<<" "<<b[i]+1<<" "<<c[i]+1<<endl;
	}

}
void solve(){
	a.clear();
	b.clear();
	c.clear();
	cin>>N>>M>>K;
	if (K == 2){
		int N2 = N/2;
		N2 *= 2;
		for (int i=0;i<N2;i++){
			a.push_back(i % 2);
			b.push_back((i + 1) % 2);
			c.push_back(2);
		}
		if (N % 2 && N > 3){
			a.push_back(2);
			b.push_back(1);
			c.push_back(0);
			swap(b[0], c[0]);			
		}
		done();
		return;
	}	
	done();
}

int main(){
	int T;
	cin>>T;
	while(T--) solve();
}