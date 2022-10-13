#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

struct NodeSimple{
    int numOfNode;
    NodeSimple* next;
};

struct Node {
    int color;
    int distance;
    int number;
    Node* parent;
    NodeSimple* inzedentWith;
    Node* next;
    Node* prev;
    bool wall;
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

void showAllEdges(int edge, Node arr[]){
    NodeSimple* curPointer = arr[edge].inzedentWith;
    while (curPointer!= nullptr){
        cout<<curPointer->numOfNode<<" ";
        curPointer = curPointer->next;
    }
    cout<<endl;
}

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
   
    
    int n, m; // n - "|"; m - "-";
    cin>>n>>m; 
    if (n==0||m==0||n+m<3){
        cout<<"-1";
        return 0;
    }

    int Tpoint, Spoint;

    Node arr[m*n+1];
    for (int i = 1; i<=n*m; i++){
        arr[i].color = 0; //0 - white, 1 - grey, 2 - black
        arr[i].distance = -1;
        arr[i].parent = nullptr;
        arr[i].inzedentWith = nullptr;
        arr[i].next = nullptr;
        arr[i].prev = nullptr;
        arr[i].number = i;
        char ch;
        cin>>ch;
        if ((ch == '.')||(ch=='S')||(ch=='T')) {
            arr[i].wall = false;
        } else if (ch == '#') {
            arr[i].wall = true;
        }

        if (ch=='S') Spoint = i;
        if (ch=='T') Tpoint = i;
        
    }

    

    for (int i = 1; i<=m*n; i++){
        //right neighbough
        if ( (i+1<=m*n) && ( (i % m) != 0) && (arr[i+1].wall == false) && (arr[i].wall == false)) {
            addNewEdge(i, i+1, arr);
            addNewEdge(i+1, i, arr);
        }
        //lower neighbow
        if ((i + m <= n*m) && (arr[i+m].wall == false) && (arr[i].wall == false)){
            addNewEdge(i, i+m, arr);
            addNewEdge(i+m, i, arr);
        }
        
    }

    //start - Spoint Node
    arr[Spoint].color = 1;
    arr[Spoint].distance = 0; 
    Node* queueTail = &(arr[Spoint]);
    Node* queueHead = &(arr[Spoint]);
    

    while (queueHead != nullptr){
        Node* u = Dequeue(queueTail, queueHead);
        NodeSimple* curPointer = u->inzedentWith;
        
        while (curPointer != nullptr){

            if (arr[curPointer->numOfNode].color == 0) {
                arr[curPointer->numOfNode].color = 1;
                arr[curPointer->numOfNode].distance = u->distance+1;
                arr[curPointer->numOfNode].parent = u;
                Enqueue(queueTail, queueHead, &arr[curPointer->numOfNode]);
            }

            curPointer = curPointer->next;
        }
        u->color = 2;
    }

    
    cout<<arr[Tpoint].distance<<" "<<endl; 
    

    Node* curPointer = &(arr[Tpoint]); 
    int movements[arr[Tpoint].distance + 1];
    movements[0] = Tpoint;
    movements[arr[Tpoint].distance] = Spoint;

    
    
    for (int i = 1; i < arr[Tpoint].distance; i++){
        curPointer = curPointer->parent;
        movements[i] = curPointer->number;
    }

    
    for (int i = arr[Tpoint].distance; i > 0; i--){

        //going LEFT example 10->9
        if  (((movements[i])%m != 1)&&(movements[i] == movements[i-1]+1)){
            cout<<"L";
        }
        //going RIGHT example 3->4
        if (((movements[i])%m != 0)&&(movements[i]+1 == movements[i-1])){
            cout<<"R";
        }

        //goint DOWN example 4->8
        if ((movements[i] + m <= m*n)&&(movements[i] == movements[i-1]-m)){
            cout<<"D";
        }
        //going UP example 8->4
        if ((movements[i] - m >= 0)&&(movements[i] == movements[i-1]+m)){
            cout<<"U";
        }
    }
    

    return 0;
}
