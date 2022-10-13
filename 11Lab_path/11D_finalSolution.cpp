#include <iostream>
#include <vector>

using namespace std;


const long long int inf = 9000000000000000000;
   


vector <long long int> dist;
vector <int> parent;
vector <int> start ;
vector <int> fin ;
vector <long long int> weight ;


int main()
{
    
    //freopen("path.in", "r", stdin); freopen("path.out", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    long long n, s, m; int x;
    cin >> n >> m >> s;
  
    
    
    
    dist = vector<long long>(n+1, inf);
    parent = vector<int>(n+1, -1);
    start = vector <int> (m, 0);
    fin = vector <int> (m, 0);
    weight = vector <long long> (m, 0);
   
    for (long long i = 0; i < m; i++) {
        cin >> start[i] >> fin[i] >> weight[i];
        
    }
    dist[s] = 0;
    vector <int> negCycleVertexes;
    for (long long i = 1; i <= n; i++) {
        x = -1;
        for (long long j = 0; j < m; j++) {
            int tmp = x;
            if (dist[start[j]] < inf)
                {
                    if (dist[fin[j]] > dist[start[j]] + weight[j]) {
                        dist[fin[j]] = max(-inf, dist[start[j]] + weight[j]);
                        parent[fin[j]] = start[j];
                        x = fin[j];
                           
                     }
                }
            if (i == n && tmp != x) { 
            negCycleVertexes.push_back(x);}
                
        }
    }
    

    while (!negCycleVertexes.empty())
    {
        int y = negCycleVertexes.back();
        negCycleVertexes.pop_back();
        int counter = 0;
        while (y >= 0 && counter < n) {
            dist[y] = -inf;
            y = parent[y];
            counter++;
        }
        
    }

    


    for (long long i = 1; i <= n; i++){
        for (long long j = 0; j < m; j++)
            if (dist[start[j]] == -inf) dist[fin[j]] = -inf;
    }
       

    
    for (long long i = 1; i <= n; i++) {
        if (dist[i] == -inf)
            cout << "-" << "\n";
        else if (dist[i] < inf)
            cout << dist[i] << "\n";
        else if
            cout << "*" << "\n";
    }
    return 0;
}