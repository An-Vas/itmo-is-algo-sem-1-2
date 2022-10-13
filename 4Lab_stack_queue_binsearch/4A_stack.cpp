#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <cstdlib>


using namespace std;

struct Node {
  int val;
  //Node* next;
  Node* prev;
};



int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

   freopen("stack.in", "r", stdin);
   freopen("stack.out", "w", stdout);

   int n, a;
   char ch;
   Node* lastPointer = new Node;

   cin>>n;
   for (int i = 0; i < n; i++){
        cin >> ch;
        if (ch == '+'){
            cin>>a;
            Node* pointerA = new Node;

            pointerA->val = a;
            pointerA->prev = lastPointer;
            lastPointer = pointerA;

        } else if (ch == '-'){
             cout<<lastPointer->val<<endl;
             lastPointer = lastPointer->prev;


        }
   }

   return 0;

}
