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


struct InHtArray {
    int CNToAdd; //curNumToAdd;
    string key;
    string htValues[100];
   // string htKeys[100];
    bool htFlags [100];
    int addarr; //additional arrays
    InHtArray* nextP;
};


struct NodeQueueForPrint {
    string value;
    NodeQueueForPrint* next;

};
InHtArray* createNewArr(){
    InHtArray* newInHTArray = new InHtArray;
    newInHTArray->key = "";
    newInHTArray->CNToAdd = 0;
    newInHTArray->addarr = 0;
    newInHTArray->nextP = NULL;
    for (int i = 0; i < 100; i ++){
        newInHTArray->htValues[i] = "";
        newInHTArray->htFlags[i] = false;
    }
}
void putX (int keyHash, string key, string value, vector <InHtArray*>& hashTable){
    if (hashTable[keyHash] == NULL){
        InHtArray* newInHTArray = createNewArr();
        newInHTArray->htValues[0] = value;
        newInHTArray->key = key;
        newInHTArray->htFlags[0] = false;
    }
    else {
        InHtArray* curPointer = hashTable[keyHash];
        InHtArray* lastPointer = curPointer;
        while (curPointer->nextP != 0){
            if (curPointer->key == key){

                break;
            }
            lastPointer = curPointer;
            curPointer = curPointer->nextP;
        }
        if (curPointer->key == key){
            curPointer->htValues[curPointer->CNToAdd] = value;
            curPointer->htFlags[curPointer->CNToAdd] = false;
            curPointer->CNToAdd++;
            return;
        }
        //оставшийся вариант просто создаать новую структуру под новый ключ
        if (1){
            InHtArray* newInHTArray = createNewArr();
            newInHTArray->htValues[0] = value;
            newInHTArray->key = key;
            newInHTArray->htFlags[0] = false;
            curPointer->nextP = newInHTArray;
        }



    }

}

void deleteX (int keyHash, string key, string value, vector <InHtArray*>& hashTable){
    /*Node* curPointer = hashTable[keyHash];
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
    }*/
}


void deleteAllX (int keyHash, string key, vector <InHtArray*>& hashTable){
   /* Node* curPointer = hashTable[keyHash];
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

    }*/

}


void getXpart1 (int keyHash, string searchKey, vector <InHtArray*>& hashTable, int &counter){

/*
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
    if (counter>0) cout<<" ";


    NodeQueueForPrint* curPointerQueue = head;
    while (curPointerQueue -> next != 0){
        curPointerQueue = curPointerQueue -> next;
        cout<<curPointerQueue->value;
        //counter--;
        if (counter>0){cout<<" ";}
    }
    cout<<endl;
*/

}




int HashFunction(string str){

    int testint = 0;
    for (int i = 0; i < str.size(); i++){
       testint +=  str[i] - 65 + str.size()*str.size()*(str[i] - 13);
       testint += testint*str[i]*13*11 - str.size();
       testint = testint % 1000000;

    }

    return abs(testint);
    //return 7;
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
    //int a = HashFunction("aaZiop2");
    //cout<<a;

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    //freopen("multimap.in", "r", stdin);
    //freopen("multimap.out", "w", stdout);

    string curCommand;

    vector <InHtArray*> hashTable (1000000);

    for (int i = 0; i < 1000000; i++){
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
            putX (keyHash, key, value, hashTable);
        }

        else if (curCommand[0] == 'd' && curCommand.size()<8) {
            cin>>value;
            //deleteX (keyHash, key, value, hashTable);
        }

        else if (curCommand[0] == 'd') {
            //deleteAllX (keyHash, key, hashTable);
        }

        else if (curCommand[0] == 'g') {
           // getXpart1 (keyHash, key, hashTable, counter);

        }



        //show (keyHash, key, hashTable);
    }




    return 0;
}
