#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <cstdio>
#include <iostream>
#define N 50
#define M 2500
using namespace std;

int S[999];
int P[999][999];
int countP[999];

bool bpm(bool bpGraph[M][N], int u, bool seen[], int matchR[])
{
    // Try every job one by one
    for (int v = 0; v < N; v++)
    {
        // If applicant u is interested in job v and v is
        // not visited
        if (bpGraph[u][v] && !seen[v])
        {
            seen[v] = true; // Mark v as visited

            // If job 'v' is not assigned to an applicant OR
            // previously assigned applicant for job v (which is matchR[v])
            // has an alternate job available.
            // Since v is marked as visited in the above line, matchR[v]
            // in the following recursive call will not get job 'v' again
            if (matchR[v] < 0 || bpm(bpGraph, matchR[v], seen, matchR))
            {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}

// Returns maximum number of matching from M to N
int maxBPM(bool bpGraph[M][N])
{
    // An array to keep track of the applicants assigned to
    // jobs. The value of matchR[i] is the applicant number
    // assigned to job i, the value -1 indicates nobody is
    // assigned.
    int matchR[N];

    // Initially all jobs are available
    memset(matchR, -1, sizeof(matchR));

    int result = 0; // Count of jobs assigned to applicants
    for (int u = 0; u < M; u++)
    {
        // Mark all jobs as not seen for next applicant.
        bool seen[N];
        memset(seen, 0, sizeof(seen));

        // Find if the applicant 'u' can get a job
        if (bpm(bpGraph, u, seen, matchR))
            result++;
    }
    return result;
}


void solve() {
    int NN;
    cin>>NN;
    for (int i=0;i<NN;i++){
        cin>>S[i];
        S[i]--;
    }

    bool bpgraph[M][N];
    memset(bpgraph,0,sizeof(bpgraph));

    for (int i=0;i<NN;i++){
        cin>>countP[i];
        for (int j=0;j<countP[i];j++) {
            cin>>P[i][j];
            P[i][j]--;
        }
        for (int j=0;j<S[i];j++)
            for (int k=0;k<countP[i];k++)
                bpgraph[i*50 + j][P[i][k]]=1;
    }

    cout<<NN + maxBPM(bpgraph)<<endl;
}

int main() {
    int T;
    cin>>T;
    while(T--) solve();
}