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


void InorderTreeWalk(Node arr[], vector <long long>& orderCheck, int rootNum, int &counter){
    if (rootNum != 0){
        InorderTreeWalk(arr, orderCheck, arr[rootNum].left, counter);
        orderCheck[counter] = arr[rootNum].key;
        counter++;
        InorderTreeWalk(arr, orderCheck, arr[rootNum].right, counter);
    }
}

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    //freopen("check.in", "r", stdin);
    //freopen("check.out", "w", stdout);

    int n;
    cin>>n;

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
        if (leftChildNum != 0) arr[leftChildNum].parent = i;
        if (rightChildNum != 0) arr[rightChildNum].parent = i;
    }

    int rootNum = 0, rootCounter = 0;

    for (int i = 1; i < n+1; i++){
        if (arr[i].parent == 0) {
            rootNum = i;
            rootCounter++;

        }
    }

    int treeOrderCheckResult = 1;

    vector <long long> orderCheck (n+1);
    int counter=1;
    InorderTreeWalk(arr, orderCheck, rootNum, counter);


    for (int i = 1; i < n; i ++){
        if (orderCheck[i]>=orderCheck[i+1]) { treeOrderCheckResult = 0; break; }
    }



    if (n==0){cout<<"YES";}
    else if (rootCounter != 1) {cout<<"NO";}
    else{

        if (treeOrderCheckResult == 1) cout<<"YES";
        else  cout<<"NO";

    }

    return 0;

}
