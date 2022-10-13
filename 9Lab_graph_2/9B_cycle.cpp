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


void DFS_Cycle_OutPut (Node* arr, const int & n, const int & u, bool & noCycle, stack <int>& stack1) {
    
    if (!noCycle) return;
   
    if (!arr[u].alreadyInQueue) {
        stack1.push(u); 
        arr[u].alreadyInQueue = true; 
    }

    arr[u].visited = true;
    arr[u].color = 1; 

    NodeSimple* curPointer = arr[u].inzedentWith;
    while (curPointer != nullptr) {
       
        if (!noCycle) return;
        int v = curPointer->numOfNode; 
         
        if (!arr[v].visited){
            DFS_Cycle_OutPut (arr, n, v, noCycle, stack1);
            if (!noCycle) return;   
        } 

        
        if (arr[v].color == 1) {
            noCycle = false;
            cout<<"YES"<<endl;
            stack <int> stack2_ans;
            while (!stack1.empty()){ 
                int r = stack1.top();  
                stack2_ans.push(r);
                stack1.pop();
                if (r == v) break;
            }
            while (!stack2_ans.empty()){
                int r = stack2_ans.top();  
                cout<<r<<" ";
                stack2_ans.pop();
            }
            return;
            
        }
        
        curPointer = curPointer->next;
    }
    arr[u].color = 2;
    if (!stack1.empty()) stack1.pop();
    
}

void DFS_Cycle_Search (Node* arr, const int & n,  bool & noCycle){
    
    for (int i = 1; i <= n; i++){
        if (!noCycle) return;
        
        if (!arr[i].visited){
            stack <int> stack1;
            DFS_Cycle_OutPut(arr, n, i, noCycle, stack1); 
            for (int i = 1; i <= n; i++) arr[i].color = 0;
         }
    }

    

}



int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    //freopen("cycle.in", "r", stdin);
    //freopen("cycle.out", "w", stdout);
   
    int n, m; //вершин и ребер
    cin>>n>>m;
    
    bool noCycle = true;
    Node* arr = new Node[n+1];
    
    for (int i = 0; i<m; i++){
        int a,b;
        cin>>a>>b;
        arr[a].addNewEdge(b);
    }

    
    DFS_Cycle_Search(arr, n, noCycle);
    
    if (noCycle) {
        cout<<"NO"<<endl;
    } 
    
    

    return 0;
}
