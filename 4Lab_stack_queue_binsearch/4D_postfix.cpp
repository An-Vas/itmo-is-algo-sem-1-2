#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <cstdlib>


using namespace std;

struct Node {
  long  long val;
  //Node* next;
  Node* prev;
};


int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    freopen("postfix.in", "r", stdin);
    freopen("postfix.out", "w", stdout);

    char newChar;
    Node* lastPointer = new Node;

    while (cin>>newChar){
        if (newChar == '+'){
            lastPointer->val = lastPointer->prev->val + lastPointer->val;
            lastPointer->prev = lastPointer->prev->prev;
        } else if (newChar == '-'){
            lastPointer->val = lastPointer->prev->val - lastPointer->val;
            lastPointer->prev = lastPointer->prev->prev;
        } else if (newChar == '*'){
            lastPointer->val = lastPointer->prev->val * lastPointer->val;
            lastPointer->prev = lastPointer->prev->prev;
        } else {
            //значит, новый символ это число
            Node* pointerA = new Node;
            pointerA->val = (long long) newChar - 48;

            pointerA->prev = lastPointer;
            lastPointer = pointerA;

        }



    }
    cout<<lastPointer->val;




   return 0;

}
