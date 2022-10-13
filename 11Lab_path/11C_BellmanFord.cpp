#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
struct Edge{
    int start, fin, w;
};


int main (){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("pathbgep.in", "r", stdin);
    freopen("pathbgep.out", "w", stdout);

    int n, m; 
    cin >> n >> m;
    //int adj [30002][30002];
    vector <Edge> graph ((m+1));


    //vector <vector<int>> adj (n+1, vector<int>(n+1)); 
     
    const int inf = 10000000;

    vector <int> dist (n+1);
    vector <int> parent (n+1);
    for (int i = 1; i <= n; i++) {
        dist[i] = inf;
        parent[i] = 0;
    }
    //dist.assign(n+1, inf);
    //parent.assign(n+1, 0);
    dist[1] = 0;


    /*for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            adj[i][j] = inf;
        }
    }*/
    for (int i = 1; i<=m; i++){
        int a, b, c; 
        cin>>a>>b>>c;
        graph[i].start = a;
        graph[i].fin = b;
        graph[i].w = c;
        /*adj[a][b] = c;
        adj[b][a] = c;*/
    }

    //Bellman-Ford

   /* for (int i = 1; i <= n; i++){
        for (int v = 1; v <= n; v++){
            for (int u = 1; u <= n; u++){
                if (adj[v][u] != inf) {
                    if (dist[v] > dist[u] + adj[u][v]) {
                        dist[v] =  dist[u] + adj[u][v];
                        parent[v] = u; 
                    }
                    
                }
            }        
        }
    }*/

    for (int i = 1; i <= n; i++) {
        for (int v = 1; v <= n; v++){

            for (int j = 1; j <=m; j++){
                if (graph[j].start == v) {
                    int u = graph[j].fin;
                    if (dist[v] > dist[u] + graph[j].w) {
                        dist[v] =  dist[u] + graph[j].w;
                        parent[v] = u; 
                    }
                }
                if (graph[j].fin == v) {
                    int u = graph[j].start;
                    if (dist[v] > dist[u] + graph[j].w) {
                        dist[v] =  dist[u] + graph[j].w;
                        parent[v] = u; 
                    }
                }
            }


        }
    }

    for (int i = 1; i <= n; i++){
        cout<<dist[i] <<" ";
    }
    

    
    return 0;
}
