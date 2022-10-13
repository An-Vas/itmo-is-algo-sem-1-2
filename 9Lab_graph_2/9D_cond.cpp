#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct NodeSimple{
    int numOfNode;
    NodeSimple* next;
};

struct Node {
public:    
    bool visited;
    int componentNum;
    NodeSimple* inzedentWith;
    NodeSimple* revInzedentWith;

    Node(){
        visited = false;
        componentNum = 0;
        inzedentWith = nullptr;
        revInzedentWith = nullptr;
    }
    void addNewEdge (const int & edgeEnd){

        NodeSimple* newNodeSPointer = new NodeSimple;
        newNodeSPointer->numOfNode = edgeEnd;
        newNodeSPointer->next = nullptr;
        NodeSimple* curPointer =  inzedentWith;
        
        if (inzedentWith == nullptr) {
            inzedentWith = newNodeSPointer;
        } else {
            newNodeSPointer->next = inzedentWith;
            inzedentWith = newNodeSPointer;
        }
    
}
   
};



void addNewEdge (int edgeStart, int edgeEnd, Node arr[]){

    NodeSimple* newNodeSPointer = new NodeSimple;
    newNodeSPointer->numOfNode = edgeEnd;
    newNodeSPointer->next = nullptr;
    NodeSimple* curPointer =  arr[edgeStart].inzedentWith;
    
    if (arr[edgeStart].inzedentWith == nullptr) {
        arr[edgeStart].inzedentWith = newNodeSPointer;
    } else {
        newNodeSPointer->next = arr[edgeStart].inzedentWith;
        arr[edgeStart].inzedentWith = newNodeSPointer;
    }
    
}

void addNewRevEdge (int edgeStart, int edgeEnd, Node arr[]){

    NodeSimple* newNodeSPointer = new NodeSimple;
    newNodeSPointer->numOfNode = edgeEnd;
    newNodeSPointer->next = nullptr;
    NodeSimple* curPointer =  arr[edgeStart].revInzedentWith;
    
    if (arr[edgeStart].revInzedentWith == nullptr) {
        arr[edgeStart].revInzedentWith = newNodeSPointer;
    } else {
        newNodeSPointer->next = arr[edgeStart].revInzedentWith;
        arr[edgeStart].revInzedentWith = newNodeSPointer;
    }
    
}



void reversGraphDFS (Node graph[], const int & n, int u, int componentsCount, vector <int> & componentNum) {

    //isBurn[top] = true;
    graph[u].visited = true;
    componentNum[u] = componentsCount;
    //strongComponent[top] = componentsCount;
    //graph[u].componentNum = componentsCount;

    NodeSimple* curPointer = graph[u].revInzedentWith;
    while (curPointer != nullptr) {
        int v = curPointer->numOfNode; 
         
        if (!graph[v].visited){
            reversGraphDFS(graph, n, v, componentsCount, componentNum);   
        } 
        
        curPointer = curPointer->next;
    }

    /*for (int i : graphRevers[top]) {
        if (!isBurn[i]) {
            reversGraphDFS(i, componentsCount);
        }
    }*/
}


void graphDFS_andTopSort ( Node graph[], const int & n, int u, vector <int> & topSortList){  
    graph[u].visited = true;

    NodeSimple* curPointer = graph[u].inzedentWith;
    cout<<"start"<<endl;
    while (curPointer != nullptr) {
        cout<<"start while"<<endl;
        int v = curPointer->numOfNode; 
        cout<<"v = "<<v<<endl;
         
        if (!graph[v].visited){
             graphDFS_andTopSort(graph, n, v, topSortList);   
        } 
        
        curPointer = curPointer->next;
    }
    //if (!graph[u].alreadyInQueue) { 
        topSortList.push_back(u); //graph[u].alreadyInQueue = true; }
    //graph[u].color = 2;
    cout<<"fin"<<endl;
    
}

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    //freopen("cond.in", "r", stdin);
    //freopen("cond.out", "w", stdout);
   
    
    int n, m; // n - count of vertexes; m - count of Edges of Graph;
    cin>>n>>m;

    Node graph[n+1];
  
    vector <int>  topSortList(n+1);
    vector <int>  ComponentNum(n+1);

    for (int i = 1; i<=n; i++){
        graph[i].inzedentWith = nullptr;  
        graph[i].revInzedentWith = nullptr; 
        graph[i].visited = false;
    }

    

    for (int i = 0; i<m; i++){
        int a,b;
        cin>>a>>b;
        addNewEdge(a, b, graph);
        addNewRevEdge(b, a, graph);
    }

   int componentCount = 0;
   for (int i = 1; i <= n; i++){
        if (!graph[i].visited) {
            graphDFS_andTopSort(graph, n, i, topSortList);
        }
    }
    for (int i = 1; i <= n; i++){
        graph[i].visited = false;
    }
    cout<<"SFD";
    for (int i : topSortList){

        if (!graph[i].visited) {
            componentCount++;
            reversGraphDFS(graph, n, i, componentCount, ComponentNum);
        }
    }
    cout << componentCount << "\n";

    for (int i = 1; i <= n; i++)
        std::cout << ComponentNum[i]<<" ";

   
    return 0;
}
