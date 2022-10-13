#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;


int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("pathmgep.in", "r", stdin);
    freopen("pathmgep.out", "w", stdout);
    
    int n, m;
    cin >> n >> m;

    int adj [n+1][n+1]; //adjacity - смежность
    
    for (int i = 1; i <= n; i ++){
        for (int j = 1; j <= n; j++){
            adj[i][j] = 100000;
            if (i == j) adj[i][j] = 0;
        }
    }

    for (int i = 0; i < m; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        adj[a][b] = c;
    }


    
    for (int i = 1; i <= n; i ++) {
        for (int u = 1; u <= n; u++){
            for (int v = 1; v <= n; v++){
                adj[u][v] = min(adj[u][v], adj[u][i] + adj[i][v]);
            }
        }
    }
    

    for (int i = 1; i <= n; i ++) {
        for (int u = 1; u <= n; u++){
            for (int v = 1; v <= n; v++){
                adj[i][u] = min(adj[i][u], adj[i][v] + adj[v][u]);
            }
        }
    }

    cout<<endl;
    for (int i = 1; i <= n; i ++){
        for (int j = 1; j <= n; j++){
            cout << adj[i][j] << " ";
        }
        cout<<endl;
    }
   
    return 0;
}
