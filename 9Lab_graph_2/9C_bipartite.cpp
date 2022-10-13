#include <iostream>
#include <iomanip>
#include <cmath>
#include <queue>


using namespace std;

struct NodeSimple{
    int numOfNode;
    NodeSimple* next;
}; 

enum color { white, black };

class Node {
public:
    int color;

    NodeSimple* inzedentWith;
    
    int distance;
    //int number;
    //int component;
    //int f;
    //int parent;
    Node* next;
    Node* prev;
    bool alreadyInQueue;
    bool visited;

    Node(){
        color = 0;
        inzedentWith = nullptr;
        alreadyInQueue = false;
        next = nullptr;
        prev = nullptr;
        
        //visited = false;

        //next = nullptr;
        //prev = nullptr;
        //number = 0;
        //component = 0;
        //f = 0; 
        distance = 100001; 
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

void Enqueue (Node* &queueTail, Node* &queueHead, Node* s){
    if (queueHead == nullptr) queueHead = s;
    if (queueTail!= nullptr) queueTail->prev = s;
    s->next = queueTail;
    queueTail = s;
}

Node* Dequeue (Node* &queueTail, Node* &queueHead){
    Node* u = queueHead;
    if (u == queueTail) { queueTail = nullptr;}
    if (u->prev != nullptr){  (u->prev)->next = nullptr; }
    queueHead = u->prev;
    u->prev = nullptr;
    return u;
}


void BFS (Node* arr, const int & n, int & curColorNum, bool & bipartite){
    
    queue <int> queue1;
    arr[1].color = 1;
    arr[1].distance = 0; 
    Node* queueTail = &(arr[1]);
    Node* queueHead = &(arr[1]);
     
    for (int i = 1; i <= n; i++){
        
        if (arr[i].color == 0){
            
            arr[i].distance = 0;
            int curDistance = 0;
            queue1.push(i);
            
            
            while (/*!queue1.empty()*/queueHead != nullptr){
                Node* u = Dequeue(queueTail, queueHead);
                NodeSimple* curPointer = u->inzedentWith;
                //r = queue1.front();                
                //arr[r].color = 1;

                //NodeSimple* curPointer = arr[r].inzedentWith;
                while (/*curPointer != nullptr*/ arr[curPointer->numOfNode].color == 0){
                    int v = curPointer->numOfNode;
                    /*if (arr[v].color == 0) {
                        arr[v].distance = arr[r].distance+1;
                        arr[r].color = 1;
                        queue1.push(v);
                        
                    } */
                    if (arr[curPointer->numOfNode].color == 0) {
                        arr[curPointer->numOfNode].color = 1;
                        arr[curPointer->numOfNode].distance = u->distance+1;
                        Enqueue(queueTail, queueHead, &arr[curPointer->numOfNode]);
                    }
                    else if (abs(arr[v].distance - u->distance) % 2 == 0) {
                    //else if (abs(arr[v].distance - arr[r].distance) % 2 == 0) {
                        bipartite = false;
                        return;
                    }
                    curPointer = curPointer->next;
                }
                //queue1.pop();
                u->color = 2;
                
            }
            //arr[r].color = 1;
            
            
        }
    }
}



int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("bipartite.in", "r", stdin);
    //freopen("bipartite.out", "w", stdout);
   
    int n, m; //вершин и ребер
    cin>>n>>m;
    
    bool noCycle = true;
    Node* arr = new Node[n+1];
    
    for (int i = 0; i<m; i++){
        int a,b;
        cin>>a>>b;
        arr[a].addNewEdge(b);
        arr[b].addNewEdge(a);
    }
    int curColorNum = 1; 
    bool bipartite = true;
    int r;
    
    BFS(arr, n, curColorNum, bipartite);
    
    if (bipartite) {
        cout<<"YES"<<endl;
    } else {
        cout<<"NO"<<endl;
    }
    
    

    return 0;
}
