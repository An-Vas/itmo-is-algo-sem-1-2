#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

void heap_item_recover (vector <long long>& a, int item, int heapSize){

    int leftChildNum = 2*item;
    int rightChildNum = 2*item+1;
    int largestNum;

    if (leftChildNum <= heapSize && a[leftChildNum] > a[item]){
        largestNum = leftChildNum;
    } else {
        largestNum = item;
    }

    if (rightChildNum <= heapSize && a[rightChildNum]>a[largestNum]) {
        largestNum = rightChildNum;
    }

    if (largestNum != item){
        swap (a[item], a[largestNum]);
        heap_item_recover(a, largestNum, heapSize);
    }
}

void build_heap(vector <long long>& a, int heapSize){
    for (int i = (heapSize/2); i>=1;  i--){
        heap_item_recover(a, i, heapSize);
    }
}

void heap_sort (vector <long long>& a, int heapSize){
    build_heap(a, heapSize);
    for (int i = heapSize; i >= 2; i--){
        swap (a[1], a[i]);
        heapSize--;
        heap_item_recover(a, 1, heapSize);
    }

}

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);

    int n;
    cin >> n;

    vector <long long> a (n+1);

    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }

    heap_sort(a,n);


    for (int i = 1; i <= n; i++){
        cout << a[i] << " ";
    }


    return 0;

}
