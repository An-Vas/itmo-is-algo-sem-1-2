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
  int left;
  int right;
  int height;

};

int getHeight (Node* arr, int a){
    return a ? arr[a].height : 0;
}

int getBalance (Node* arr, int a){
    return getHeight (arr, arr[a].right) - getHeight (arr, arr[a].left);
}


void makeResultArr(Node* inputArr, Node* outputArr, int inputRoot, int* outputCurIndex){
    (*outputCurIndex)++;
    //printf("Start reNumber, key = %d, inputRoot = %d, outputCurIndex = %d\n", inputArr[inputRoot].key, inputRoot, *outputCurIndex);
    int originalOutputCurIndex = *outputCurIndex;
    outputArr[*outputCurIndex].key = inputArr[inputRoot].key;
    outputArr[*outputCurIndex].height = inputArr[inputRoot].height;

    if (inputArr[inputRoot].left != 0) {
        outputArr[*outputCurIndex].left = (*outputCurIndex) + 1;
        makeResultArr(inputArr, outputArr, inputArr[inputRoot].left, outputCurIndex);
    } else {
        outputArr[*outputCurIndex].left = 0;
    }

    if (inputArr[inputRoot].right != 0) {
        outputArr[originalOutputCurIndex].right = (*outputCurIndex) + 1;
        makeResultArr(inputArr, outputArr, inputArr[inputRoot].right, outputCurIndex);
    } else {
        outputArr[originalOutputCurIndex].right = 0;
    }

}


int writeHeights(Node* arr, int root){

    int leftHeight = 0, rightHeight = 0;

    if (arr[root].left != 0) {
        writeHeights(arr, arr[root].left);
        leftHeight = arr[arr[root].left].height;
    } else {
        leftHeight = 0;
    }

     if (arr[root].right != 0) {
        writeHeights(arr, arr[root].right);
        rightHeight = arr[arr[root].right].height;
    } else {
        rightHeight = 0;
    }


    if (leftHeight > rightHeight) {
        arr[root].height = 1+leftHeight;
        return 1+leftHeight;
    } else {
        arr[root].height = 1+rightHeight;
        return 1+rightHeight;
    }
}

int fixOneHeight (Node* arr, int root){

    int leftHeight = getHeight(arr, arr[root].left);
    int rightHeight = getHeight(arr, arr[root].right);
    //printf("start fix H, root = %d, leftH = %d, rH = %d\n", root, leftHeight, rightHeight);

    if (leftHeight > rightHeight) {
        arr[root].height = 1+leftHeight;
        return 1+leftHeight;
    } else {
        arr[root].height = 1+rightHeight;
        return 1+rightHeight;
    }

}


int rotateLeft(Node* arr, int a){
    //cout<<"start rotate left a "<<a<<endl;
    //cout<<arr[1].right<<endl;

   int b = arr[a].right;
   arr[a].right = arr[b].left;
   arr[b].left = a;


    fixOneHeight(arr, a);
    fixOneHeight(arr, b);
   //writeHeights(arr, a);
   //writeHeights(arr, b);


    return b;
}


int rotateRight(Node* arr, int a){
    //cout<<"start rotate right a "<<a<<endl;
    int b = arr[a].left;
    arr[a].left = arr[b].right;
    arr[b].right = a;

    //writeHeights(arr, a);
    //writeHeights(arr, b);
    fixOneHeight(arr, a);
    fixOneHeight(arr, b);
    return b;
}


int balanceNode (Node* arr, int node){
    //printf("start balanceNode for node %d key %d\n",node, arr[node].key);
    fixOneHeight(arr, node);
    //arr[node].height = writeHeights(arr, node);

    //printf("arr[node].height = %d, ", arr[node].height);
    int curBalance = getBalance(arr, node);


    //printf ("curBalance = %d\n", curBalance);


    int rChild = arr[node].right;
    int lChild = arr[node].left;

    if (curBalance > 1) {
        int rightChildBalance = getBalance(arr, rChild);


        if (rightChildBalance < 0){
            arr[node].right = rotateRight(arr, rChild);
        }
        return rotateLeft(arr, node);

    } else if (curBalance < -1){
        int leftChildBalance = getBalance(arr, lChild);

        if (leftChildBalance > 0){
            arr[node].left = rotateLeft(arr, lChild);
        }
        return rotateRight(arr, node);

    } else

    return node;
}





int insertNode (Node* arr, int root, int numOfNew){
    //printf("insertNode, root = %d, numOfNew = %d\n", root, numOfNew);
    if (root == 0) { /*fixOneHeight(arr, root);*/ return numOfNew;}
    int newKey = arr[numOfNew].key;
    if (arr[root].key > arr[numOfNew].key){
        //printf("LeftCh = %d\n",arr[root].left);
        arr[root].left = insertNode (arr, arr[root].left, numOfNew);
    } else {
        //printf("rightCh = %d\n",arr[root].right);
        arr[root].right = insertNode (arr, arr[root].right, numOfNew);
    }
    //printf("Inserted root = %d\n", root);
    return balanceNode(arr, root);
}

int findRightestNode (Node* arr, int root){
    if (arr[root].right!=0){
        return findRightestNode(arr, arr[root].right);
    } else {
        return root;
    }
}

int deleteNode (Node* arr, int root, int keyToDel){
    //printf("deleting from root = %d, keytodel = %d\n", root, keyToDel);
    if (root == 0){
        return 0;
    } else if (keyToDel < arr[root].key) {
        arr[root].left = deleteNode(arr, arr[root].left, keyToDel);
    } else if (keyToDel > arr[root].key) {
        arr[root].right = deleteNode(arr, arr[root].right, keyToDel);
    } else if ( arr[root].left==0) {
        return arr[root].right;
    } else {
        int prevNode = findRightestNode(arr, arr[root].left);
        arr[root].key = arr[prevNode].key;
        arr[root].left = deleteNode (arr, arr[root].left, arr[prevNode].key);
    }
    fixOneHeight(arr, root);
    return balanceNode(arr, root);
}


int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("deletion.in", "r", stdin);
    freopen("deletion.out", "w", stdout);

    int n; cin>>n;





    long long newKey;
    int leftChildNum;
    int rightChildNum;

    Node arr[n+1];


    for (int i = 1; i < n+1; i++){
        cin>>newKey>>leftChildNum>>rightChildNum;
        arr[i].key = newKey;
        arr[i].left = leftChildNum;
        arr[i].right = rightChildNum;
        arr[i].height = 1;
    }
    int keyToDelete;
    cin>>keyToDelete;


    writeHeights(arr, 1);



    int root = 1;

    //root = insertNode(arr, 1, n+1);
    root = deleteNode(arr, 1, keyToDelete);

    Node resArr[n+3];
    int outputCurIndex = 0;
    makeResultArr(arr, resArr, root, &outputCurIndex);



    cout<<n-1<<endl;
    for (int i = 1; i < n; i++){
        cout<<resArr[i].key<<" "<<resArr[i].left<<" "<<resArr[i].right<<endl;
    }

    //cout<<endl; for (int i = 1; i < n + 2; i++){  cout<<resArr[i].key<<" "<<resArr[i].left<<" "<<resArr[i].right<<endl;}


    return 0;
}
