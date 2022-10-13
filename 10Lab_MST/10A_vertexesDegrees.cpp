#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;


int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n, m;
    cin >> n >> m;

    int adj [n+1][n+1]; //adjacity - смежность
    for (int i = 1; i <= n; i ++){
        for (int j = 1; j <= n; j++){
            adj[i][j] = 0;
        }
    }

    for (int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        adj[a][b] = 1;
        adj[b][a] = 1;
    }


    for (int i = 1; i <= n; i ++){
        int degree = 0;
        for (int j = 1; j <= n; j++){
            if (adj[i][j] == 1) degree ++;
        }
        cout << degree << " ";
    }
    
   
    return 0;
}
