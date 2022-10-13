#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;



int main (){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("negcycle.in", "r", stdin);
    freopen("negcycle.out", "w", stdout);
    int n; cin >> n;
    long long adj [n+1][n+1];
    const long long inf = -1000000000;

    vector <long long> dist (n+1);
    vector <int> parent (n+1);
    dist.assign(n+1, inf);
    parent.assign(n+1, 0);


    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            cin >> adj[i][j];
        }
    }

    for (int i = 1; i <= n; i++){
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
    }

    bool exit = false;      
    vector <int> answer;
    for (int v = 1; v <= n; v++){
        for (int u = 1; u <= n; u++){
            if (dist[v] > dist[u]+adj[u][v]) {
                for (int i = 1; i < n; i++){
                v = parent[v]; }
                u = v;
                while ( u != parent[v]){
                    answer.push_back(v);
                    v = parent[v];
                }
                answer.push_back(v);
                v = parent[v];
                answer.push_back(v);

                reverse(answer.begin(), answer.end());
                exit = true;
                break;
            }
        
        }
        if (exit) break;
    }
    

    if (answer.size() > 0) {
        cout<<"YES\n" << answer.size() << "\n"; 
        for (int i = 0; i < answer.size(); i++ ){
            cout<<answer[i]<<" ";
        }
    } else  cout<<"NO";
    
    

    
    return 0;
}
