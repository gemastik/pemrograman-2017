#include<bits/stdc++.h>
#define ll long long
#define read(x) scanf("%d",&x);
#define readll(x) cin>>x;
#define FOR(x,a,b) for(int x=a;x<b;x++)
#define MP make_pair
#define PB push_back
#define pii pair<int,int>
#define readN(N,X) for(int i=0;i<N;i++) cin>>X[i];
#define pff pair<double,double>
#define PI 3.14159265358979323846
#define INF 9999999999999999999999.9
using namespace std;


double get_deg(int x, int y){

	double rad_angle = atan2(y, x);
	double deg = rad_angle * 180.0 / PI;
	deg += 360.0;
	if (deg > 360.0) deg -=360.0;
	return deg;

}

int N, K;
double area(double t){
	double deg = 360.0 / K;
	double r = t / cos(deg * 0.5 * PI / 180.0);

	return K*0.5*r*r*sin(deg *PI/180.0);

}

void solve(){
	cin>>N>>K;
	int x,y;
	cin>>x>>y;

	cout<<area(hypot(x,y))<<endl;
}

int main(){
	int T;
	cin>>T;
	while (T--) solve();
}