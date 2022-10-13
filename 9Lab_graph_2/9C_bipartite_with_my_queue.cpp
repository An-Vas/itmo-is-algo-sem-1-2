#include <iostream>
#include <iomanip>

using namespace std;

struct NodeSimple{
    int numOfNode;
    NodeSimple* next;
};

struct Node {
    int color;
    int distance;
    int number;
    //Node* parent;
    NodeSimple* inzedentWith;
    Node* next;
    Node* prev;
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

void DFS_ifBipartite(Node arr[], const int & n, bool & bipartite){
    for(int i = 1; i <= n; i++){
        if (arr[i].color == 0){
            arr[i].color = 1;
            arr[i].distance = 0; 
            Node* queueTail = &(arr[i]);
            Node* queueHead = &(arr[i]);
            

            while (queueHead != nullptr){
                Node* u = Dequeue(queueTail, queueHead);
                NodeSimple* curPointer = u->inzedentWith;
                
                while (curPointer != nullptr){

                    if (arr[curPointer->numOfNode].color == 0) {
                        arr[curPointer->numOfNode].color = 1;
                        arr[curPointer->numOfNode].distance = u->distance+1;
                        Enqueue(queueTail, queueHead, &arr[curPointer->numOfNode]);
                    }
                    else if (abs(arr[curPointer->numOfNode].distance - u->distance) % 2 == 0) {
                        bipartite = false;
                        return;
                    }

                    curPointer = curPointer->next;
                }
                u->color = 2;
            }

        }
       
    }
}

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("bipartite.in", "r", stdin);
    freopen("bipartite.out", "w", stdout);
   
    
    int n, m; // n - count of vertexes; m - count of Edges of Graph;
    cin>>n>>m;

    Node arr[n+1];
    for (int i = 1; i<=n; i++){
        arr[i].color = 0; //0 - white, 1 - grey, 2 - black
        arr[i].distance = 30001; //так как  вершин не больше 30 000, то и такого расстояния быть не может
        //arr[i].parent = nullptr;
        arr[i].inzedentWith = nullptr;
        arr[i].next = nullptr;
        arr[i].prev = nullptr;
        arr[i].number = i;
    }

    

    for (int i = 0; i<m; i++){
        int a,b;
        cin>>a>>b;
        addNewEdge(a, b, arr);
        addNewEdge(b, a, arr);
    }

    bool bipartite = true;

    DFS_ifBipartite(arr, n, bipartite);

    
   
    if (bipartite) {
        cout<<"YES"<<endl;
    } else {
        cout<<"NO"<<endl;
    }
    
   
   
    return 0;
}
