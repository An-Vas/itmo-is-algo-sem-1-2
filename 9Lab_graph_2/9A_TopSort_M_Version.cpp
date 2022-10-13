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
    int distance;
    //int number;
    int component;
    int f;
    int parent;
    NodeSimple* inzedentWith;
    Node* next;
    Node* prev;
    bool alreadyInQueue;

    Node(){
        color = 0;
        distance = 100001; 
        parent = 0;
        inzedentWith = nullptr;
        next = nullptr;
        prev = nullptr;
        //number = 0;
        component = 0;
        f = 0;
        alreadyInQueue = false;
    }

    void addNewEdge (int edgeStart, int edgeEnd){

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

void DFS_visit(Node arr[],const int & n, const int & u, int & time, stack <int> & answerList, bool & noTopSort){
    //cout<<"DFS-visit "<<u<<" start"<<endl;
    time++;
    arr[u].distance = time;
    arr[u].color = 1;
    NodeSimple* curPointer = arr[u].inzedentWith;
    while (curPointer != nullptr) {
        int v = curPointer->numOfNode;        
        if (arr[v].color == 0){
            arr[v].parent = u;
            DFS_visit(arr, n, v, time, answerList, noTopSort);
        }
        if (arr[v].color == 1) {
            noTopSort = true;
            break;
        }
        curPointer = curPointer->next;
    }
    //cout<<"DFS v "<<u<<" finish"<<endl;
    if (!arr[u].alreadyInQueue) { answerList.push(u);

    int r = answerList.top();
    //cout<<"Queue top = "<<r<<endl;
    arr[u].alreadyInQueue = true;
    }

    arr[u].color = 2;
    time++;
    arr[u].f = time;
    
}

void DFS(Node arr[], const int & n, const int & u, stack <int> & answerList, bool & noTopSort){
    //cout<<"DFS "<<u<<endl;
    for (int i = 1; i < n+1; i++){
        arr[i].color = 0;
        arr[i].parent = 0;
    }
    int time = 0;
    //for (int i = 1; i < n+1; i++){
        if (arr[u].color == 0){
            DFS_visit(arr, n, u, time, answerList, noTopSort);
        }
    //}

}

void Top_sort (Node arr[], const int & n, stack <int> & answerList, bool & noTopSort){
    for (int i = 1; i <= n; i++){
        if (noTopSort) break;
        if (arr[i].color == 0) DFS(arr, n, i, answerList, noTopSort);
        //answerList.push(i);
    }

}

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


int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("topsort.in", "r", stdin);
    freopen("topsort.out", "w", stdout);
   
    int n, m; //вершин и ребер
    cin>>n>>m;
    
    bool noTopSort = false;

    Node arr[n+1];
    for (int i = 1; i<=n; i++){
        //arr[i].number = i;
    }

    for (int i = 0; i<m; i++){
        int a,b;
        cin>>a>>b;
        addNewEdge(a, b, arr);
    }

    stack <int> answerList;
    //DFS(arr, n, 1, answerList);
    //cout<<arr[1].distance<<" "<<arr[1].f<<endl;

    
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
