#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const long long inf = 200000000000000;

class Vertex {
    public:
    vector <std::pair <int, int>> edges;
};


int main ()
{
    cin.tie(0); //cout.tie(0);
    ios_base::sync_with_stdio(0);
    //freopen("pathbgep.in", "r", stdin);
    //freopen("pathbgep.in", "w", stdout);
    int n, m;
    cin >> n >> m;

    
    Vertex* graph = new Vertex [n+1];
    set <pair <long long, int>> q;
    
    bool* inQueue = new bool [n+1];
    long long* dist = new  long long[n+1];


    for (int i = 1; i<=m; i++){
        int a,b,c; 
        cin>>a>>b>>c;
        graph[a].edges.push_back({b,c});
        graph[b].edges.push_back({a,c});
    }

    for (int i= 1; i<=n; i++) {
        dist[i] = inf;
        inQueue[i] = true;
    }
  
 

    int s = 1;
    dist[s] = 0;
    q.insert ({0, s});

    //Deikstra

    for (int i = 1; i <= n; i++) {
        s = q.begin()->second;
        q.erase(q.begin());  
        for (int j = 0; j < graph[s].edges.size(); j++) {
                int k = graph[s].edges[j].first;
                if (dist[k] > dist[s] +  graph[s].edges[j].second) {
                    q.erase({dist[k], k});
                    dist[k] = dist[s] +  graph[s].edges[j].second;
                    q.insert({dist[k], k});
                    
                }
        }
    }

    for (int i = 1; i <=n; i++){  cout << dist[i] <<" "; }

    delete[] inQueue;
    delete[] dist;
    return 0;
}
