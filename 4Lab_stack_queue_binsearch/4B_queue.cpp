#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <cstdlib>


using namespace std;

struct Node {
  int val;
  Node* next;
  Node* prev;
};



int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

   freopen("queue.in", "r", stdin);
   freopen("queue.out", "w", stdout);

   int n, a;
   char ch;
   Node* lastPointer = new Node;
   lastPointer->next = NULL;
   Node* nowShowPointer = lastPointer;

   cin>>n;
   for (int i = 0; i < n; i++){
        cin >> ch;
        if (ch == '+'){
            cin>>a;
            Node* pointerA = new Node;

            lastPointer->next = pointerA;
            pointerA->val = a;
            pointerA->prev = lastPointer;
            pointerA->next = NULL;
            lastPointer = pointerA;

        } else if (ch == '-'){

             cout<<nowShowPointer->next->val<<endl;
             nowShowPointer = nowShowPointer->next;



        }
   }

   return 0;

}
