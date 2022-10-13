#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>

using namespace std;

void put_on_right_place_down (vector <long long>& a, vector <long long>& extraArr, long long itemNum, long long heapSize){

    long long leftChildNum = 2*itemNum;
    long long rightChildNum = 2*itemNum+1;
    long long smallestNum;


    if (leftChildNum <= heapSize && a[leftChildNum] < a[itemNum]){
        smallestNum = leftChildNum;
    } else {
        smallestNum = itemNum;
    }

    if (rightChildNum <= heapSize && a[rightChildNum]< a[smallestNum]) {
        smallestNum = rightChildNum;
    }

    if (smallestNum != itemNum){
        swap (a[itemNum], a[smallestNum]);
        swap (extraArr[itemNum], extraArr[smallestNum]);
        put_on_right_place_down(a, extraArr, smallestNum, heapSize);
    }
}

void put_on_right_place_up (vector <long long>& a, vector <long long>& extraArr, long long numberOfItem){
    if (a[numberOfItem] < a[numberOfItem/2] && numberOfItem > 1 ){
        swap(a[numberOfItem], a[numberOfItem/2]);
        swap(extraArr[numberOfItem], extraArr[numberOfItem/2]);
        put_on_right_place_up(a, extraArr, numberOfItem/2);
    }

}

void push (vector <long long>& a, vector <long long>& extraArr, long long heapSize, long long totalCommands){
    long long newItem;
    cin>>newItem;
    a[heapSize] = newItem;
    extraArr[heapSize] = totalCommands;
    put_on_right_place_up(a, extraArr, heapSize);
}

void decrease_key (vector <long long>& a, vector <long long>& extraArr){
    long long numberOfCommand, newValue, curNumOfItem;
    cin>>numberOfCommand>>newValue;
    for (long long i = 1; i <= 1000000; i++){
        if (extraArr[i] == numberOfCommand){
            curNumOfItem = i;
            break;
        }
    }
    a[curNumOfItem] = newValue;
    put_on_right_place_up(a, extraArr, curNumOfItem);
}

void extract_min (vector <long long>& a, vector <long long>& extraArr , long long heapSize){
    long long minNum = a[1];
    a[1] = a [heapSize+1];
    extraArr[1] = extraArr[heapSize+1];
    cout<<minNum<<endl;
    put_on_right_place_down ( a, extraArr, 1, heapSize);
}

int main (){
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    freopen("priorityqueue.in", "r", stdin);
    freopen("priorityqueue.out", "w", stdout);

    long long totalCommands = 0;
    long long heapSize = 0;
    string curStr;

    vector <long long> a (1000000);
    vector <long long> extraArr (1000000);


    while (cin >> curStr){
        char curCommand = curStr[0];
        if (curCommand == 'p') {
            totalCommands++; heapSize++;
            push(a, extraArr, heapSize, totalCommands);
        }
        if (curCommand == 'd') {
            totalCommands++;
            decrease_key (a, extraArr);
        }
        if (curCommand == 'e') {
            totalCommands++;
            if (heapSize >= 1){
                heapSize--;
                extract_min (a, extraArr, heapSize);
            } else cout <<"*"<<endl;

        }

    }

    return 0;
}
