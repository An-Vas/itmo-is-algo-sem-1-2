#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

void QSort (vector <int>& a, int  left, int  right, int  k){
     //cout<<"Now working with "<<left<<" to "<<right<<endl;
     int  lPointer, rPointer, key, keyPos;
     //key  = a [(left + right)/ 2] ;
     key  = a [left + rand()%(right - left + 1)] ;
     //cout<<right - left<<endl;
     lPointer = left;
     rPointer = right;
     while (rPointer >= lPointer) {
        while (a[lPointer] < key) {
            lPointer++;
        }
        while (a[rPointer] > key ){
            rPointer--;
        }
        if (lPointer <= rPointer){
            swap(a[lPointer], a[rPointer]);
            lPointer++;
            rPointer--;
        }
     }


    if (lPointer - rPointer == 1 && a[lPointer - 1] == key && k == lPointer - 1){return;}
    else if (a[lPointer] == key && k == lPointer){ return;}
    else if (a[rPointer] == key && k == rPointer){ return;}


    if (k < lPointer && left < rPointer){ QSort(a, left, rPointer, k);}
    else if (k > rPointer && lPointer < right){ QSort(a, lPointer, right, k);}

}


int main ()

{

   freopen("kth.in", "r", stdin);
   freopen("kth.out", "w", stdout);
   int  n, k, Aconst, Bconst, Cconst;
   cin>>n>>k;
   k--;
   vector <int> a(n);

   cin>>Aconst>>Bconst>>Cconst>>a[0]>>a[1];

   for (int  i = 2; i<n; i++){
           a[i] = Aconst*a[i-2] + Bconst*a[i-1]+Cconst;
   }

   QSort(a, 0, n-1, k);
   cout<<a[k];

   return 0;

}





/*



*/

