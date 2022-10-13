#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

const long long inf = 200000000000000;

int adj [2001][2001];
bool inQueue[2001];
long long dist [2001];
int n, s, f;

int extracrMin_vector () {
    long long min = inf; 
    int minNumOf = -1;
    for (int i = 1; i <= n; i++) {

        if (inQueue[i] && (dist[i] <= min)){
            min = dist[i];
            minNumOf = i;
        }

    }
    inQueue[minNumOf] = false;
    return minNumOf;

}



int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("pathmgep.in", "r", stdin);
    freopen("pathmgep.out", "w", stdout);

    cin >> n >> s >> f;
  
    for (int i = 1; i <= n; i ++){
        for (int j = 1; j <= n; j++){
            long long a;
            cin >> adj[i][j];
        }
        dist[i] = inf;
        inQueue[i] = true;
    }
    dist[s] = 0;

    //Deijkstra

    for (int i = 1; i <= n; i++) {
        int s = extracrMin_vector();     
        for (int j = 1; j <= n; j++) {
            if ((adj[s][j] != -1) && (dist[s]!= inf)) {

                if (dist[j] > dist[s] + adj[s][j]) {
                    dist[j] = dist[s] + adj[s][j];
                } 
                
            }

        }
        
    }

   
   
    if (dist[f] == inf) cout << -1; 
    else cout << dist[f];

    return 0;
}
