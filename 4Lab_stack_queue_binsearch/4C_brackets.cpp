#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <cstdlib>


using namespace std;

struct Node {
  char val;
  //Node* next;
  Node* prev;
};

bool isPair(char ch1, char ch2){
    if (ch1 == '(' && ch2 == ')') { return true;}
    else if (ch1 == '[' && ch2 == ']') { return true;}
    else  {return false;}
}

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    freopen("brackets.in", "r", stdin);
    freopen("brackets.out", "w", stdout);

    int n, a;
    string line;
    char newChar;
    bool finishAll = false;

    while (cin>>line){
        int counter = 0;
        Node* Head = new Node;
        Node* lastPointer = Head;

        for (int i = 0; i < line.length(); i++){
            newChar = line[i];
            if (isPair(lastPointer->val,newChar)) {
                lastPointer = lastPointer->prev;
                counter--;
                //delete last bracket
            } else /*if (newChar == '(' || newChar == '[')*/{
                //add bracket
                Node* pointerA = new Node;
                pointerA->val = newChar;
                pointerA->prev = lastPointer;
                lastPointer = pointerA;
                counter++;
            }

        }
        if (counter == 0) {cout<<"YES"<<endl;}
        else { cout<<"NO"<<endl;}
    }





   return 0;

}
