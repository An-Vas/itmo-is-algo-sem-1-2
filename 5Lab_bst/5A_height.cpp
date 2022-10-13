#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

struct Node {
  long long key;
  int left;
  int right;
  int parent;
};

int maxHeight(Node arr[], int root){

    int leftHeight, rightHeight;

    if (arr[root].left != 0) {
        leftHeight = maxHeight(arr, arr[root].left);
    } else {
        leftHeight = 0;
    }

     if (arr[root].right != 0) {
        rightHeight = maxHeight(arr, arr[root].right);
    } else {
        rightHeight = 0;
    }



    if (leftHeight > rightHeight) {
        return 1+leftHeight;
    } else {
        return 1+rightHeight;
    }
}

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    freopen("height.in", "r", stdin);
    freopen("height.out", "w", stdout);

    int n;
    cin>>n;

    if (n==0){ cout<<0;}
    long long newKey;
    int leftChildNum;
    int rightChildNum;

    Node arr[n+1];

    for (int i = 1; i < n+1; i++){
        cin>>newKey>>leftChildNum>>rightChildNum;
        arr[i].key = newKey;
        arr[i].left = leftChildNum;
        arr[i].right = rightChildNum;
        arr[i].parent = 0;
        if (leftChildNum != 0) arr[leftChildNum].parent = i;
        if (rightChildNum != 0) arr[rightChildNum].parent = i;
    }

    int rootNum;

    for (int i = 1; i < n+1; i++){
        if (arr[i].parent == 0) {
            rootNum = i;
            break;
        }
    }

    if (n!=0) cout<<maxHeight(arr, rootNum);


    return 0;

}
