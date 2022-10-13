#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>

using namespace std;

struct NodeSimple{
    int numOfNode;
    NodeSimple* next;
};


class Node {
public:     
    bool visited;
    int color; //1 - winVertex, 2 - loseVertex
    NodeSimple* inzedentWith;
    

    Node(){
        visited = false;
        color = 0;
        inzedentWith = nullptr;
    }

    void addNewEdge (const int & edgeEnd){

        NodeSimple* newNodeSPointer = new NodeSimple;
        newNodeSPointer->numOfNode = edgeEnd;
        newNodeSPointer->next = nullptr;
        
        if (inzedentWith == nullptr) {
            inzedentWith = newNodeSPointer;
        } else {
            newNodeSPointer->next = inzedentWith;
            inzedentWith = newNodeSPointer;
        }
    
    }

};


void graphDFS (int u, Node graphN[]){

    graphN[u].visited = true;

    NodeSimple* curPointer = graphN[u].inzedentWith;
    while (curPointer != nullptr) {
        int v = curPointer->numOfNode; 
         
        if (!graphN[v].visited){
            graphDFS(v, graphN); 
        } 

        if (graphN[v].color == 0) { 
            graphN[u].color  = 1; 
        }
        
        
        curPointer = curPointer->next;
    }
}


int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    

    int n, m , s; //s - вершина, из которой стартуем
    cin >> n >> m >> s;

    Node graphN[n];
    stack <int> stack1; 

    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        graphN[a-1].addNewEdge(b-1);   
    }

    for (int i = 0; i < n; i++) {

        if (!graphN[i].visited)
            graphDFS(i, graphN);
    }

    if (graphN[s-1].color == 1) {
        cout << "First player wins";
    } else {
        cout << "Second player wins";
    }
    
   
    return 0;
}