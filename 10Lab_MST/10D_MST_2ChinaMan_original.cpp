#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;
class Edge {
    int entrance;
    int exit;
    int weight;
};

class Vertex {
    int color;
    int component;
};
 
vector <char> Color;
vector <int> OrderList;
vector <int> Component;
int ComponentNum, Count = 0;
 

 
int DFS_number_of_available_vertices(vector <vector <pair <int, int>>>& graph, int v){
    Color[v] = 1;
    for (auto i : graph[v]){
        if (Color[i.first] == 0)
            DFS_number_of_available_vertices(graph, i.first);
    } 
    return ++Count; 
    //Если пройдемся не по всем вершинам, то получается попасть в какие то вершины не можем
    //возращаем число вершин, в которые можем попасть. Есди оно меньш общего количества вершин в графе
}
 
int DFS(vector <vector <int>> &graph, int v)
{
    Color[v] = 1;
    for (int i : graph[v])
        if (Color[i] == 0)
            DFS(graph, i);
    return ++Count;
}
 
void DFS_C(vector <vector <int>> &graph, int v)
{
    Color[v] = 1;
    for (int i : graph[v])
        if (Color[i] == 0)
            DFS_C(graph, i);
    OrderList.push_back(v);
}
 
void DFST_C(vector <vector <int>> &GraphT, int v)
{
    Color[v] = 1;
    Component.push_back(v);
    for (int i : GraphT[v])
        if (Color[i] == 0)
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
 
void CreateOrderList(vector <vector <int>> &graph)
{
    Color.assign(graph.size(), 0);
 
    for (int i = 0; i < graph.size(); i++)
        if (Color[i] == 0)
            DFS_C(graph, i);
}
 
 
void DefineComponents(vector <vector <int>> &GraphT, vector <int> &NewComponents)
{
    Color.assign(GraphT.size(), 0);
 
    for (int i = 0; i < GraphT.size(); i++) {
        int v = OrderList[GraphT.size() - 1 - i];
        if (Color[v] == 0)
        {
            DFST_C(GraphT, v);
            ComponentNum++;
            for (int j : Component)
                NewComponents[j] = ComponentNum - 1;
            Component.clear();
        }
    }
}
 
vector <int> Condensation(vector <vector <int>> &graph)
{
    ComponentNum = 0;
    vector <vector <int>> GraphT = Transpose(graph);
    vector <int> NewComponents(graph.size());
    CreateOrderList(graph);
    DefineComponents(GraphT, NewComponents);
    OrderList.clear();
    return NewComponents;
}
 
long long FindMST(vector <vector <pair <int, int>>> &graph, int n, int Root){

    long long Result = 0;
    vector <int> MinEdge(n, INT_MAX);
 
    for (auto & i : graph)
        for (auto j : i)
            MinEdge[j.first] = min(j.second, MinEdge[j.first]);
 
    for (int i = 0; i < graph.size(); i++){
        if (i != Root) Result += MinEdge[i];
    }
 
    vector <vector <int>> ZeroEdges(n);
    for (int i = 0; i < graph.size(); i++)
        for (auto j : graph[i])
            if (j.second == MinEdge[j.first])
                ZeroEdges[i].push_back(j.first);
 
    Color.assign(ZeroEdges.size(), 0);
    Count = 0;
    if (DFS(ZeroEdges, Root) == ZeroEdges.size())
        return Result;
 
 
    vector <int> NewComponents(graph.size());
    NewComponents = Condensation(ZeroEdges);
 
    vector <vector <pair <int, int>>> NewGraph(ComponentNum);
    for (int i = 0; i < graph.size(); i++)
        for (auto j : graph[i])
            if (NewComponents[i] != NewComponents[j.first])
                NewGraph[NewComponents[i]].push_back({NewComponents[j.first], j.second - MinEdge[j.first]});
 
    Result += FindMST(NewGraph, ComponentNum, NewComponents[Root]);
    return Result;
}
 
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("chinese.in", "r", stdin);
    freopen("chinese.out", "w", stdout);
 
    int n, m;
    cin >> n >> m;

    vector <vector <pair <int, int>>> graph (n); // first - vertex, second - weight //список смежности на массиве
 
    Color.assign(n, 0);
 
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        //graph[a - 1].push_back(make_pair(b - 1, w));
        graph[a - 1].push_back({b - 1, w});
    }
 
    if (DFS_number_of_available_vertices(graph, 0) != n)
        cout << "NO";
    else
        cout << "YES" << endl << FindMST(graph, graph.size(), 0);
 
    return 0;
}