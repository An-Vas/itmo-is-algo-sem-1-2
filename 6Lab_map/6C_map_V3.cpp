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

struct Node {
    string key;
    string value;
    Node* next;
    Node* nextInsertedNode;
    Node* prevInsertedNode;
};

void putX (int keyHash, string key, string value, vector <Node*> &hashTable, Node* &lastPointer){

    Node* newNodePointer = new Node;
    newNodePointer->key = key;
    newNodePointer->value = value;
    newNodePointer->next = NULL;
    newNodePointer->nextInsertedNode = NULL;
    newNodePointer->prevInsertedNode = lastPointer;
    //if (lastPointer!= 0 )cout<<"lastPointer is "<<lastPointer->value<<endl;
    //else cout<<"lastPointer is 0"<<endl;



    Node* curPointer = hashTable[keyHash];
    if (curPointer == NULL){
        hashTable[keyHash] = newNodePointer;
    } else {
        while (curPointer->next != NULL) {
            //if (curPointer->key == key){return;}
            if (curPointer->key == key){
                curPointer->value = value;
                return;
            }
            curPointer = curPointer->next;
        }
        if (curPointer->key == key){
            curPointer->value = value;
            return;
        }
        curPointer->next = newNodePointer;
    }
    if (lastPointer != 0){
        lastPointer->nextInsertedNode = newNodePointer;
    }
    lastPointer = newNodePointer;
}

void deleteX (int keyHash, string key, vector <Node*> &hashTable, Node* &lastPointerFromMain){
    Node* curPointer = hashTable[keyHash];
    Node* lastPointer = hashTable[keyHash];
    if (curPointer == NULL){return;}
    if (curPointer->next == NULL){
        if (curPointer->key == key){
            if (curPointer == lastPointerFromMain) lastPointerFromMain = lastPointerFromMain->prevInsertedNode;
            if (curPointer->prevInsertedNode != 0)
                curPointer->prevInsertedNode->nextInsertedNode = curPointer->nextInsertedNode;
            if (curPointer->nextInsertedNode!= 0)
                curPointer->nextInsertedNode->prevInsertedNode = curPointer->prevInsertedNode;
            hashTable[keyHash] = NULL;
        }

        return;
    }

    while (curPointer->next != NULL && curPointer->key != key) {
        lastPointer = curPointer;
        curPointer = curPointer->next;
    }
    if (curPointer->key == key){
        if (curPointer == lastPointerFromMain) lastPointerFromMain = lastPointerFromMain->prevInsertedNode;

        if (curPointer->prevInsertedNode!= 0)
            curPointer->prevInsertedNode->nextInsertedNode = curPointer->nextInsertedNode;
        if (curPointer->nextInsertedNode!= 0)
            curPointer->nextInsertedNode->prevInsertedNode = curPointer->prevInsertedNode;

        lastPointer->next = curPointer->next;

        if (curPointer == hashTable[keyHash]) {
            hashTable[keyHash] = curPointer->next;
        }

        return;
    }
}

void getX (int keyHash, string searchKey, vector <Node*>& hashTable){
    bool searchResult = false;
    Node* curPointer = hashTable[keyHash];
    while (curPointer != 0){
        if (curPointer->key == searchKey) {
           searchResult = true;
           break;
        }
        curPointer = curPointer->next;
    }
    if (searchResult == true){
        cout<<curPointer->value<<endl;
    } else {
        cout<<"none"<<endl;
    }
}

void prevX(int keyHash, string searchKey, vector <Node*>& hashTable){
    bool searchResult = false;
    Node* curPointer = hashTable[keyHash];
    while (curPointer != 0){
        if (curPointer->key == searchKey) {
           searchResult = true;
           break;
        }
        curPointer = curPointer->next;
    }
    if (searchResult == true && curPointer->prevInsertedNode!=0){
        cout<<curPointer->prevInsertedNode->value<<endl;
    } else {
        cout<<"none"<<endl;
    }
}

void nextX(int keyHash, string searchKey, vector <Node*>& hashTable){
    bool searchResult = false;
    Node* curPointer = hashTable[keyHash];
    while (curPointer != 0){
        if (curPointer->key == searchKey) {
           searchResult = true;
           break;
        }
        curPointer = curPointer->next;
    }
    if (searchResult == true && curPointer->nextInsertedNode!=0){
        cout<<curPointer->nextInsertedNode->value<<endl;
    } else {
        cout<<"none"<<endl;
    }
}


int HashFunction(string str){

    int testint = 0;
    for (int i = 0; i < str.size(); i++){
       testint +=  (str[i] - 63); //63 - random number less then 65
       testint*= 7;
       testint = testint % 5000;

    }

    return testint;
    return 7;
}

void show (int keyHash, string searchKey, vector <Node*>& hashTable) {
    Node* curPointer = hashTable[keyHash];
    if (curPointer == 0){cout<<"nothing"<<endl;}
    while (curPointer!=0){
        cout<<curPointer -> key<<" "<<curPointer->value<<" ";
        curPointer = curPointer-> next;
    }
    cout<<endl;
}

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    freopen("linkedmap.in", "r", stdin);
    freopen("linkedmap.out", "w", stdout);

    string curCommand;

    vector <Node*> hashTable (5000);

    for (int i = 0; i < 5000; i++){
        hashTable[i] = NULL;
    }

    Node* lastPointer = 0;

    while (cin >> curCommand){
        string key;
        cin>>key;
        string value;
        int keyHash = HashFunction(key);


        if (curCommand[0] == 'p'&&curCommand[1] == 'u') {
            cin>>value;
            putX (keyHash, key, value, hashTable, lastPointer);
        }

        if (curCommand[0] == 'd') {
            deleteX (keyHash, key, hashTable, lastPointer);
        }

        if (curCommand[0] == 'g') {
            getX (keyHash, key, hashTable);
        }

        if (curCommand[0] == 'p'&&curCommand[1] == 'r') {
            prevX (keyHash, key, hashTable);
        }


        if (curCommand[0] == 'n') {
            nextX (keyHash, key, hashTable);
        }

        //show (keyHash, key, hashTable);
    }




    return 0;
}
