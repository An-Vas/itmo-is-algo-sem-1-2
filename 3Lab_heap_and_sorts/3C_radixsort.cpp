#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

 void mergeM (vector <string>& a, int left, int mid, int right, int curNumToSort){
     int lPointer = 0;
     int rPointer = 0;

     vector <string> result (right - left);

     while (left + lPointer < mid and mid + rPointer < right) {
        if (a[left + lPointer][curNumToSort] <= a[mid + rPointer][curNumToSort]){
            result[lPointer + rPointer] = a[left + lPointer];
            lPointer += 1;
        } else if (a[left + lPointer][curNumToSort] > a[mid + rPointer][curNumToSort]){
            result[lPointer + rPointer] = a[mid + rPointer];
            rPointer += 1;
        }
     }
     while (left + lPointer < mid) {
            result[lPointer + rPointer] = a[left + lPointer];
            lPointer += 1;
     }
     while (mid + rPointer < right) {
            result[lPointer + rPointer] = a[mid + rPointer];
            rPointer += 1;
     }
     for (int i = 0; i < lPointer + rPointer; i++){
        a[left + i] = result[i];
     }

}


void mergeSort(vector <string>& a, int leftBorder, int rightBorder, int curNumToSort){

    if (leftBorder+1 >= rightBorder) {return ;}

    int mid = (rightBorder + leftBorder)/2;
    mergeSort(a, leftBorder, mid, curNumToSort);
    mergeSort(a, mid, rightBorder, curNumToSort);
    mergeM(a ,leftBorder, mid, rightBorder, curNumToSort);
}


void radixSort(vector <string>& a, int n, int m, int k){
    int curNumToSort = m;
    for (int i = 0; i<k; i++){
        curNumToSort--;
        mergeSort(a, 0, n, curNumToSort);
    }

}



int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    freopen("radixsort.in", "r", stdin);
    freopen("radixsort.out", "w", stdout);

    int n, m, k;
    cin>>n>>m>>k;

    vector <string> a(n);

    for (int i = 0; i<n; i++){
        cin>>a[i];
    }

    radixSort(a, n, m, k);

    for (int i = 0; i<n; i++){
        cout<<a[i]<<endl;
    }

    return 0;
}
