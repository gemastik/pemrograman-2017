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
	if (K == 1){
		for (int i=0;i<N;i++){
			a.push_back(0); b.push_back(1); c.push_back(2);
		}
		done();
		return;
	}
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
	
	int win = N/K;
	for (int i=0;i<K;i++)
		for (int j=0;j<win;j++){
			a.push_back(i); b.push_back((i+1) % K); c.push_back((i+2) % K);
		}

	int ptr = 0;
	for (int i=K;i<M;i++){
		if (a.size() == N) break;
		for (int j=0;j<win;j++){
			if (a.size() == N) break;
			if (i == K && j == 0) continue;
			a.push_back(i); 
			if (i == K){
				b.push_back(b[ptr]); b[ptr++] = K; 
				c.push_back(c[ptr]); c[ptr++] = K;
			} else {
				b.push_back(K);
				c.push_back(c[ptr]); c[ptr++] = K;
			}
		}
	}	
	done();
}

int main(){
	int T;
	cin>>T;
	while(T--) solve();
}