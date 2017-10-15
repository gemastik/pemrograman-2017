/*WA = ternary searchnya full 360, instead of 360/K
*/

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
vector<pair< double, pair<int,int> > > points;


double check(double deg){
	double dist = INF;
	for (int i=0;i<N;i++){
		double d = points[i].first + deg;
		if (d > 360.0) d -= 360.0;

		double tri_deg = 360.0 / K;
		while (d > tri_deg) d-= tri_deg;
		if (d > (tri_deg/2.0)){
			d = tri_deg - d;
		}
		d = tri_deg/2.0 - d;
		//get distance
		double jarak = abs(cos(d * PI / 180.0) * hypot(points[i].second.first, points[i].second.second ));
		dist = min(dist, jarak);
	}
	return dist;
}

double area(double t){
	double deg = 360.0 / K;
	double r = t / cos(deg * 0.5 * PI / 180.0);

	return K*0.5*r*r*sin(deg *PI/180.0);

}

void solve(){
	points.clear();
	cin>>N>>K;
	for (int i=0;i<N;i++){
		int x,y;
		cin>>x>>y;
		points.push_back({get_deg(x,y), {x, y} });

	}

	//binser gan
	double D = 360.0;
	double lo = 0.0;
	double hi = D;
	int steps = 100;
	while (steps--){
		double left= (2.0 * lo + hi) / 3.0;
		double right = (lo + 2.0 * hi) / 3.0;
		if (check(left) < check(right))
			lo = left;
		else
			hi = right;
	}
	cout<<area(check(lo))<<endl;
}

int main(){
	int T;
	cin>>T;
	while (T--) solve();
}