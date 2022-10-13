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
    long long key;
    Node* next;
};

void insertX (int keyHash, long long key, vector <Node*>& hashTable){

    Node* newNodePointer = new Node;
    newNodePointer->key = key;
    newNodePointer->next = NULL;

    Node* curPointer = hashTable[keyHash];
    if (curPointer == NULL){
        hashTable[keyHash] = newNodePointer;
    } else {
        while (curPointer->next != NULL) {
            if (curPointer->key == key){return;}
            curPointer = curPointer->next;
        }
        if (curPointer->key == key){return;}
        curPointer->next = newNodePointer;
    }
}

void deleteX (int keyHash, long long key, vector <Node*>& hashTable){
    Node* curPointer = hashTable[keyHash];
    Node* lastPointer = hashTable[keyHash];
    if (curPointer == NULL){return;}
    if (curPointer->next == NULL){
        if (curPointer->key == key){
            hashTable[keyHash] = NULL;
        }
        return;
    }
    //cout<<curPointer->key<<endl;
    while (curPointer->next != NULL && curPointer->key != key) {
        lastPointer = curPointer;
        curPointer = curPointer->next;
    }
    if (curPointer->key == key){
        //cout<<"Before L "<<lastPointer<<endl;
        //cout<<"Before C "<<curPointer->next<<endl;
        lastPointer->next = curPointer->next;
        if (curPointer == hashTable[keyHash]) {
            hashTable[keyHash] = curPointer->next;
        }
        //cout<<"After "<<lastPointer->next<<endl;
        return;
    }
}

void existX (int keyHash, long long searchKey, vector <Node*>& hashTable){
    bool result = false;
    Node* curPointer = hashTable[keyHash];
    while (curPointer != 0){
        if (curPointer->key == searchKey) {
           result = true;
           break;
        }
        curPointer = curPointer->next;
    }
    if (result == true){
        cout<<"true"<<endl;
    } else {
        cout<<"false"<<endl;
    }
}

int HashFunction(string str x){

    int testint = 0;
    for (int i = 0; i < str.size(); i++){
       testint +=  (str[i] - 63); //63 - random number less then 65
       testint*= 7;
       testint = testint % 5000;

    }

    return abs(x%5003);

}

void show (int keyHash, long long searchKey, vector <Node*>& hashTable) {
    Node* curPointer = hashTable[keyHash];
    if (curPointer == 0){cout<<"nothing"<<endl;}
    while (curPointer!=0){
        cout<<curPointer -> key<<" ";
        curPointer = curPointer-> next;
    }
    cout<<endl;
}

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    //freopen("map.in", "r", stdin);
    //freopen("map.out", "w", stdout);




    cout<<testint;

    string curCommand;
    while (cin >> curCommand){
        long long key;
        //cin>>key;
        int keyHash = HashFunction(key);


        if (curCommand[0] == 'i') {
            //insertX (keyHash, key, hashTable);
        }

        if (curCommand[0] == 'd') {
           // deleteX (keyHash, key, hashTable);
        }

        if (curCommand[0] == 'e') {
            //existX (keyHash, key, hashTable);
        }


        if (curCommand[0] == 'f') {
           // break;
        }
        //show (keyHash, key, hashTable);
    }




    return 0;
}
