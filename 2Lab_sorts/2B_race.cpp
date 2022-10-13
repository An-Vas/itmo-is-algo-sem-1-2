#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
using namespace std;



void mergeM (vector <string>& c, vector <string>& s, int left, int mid, int right){
     int lPointer = 0;
     int rPointer = 0;

     vector <string> resultC (right - left);
     vector <string> resultS (right - left);

     while (left + lPointer < mid and mid + rPointer < right) {
        if (c[left + lPointer] <= c[mid + rPointer]){
            resultC[lPointer + rPointer] = c[left + lPointer];
            resultS[lPointer + rPointer] = s[left + lPointer];
            lPointer += 1;
        } else if ((c[left + lPointer] > c[mid + rPointer])){
            resultC[lPointer + rPointer] = c[mid + rPointer];
            resultS[lPointer + rPointer] = s[mid + rPointer];
            rPointer += 1;
        }
     }
     while (left + lPointer < mid) {
            resultC[lPointer + rPointer] = c[left + lPointer];
            resultS[lPointer + rPointer] = s[left + lPointer];
            lPointer += 1;
     }
     while (mid + rPointer < right) {
            resultC[lPointer + rPointer] = c[mid + rPointer];
            resultS[lPointer + rPointer] = s[mid + rPointer];
            rPointer += 1;
     }
     for (int i = 0; i < lPointer+rPointer; i++){
        c[left + i] = resultC[i];
        s[left + i] = resultS[i];
     }

}

void mergeSort(vector <string>& c, vector <string>& s, int leftBorder, int rightBorder){
    if (leftBorder+1 >= rightBorder) {return ;}

    int mid = (rightBorder + leftBorder)/2;

    mergeSort(c, s, leftBorder, mid);
    mergeSort(c, s, mid, rightBorder);
    mergeM(c, s, leftBorder, mid, rightBorder);
}


int main ()
{
    freopen("race.in", "r", stdin);
    freopen("race.out", "w", stdout);

    int n;
    cin>>n;

    vector <string> ListOfCounries (n);
    vector <string> ListOfSportsman (n);

    for (int i = 0; i < n; i++){
        cin>>ListOfCounries[i]>>ListOfSportsman[i];
    }

    mergeSort(ListOfCounries, ListOfSportsman, 0, n);


    string curCountry = "0";

    for (int i = 0; i < n; i++){
        if (ListOfCounries[i] == curCountry){
            cout<<ListOfSportsman[i]<<endl;

        } else {
            curCountry = ListOfCounries[i];
            cout << "=== " << ListOfCounries[i] <<" ==="<<endl;
            cout<<ListOfSportsman[i]<<endl;
        }
    }

    return 0;
}
