#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;


class Vertex {
    public:
    int color = 0;
    vector <pair <int, int>> adj; // (vertex to - edge is, weight of the edge)
};
 

vector <int> OrderList;
vector <int> Component;
Vertex* originalGraph;
int ComponentNum, Count = 0;
int OriginalN;
 

void assignAllColors ( int color){
    for (int i = 0; i < OriginalN; i ++ ){
        originalGraph[i].color = color;
    }
} 

int DFS_number_of_available_vertices(Vertex* graph1, int v){
    graph1[v].color = 1;
    for (auto i: graph1[v].adj){
        if (graph1[i.first].color == 0)
            DFS_number_of_available_vertices(graph1, i.first);
    }
    return ++Count; 
}
 
int DFS(vector <vector <int>> &graph, int v, int n){
    
    originalGraph[v].color = 1;
   
    for (int i : graph[v])
        if (originalGraph[i].color == 0)
            DFS(graph, i, n);
    return ++Count;
}
 
void DFS_C(vector <vector <int>> &graph,  int v){
    originalGraph[v].color = 1;
    
    for (int i : graph[v])
        if (originalGraph[i].color == 0)
            DFS_C(graph, i);
    OrderList.push_back(v);
}
 
void DFST_C(vector <vector <int>> &GraphT, int v){
    originalGraph[v].color = 1;
    Component.push_back(v);
    for (int i : GraphT[v])
        if (originalGraph[i].color == 0)
            DFST_C(GraphT, i);
}
 
vector <vector <int>> Transpose(vector <vector <int>> &graph)
{
    vector <vector <int>> GraphT(graph.size());
    for (int i = 0; i < graph.size(); i++)
        for (int j : graph[i])
            GraphT[j].push_back(i);
    return GraphT;
}
 
void CreateOrderList(vector <vector <int>> &graph){
    for (int i = 0; i < graph.size(); i++)
        if (originalGraph[i].color == 0)
            DFS_C(graph, i);

}
 
 
void DefineComponents(vector <vector <int>> &GraphT, vector <int> &NewComponents){
    for (int i = 0; i < GraphT.size(); i++) {
        int v = OrderList[GraphT.size() - 1 - i];
        if (originalGraph[v].color == 0){
            DFST_C(GraphT, v);
            ComponentNum++;
            for (int j : Component)
                NewComponents[j] = ComponentNum - 1;
            Component.clear();
        }
    }
}
 
vector <int> Condensation(vector <vector <int>> &graph){
    ComponentNum = 0;
    vector <vector <int>> GraphT = Transpose(graph);
    vector <int> NewComponents(graph.size());
    assignAllColors(0);
    CreateOrderList(graph);
    assignAllColors(0);
    DefineComponents(GraphT, NewComponents);
    OrderList.clear();
    return NewComponents;
}
 
long long FindMST( Vertex* graph1,  int Root, int n){

    long long Result = 0;
    vector <int> MinEdge(n, INT_MAX);
 
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < graph1[i].adj.size(); j ++)
            MinEdge[graph1[i].adj[j].first] = min(graph1[i].adj[j].second, MinEdge[graph1[i].adj[j].first]);
    
    for (int i = 0; i < n; i++){
        if (i != Root) Result += MinEdge[i];
    }
 
    vector <vector <int>> ZeroEdges(n);
    

   for (int i = 0; i < n; i++)
        for (auto j : graph1[i].adj)
            if (j.second == MinEdge[j.first])
                ZeroEdges[i].push_back(j.first);

    assignAllColors(0);
    Count = 0;
    if (DFS(ZeroEdges, Root,n) == ZeroEdges.size())
        return Result;
 
 
    
    vector <int> NewComponents(n);
    NewComponents = Condensation(ZeroEdges);
 
    Vertex* NewGraph = new Vertex [ComponentNum];
    

    for (int i = 0; i < n; i++)
        for (int j = 0; j < graph1[i].adj.size(); j++)
            if (NewComponents[i] != NewComponents[graph1[i].adj[j].first])
                NewGraph[NewComponents[i]].adj.push_back({NewComponents[graph1[i].adj[j].first], graph1[i].adj[j].second - MinEdge[graph1[i].adj[j].first]});

    Result += FindMST(NewGraph, NewComponents[Root], ComponentNum);
    return Result;
}
 
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("chinese.in", "r", stdin);
    freopen("chinese.out", "w", stdout);
 
    int n, m;
    cin >> n >> m;
    OriginalN = n;

    
    originalGraph = new Vertex [n]; 
    
    assignAllColors(0);
 
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        originalGraph[a - 1].adj.push_back({b - 1, w});
    }
 
    if (DFS_number_of_available_vertices(originalGraph, 0) != n)
        cout << "NO";
    else
        cout << "YES" << endl << FindMST(originalGraph, 0, n);
 
    return 0;
}