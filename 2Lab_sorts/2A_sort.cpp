#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

void mergeM (vector <int>& a, int left, int mid, int right){
     int lPointer = 0;
     int rPointer = 0;

     vector <int> result (right - left);

     while (left + lPointer < mid or mid + rPointer < right) {
        if ((a[left + lPointer] < a[mid + rPointer])&&(left + lPointer < mid) || mid + rPointer >= right){
            result[lPointer + rPointer] = a[left + lPointer];
            lPointer += 1;
        } else if ((a[left + lPointer] >= a[mid + rPointer])&&(mid + rPointer < right) || left + lPointer >= mid){
            result[lPointer + rPointer] = a[mid + rPointer];
            rPointer += 1;
        }

     }

     for (int i = 0; i < lPointer+rPointer; i++){
        a[left + i] = result[i];
     }
}



void mergeSort(vector <int>& a, int leftBorder, int rightBorder){
    if (leftBorder+1 >= rightBorder) {return ;}
    int mid = (rightBorder + leftBorder)/2;

    mergeSort(a, leftBorder, mid);
    mergeSort(a, mid, rightBorder);
    mergeM(a ,leftBorder, mid, rightBorder);
}



int main ()
{
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);

    int n;
    cin>>n;
    vector <int> a(n);

    for (int i = 0; i<n; i++){
        cin>>a[i];
    }

    mergeSort(a, 0, n);

    for (int i = 0; i<n; i++){
        cout<<a[i]<<" ";
    }

    return 0;
}
