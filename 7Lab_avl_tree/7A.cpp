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


int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);

    int n; cin>>n;



    if (n==0){ cout<<0; return 0; }
    long long newKey;
    int leftChildNum;
    int rightChildNum;

    Node arr[n+1];

    for (int i = 1; i < n+1; i++){
        cin>>newKey>>leftChildNum>>rightChildNum;
        arr[i].key = newKey;
        arr[i].left = leftChildNum;
        arr[i].right = rightChildNum;
        arr[i].height = 0;
    }
    int rootNum;



    rootNum = 1;

    writeHeights(arr, rootNum);



    for (int i = 1; i < n + 1; i++){
        if (arr[i].right!=0 && arr[i].left != 0)
            cout<<arr[arr[i].right].height - arr[arr[i].left].height<<endl;
        else if (arr[i].right!=0)
            cout<<arr[arr[i].right].height<<endl;
        else if (arr[i].left!=0)
            cout<<-arr[arr[i].left].height<<endl;
        else
            cout<<0<<endl;
    }

    return 0;
}
