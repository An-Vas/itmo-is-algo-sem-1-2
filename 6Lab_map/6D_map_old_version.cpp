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

};


struct NodeQueueForPrint {
    string value;
    NodeQueueForPrint* next;

};

void putX (int keyHash, string key, string value, vector <Node*>& hashTable, Node* &lastPointer){

    Node* newNodePointer = new Node;
    newNodePointer->key = key;
    newNodePointer->value = value;
    newNodePointer->next = NULL;



    Node* curPointer = hashTable[keyHash];
    if (curPointer == NULL){
        hashTable[keyHash] = newNodePointer;
    } else {
        while (curPointer->next != NULL) {
            //if (curPointer->key == key){return;}
            if (curPointer->key == key && curPointer->value == value){
                return;
            }
            curPointer = curPointer->next;
        }
        if (curPointer->key == key && curPointer->value == value){
            return;
        }
        curPointer->next = newNodePointer;
    }

}

void deleteX (int keyHash, string key, string value, vector <Node*>& hashTable){
    Node* curPointer = hashTable[keyHash];
    Node* lastPointer = hashTable[keyHash];
    if (curPointer == NULL){return;}
    if (curPointer->next == NULL){
        if (curPointer->key == key && curPointer->value == value){
            hashTable[keyHash] = NULL;
        }
        return;
    }
    while (curPointer->next != NULL && !(curPointer->key == key && curPointer->value == value)) {
        lastPointer = curPointer;
        curPointer = curPointer->next;
    }
    if (curPointer->key == key && curPointer->value == value){

        lastPointer->next = curPointer->next;

        if (curPointer == hashTable[keyHash]) {
            hashTable[keyHash] = curPointer->next;
        }

        return;
    }
}


void deleteAllX (int keyHash, string key, vector <Node*>& hashTable){
    Node* curPointer = hashTable[keyHash];
    Node* lastPointer = hashTable[keyHash];
    if (curPointer == NULL){return;}
    if (curPointer->next == NULL){
        if (curPointer->key == key){
            hashTable[keyHash] = NULL;
        }
        return;
    }

    if (curPointer->key == key){

            lastPointer->next = curPointer->next;

            if (curPointer == hashTable[keyHash]) {
                hashTable[keyHash] = curPointer->next;
            }

    }

    while (curPointer->next != NULL) {
        lastPointer = curPointer;
        curPointer = curPointer->next;

        if (curPointer->key == key){

            lastPointer->next = curPointer->next;

            if (curPointer == hashTable[keyHash]) {
                hashTable[keyHash] = curPointer->next;
            }

        }

    }

}


void getXpart1 (int keyHash, string searchKey, vector <Node*>& hashTable, int &counter){


    NodeQueueForPrint* head = new NodeQueueForPrint;
    NodeQueueForPrint* lastPonterQueue = head;
    head->next = NULL;
   // int counter;
    Node* curPointer = hashTable[keyHash];
    while (curPointer != 0){
        if (curPointer->key == searchKey) {
           counter++;
            NodeQueueForPrint* newNodeForPrint = new NodeQueueForPrint;
            newNodeForPrint->value = curPointer->value;
            newNodeForPrint->next = NULL;
            lastPonterQueue->next = newNodeForPrint;
            lastPonterQueue = newNodeForPrint;
        }
        curPointer = curPointer->next;
    }
    cout<<counter;
    //printf("%d", counter);
    if (counter>0) printf(" ");//cout<<" ";




   /* Node* curPointer1 = hashTable[keyHash];
    while (curPointer1 != 0){
        if (curPointer1->key == searchKey&&counter!=0) {
           cout<<curPointer1->value;
           counter--;
           if (counter>0){cout<<" ";}
        }
        curPointer1 = curPointer1->next;
    }
    cout<<endl;*/


    NodeQueueForPrint* curPointerQueue = head;
    while (curPointerQueue -> next != 0){
        curPointerQueue = curPointerQueue -> next;
        cout<<curPointerQueue->value;
        //printf("%s", curPointerQueue->value);
        if (counter>0){
                cout<<" ";
                //printf(" ");
        }
    }
    //printf("\n");
    cout<<endl;


}

void getXpart2 (int keyHash, string searchKey, vector <Node*>& hashTable, int counter){

    Node* curPointer = hashTable[keyHash];
    while (curPointer != 0){
        if (curPointer->key == searchKey&&counter!=0) {
           cout<<curPointer->value;
           counter--;
           if (counter>0){cout<<" ";}
        }
        curPointer = curPointer->next;
    }
    cout<<endl;

}



int HashFunction(string str){

    int testint = 0;
    for (int i = 0; i < str.size(); i++){
       testint +=  str[i] - 65 + str.size()*(str[i] - 17);
       testint += testint*str[i]*13*11 - str.size();
       testint = testint/7;
       testint = testint % 100000;

    }

    return abs(testint);
    //return 7;
}

void show (int keyHash, string searchKey, vector <Node*>& hashTable) {
    Node* curPointer = hashTable[keyHash];
    if (curPointer == 0){cout<<"nothing"<<endl;}
    while (curPointer!=0){
        //printf("%ll ", )
        cout<<curPointer -> key<<" "<<curPointer->value<<" ";
        curPointer = curPointer-> next;
    }
    cout<<endl;
}

int main ()
{
    //int a = HashFunction("aaZiop2");
    //cout<<a;

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    //freopen("multimap.in", "r", stdin);
    //freopen("multimap.out", "w", stdout);

    string curCommand;

    vector <Node*> hashTable (100000);

    for (int i = 0; i < 100000; i++){
        hashTable[i] = NULL;
    }

    Node* lastPointer = 0;

    while (cin >> curCommand){
        string key;
        //cin>>key;
        scanf("%ll", &key);
        string value;
        int keyHash = HashFunction(key);


        if (curCommand[0] == 'p') {
            //cin>>value;
            scanf("%ll", &value);
            putX (keyHash, key, value, hashTable, lastPointer);
        }

        else if (curCommand[0] == 'd' && curCommand.size()<8) {
            scanf("%ll", &value);
            deleteX (keyHash, key, value, hashTable);
        }

        else if (curCommand[0] == 'd') {
            deleteAllX (keyHash, key, hashTable);
        }

        else if (curCommand[0] == 'g') {
            int counter = 0;
            getXpart1 (keyHash, key, hashTable, counter);
            //getXpart2 (keyHash, key, hashTable, counter);
        }



        //show (keyHash, key, hashTable);
    }




    return 0;
}
