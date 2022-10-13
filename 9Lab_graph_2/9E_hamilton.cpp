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
    int color;
    int componentNum;
    NodeSimple* inzedentWith;
    NodeSimple* revInzedentWith;

    Node(){
        visited = false;
        color = 0;
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

};


void graphDFS (int u, Node graphN[], stack <int>& stack1){

    graphN[u].color = 1;

    NodeSimple* curPointer = graphN[u].inzedentWith;
    while (curPointer != nullptr) {
        int v = curPointer->numOfNode; 
         
        if (graphN[v].color == 0){
             graphDFS(v, graphN, stack1);   
        } 
        
        curPointer = curPointer->next;
    }
    stack1.push (u);
}


int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("hamiltonian.in", "r", stdin);
    freopen("hamiltonian.out", "w", stdout);
    

    int n, m;
    cin >> n >> m;

    Node graphN[n];
    stack <int> stack1; 

    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        graphN[a-1].addNewEdge(b-1);   
    }

    for (int i = 0; i < n; i++) {
        if (graphN[i].color == 0) {
            graphDFS (i, graphN, stack1);
        }
    }
   
    int cur = 0, prev = 0;
    bool isHamiltonian = false;

    if (!stack1.empty()) {
        isHamiltonian = true;
        prev = stack1.top();
        stack1.pop();
    }

    while (!stack1.empty() && isHamiltonian) {

        cur = stack1.top();
        stack1.pop();
        isHamiltonian = false;


        NodeSimple* curPointer = graphN[prev].inzedentWith;
        while (curPointer != nullptr) {
            int v = curPointer->numOfNode; 
            
            if (v == cur){
                isHamiltonian = true;
                break;
            } 
            
            curPointer = curPointer->next;
        }
        prev = cur;


       
    }

    if (isHamiltonian) {
        cout << "YES";
    } else {
        cout << "NO";
    }
   
    return 0;
}