#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

int binSearchLeft(vector <int>& a, int x, int n){
    int resultL = -2;
    int left = -1;
    int right = n;
    while (right > left + 1) {
        int m = (left + right)/2;
        if (a[m] < x){
            left = m;
        }
        else  {right = m;}
    }

    if (right < n && a[right] == x){
        resultL = right;
    } else {
        resultL = -2;
    }
    return resultL;
}

int binSearchRight(vector <int>& a,int x,int n){
    int resultR = -2;
    int left = -1;
    int right = n;
    while (right > left + 1) {
        int m = (left + right)/2;
        if (a[m] > x){
            right = m;
        }
        else  {left = m;}
    }

    if (left > -1 && a[left] == x){
        resultR = left;
    } else {
        resultR = -2;
    }

    return resultR;
}


int main ()
{

    //freopen("binsearch.in", "r", stdin);
    //freopen("binsearch.out", "w", stdout);

    int n, m, x;
    cin>>n;
    vector <int> a (n);
    for (int i = 0; i < n; i++){
        cin>>a[i];
    }

    cin>>m;

    for (int i = 0; i < m; i++){
        cin>>x;
        int resultL = binSearchLeft(a, x, n);
        int resultR = binSearchRight(a, x, n);
        cout<<resultL+1<<" "<<resultR+1<<endl;
    }

    return 0;

}
