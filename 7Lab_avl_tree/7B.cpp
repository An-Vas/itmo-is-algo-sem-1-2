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
  int parent;
  int height;

};

void treeWalk (Node* arr, int root){
    if (arr[root].left != 0) {treeWalk(arr, arr[root].left); }
    //cout<<arr[root].key<<" "<<arr[root].left<<" "<<arr[root].right<<endl;
    if (arr[root].right != 0) {treeWalk(arr, arr[root].right); }
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

int rotateLeft(Node* arr, int a){
    //cout<<"start rotate left a"<<a<<endl
    //cout<<arr[1].right<<endl;
    int RightCh = arr[a].right;
    int p;
    if (arr[a].parent!=0) p = arr[a].parent; else p=0;
   int b = arr[a].right;
   arr[a].right = arr[b].left;
   arr[b].left = a;
   //if (arr[a].parent!=0) {
        arr[p].left = b;
        arr[b].parent = p;
    //}
   writeHeights(arr, a);
   writeHeights(arr, b);


    return RightCh;

}

void rotateRight(Node* arr, int a){
    //cout<<"start rotate right a"<<a<<endl;
    int p = 0;
    if (arr[a].parent != 0) p = arr[a].parent;
    int b = arr[a].left;
    arr[a].left = arr[b].right;
    arr[b].right = a;
    //if (arr[a].parent!=0) {
        arr[p].right = b;
        arr[b].parent = p;
    //}
    writeHeights(arr, a);
    writeHeights(arr, b);
}

int bigRotateLeft(Node* arr, int a){
    int n = 7;

    rotateRight(arr, arr[a].right);

    int RightCh = arr[1].right;

    rotateLeft(arr, a);


    return RightCh;
}



int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("rotation.in", "r", stdin);
    freopen("rotation.out", "w", stdout);

    int n; cin>>n;



    if (n==0){ cout<<0; return 0; }
    long long newKey;
    int leftChildNum;
    int rightChildNum;

    Node arr[n+1];

    for (int i = 1; i < n+1; i++){
        arr[i].parent = 0;
    }

    for (int i = 1; i < n+1; i++){
        cin>>newKey>>leftChildNum>>rightChildNum;
        arr[i].key = newKey;
        arr[i].left = leftChildNum;
        arr[i].right = rightChildNum;
        arr[i].height = 0;

        if (leftChildNum != 0) arr[leftChildNum].parent = i;
        if (rightChildNum != 0) arr[rightChildNum].parent = i;
    }

    int rootNum;



    rootNum = 1;

    writeHeights(arr, rootNum);
    int rightChildBalance;
    int i = arr[rootNum].right;
    if (i==0) return 0;

    if (arr[i].right!=0 && arr[i].left != 0)
            rightChildBalance = arr[arr[i].right].height - arr[arr[i].left].height;
        else if (arr[i].right!=0)
            rightChildBalance =  arr[arr[i].right].height;
        else if (arr[i].left!=0)
            rightChildBalance = -arr[arr[i].left].height;
        else
            rightChildBalance = 0;

    int root = 1;
    //cout<<rightChildBalance<<endl;
    if (rightChildBalance == -1) {
        root = bigRotateLeft(arr, 1);
    } else
    root = rotateLeft(arr, rootNum);
    Node resArr[2*(n+1)];
    int shift = 0;




    int outputCurIndex = 0;
    makeResultArr(arr, resArr, root, &outputCurIndex);



    cout<<n<<endl;
    for (int i = 1; i < n + 1; i++){
        //cout<<arr[i].key<<" "<<arr[i].left<<" "<<arr[i].right<<endl;
        cout<<resArr[i].key<<" "<<resArr[i].left<<" "<<resArr[i].right<<endl;
    }

    return 0;
}
