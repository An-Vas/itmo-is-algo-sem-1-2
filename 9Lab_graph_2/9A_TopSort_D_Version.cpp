#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>

using namespace std;

struct NodeSimple{
    int numOfNode;
    NodeSimple* next;
}; 

class Node {
public:
    int color;
    NodeSimple* inzedentWith;
    //int distance;
    //int number;
    //int component;
    //int f;
    //int parent;
    //Node* next;
    //Node* prev;
    bool alreadyInQueue;
    bool visited;

    Node(){
        color = 0;
        inzedentWith = nullptr;
        alreadyInQueue = false;
        visited = false;

        //next = nullptr;
        //prev = nullptr;
        //number = 0;
        //component = 0;
        //f = 0; distance = 100001; 
        //parent = 0;
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


void DFS (Node arr[], const int & n, const int & u, stack <int> & answerList, bool & noTopSort) {
    
    arr[u].visited = true;
    arr[u].color = 1; 

    NodeSimple* curPointer = arr[u].inzedentWith;
    while (curPointer != nullptr) {
        int v = curPointer->numOfNode; 
         
        if (!arr[v].visited){
             DFS(arr, n, v, answerList, noTopSort);   
        } 
        if (arr[v].color == 1) {
            noTopSort = true;
            break;
        }
        curPointer = curPointer->next;
    }
    if (!arr[u].alreadyInQueue) { answerList.push(u); arr[u].alreadyInQueue = true; }
    arr[u].color = 2;

    

}

void Top_sort (Node arr[], const int & n, stack <int> & answerList, bool & noTopSort){
    for (int i = 1; i <= n; i++){
        if (noTopSort) break;
        arr[i].color = 0;
        arr[i].visited = false;
        if (!arr[i].visited) DFS(arr, n, i, answerList, noTopSort);
    }

}



int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    //freopen("topsort.in", "r", stdin);
    //freopen("topsort.out", "w", stdout);
   
    int n, m; //вершин и ребер
    cin>>n>>m;
    
    bool noTopSort = false;

    Node arr[n+1];
    
    for (int i = 0; i<m; i++){
        int a,b;
        cin>>a>>b;
        arr[a].addNewEdge(b);
    }

    stack <int> answerList;
    
    
    Top_sort(arr, n, answerList, noTopSort);

    if (noTopSort) {
        cout<<-1;
        return 0;
    } else {
        for (int i = 1; i <= n; i++){
        int r = answerList.top();
        cout<<r<<" ";
        answerList.pop();
    }
    }
    
    
   
    return 0;
}
