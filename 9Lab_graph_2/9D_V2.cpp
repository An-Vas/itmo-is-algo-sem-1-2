#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

struct NodeSimple{
    int numOfNode;
    NodeSimple* next;
};


std::vector <int> topSequence;





class Node {
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
        
        if (inzedentWith == nullptr) {
            inzedentWith = newNodeSPointer;
        } else {
            newNodeSPointer->next = inzedentWith;
            inzedentWith = newNodeSPointer;
        }
    
    }

    void addNewRevEdge (const int & edgeEnd){

        NodeSimple* newNodeSPointer = new NodeSimple;
        newNodeSPointer->numOfNode = edgeEnd;
        newNodeSPointer->next = nullptr;
        
        if (revInzedentWith == nullptr) {
            revInzedentWith = newNodeSPointer;
        } else {
            newNodeSPointer->next = revInzedentWith;
            revInzedentWith = newNodeSPointer;
        }
    
    }

};




void graphDFS (int top, Node graphN[]){

    graphN[top].visited = true;

    NodeSimple* curPointer = graphN[top].inzedentWith;
    while (curPointer != nullptr) {
        int v = curPointer->numOfNode; 
         
        if (!graphN[v].visited){
             graphDFS(v, graphN);   
        } 
        
        curPointer = curPointer->next;
    }

    topSequence.push_back(top);
}


void reversGraphDFS (int top, int componentsCount, Node graphN[]) {

    graphN[top].visited = true;
    graphN[top].componentNum = componentsCount;
    

    NodeSimple* curPointer = graphN[top].revInzedentWith;
    while (curPointer != nullptr) {
        int v = curPointer->numOfNode; 
         
        if (!graphN[v].visited){
            reversGraphDFS(v,  componentsCount, graphN);   
        } 
        
        curPointer = curPointer->next;
    }
}


int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("cond.in", "r", stdin);
    freopen("cond.out", "w", stdout);
    

    int n, m;
    std::cin >> n >> m;


    Node graphN[n];

    for (int i = 0; i < m; i++){
        int a, b;
        std::cin >> a >> b;
        graphN[a-1].addNewEdge(b-1);
        graphN[b-1].addNewRevEdge(a-1);
        
    }
   

    int componentCount = 0;

   
    for (int i = 0; i < n; i++){
        graphN[i].visited = false;
    }

    for (int i = 0; i < n; i++){

        if (!graphN[i].visited) {
        
            graphDFS(i, graphN);
        }
    }



    for (int i = 0; i < n; i++){
        graphN[i].visited = false;
    }

    std::reverse (topSequence.begin(), topSequence.end());
    for (int top : topSequence){

        if (!graphN[top].visited) {
        
            componentCount++;
            reversGraphDFS(top, componentCount, graphN);
        }
    }

    cout << componentCount << endl;
    for (int i = 0; i < n; i++)
        cout << graphN[i].componentNum << " ";
        

    return 0;
}