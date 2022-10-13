#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;
#define INF 1000000001

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

    if (right < n && a[right] >= x){
        resultL = right;
    } else {
        resultL = -2;
    }
    return resultL;
}



int main (){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    
    int n, LIP_lenght = 0, j; //The largest increasing subsequence 
    cin >> n;
    
    vector <int> data (n); //сюда записывается исходный массив чиселок
    vector <int> lip_end_number (n + 1); //элемент под номером i это минимальное число, на которое может заканчиваться последовательность длины i
    vector <int> lip_position (n + 1); //элемент под номером i это индекс числа, записанного на этой позиции в массиве gip_number
    vector <int> lip_prev (n + 1);//элемент под номером i это индекс числа, предыдущего для элемента data[i]


    for (int i = 0; i < n; ++i){
        cin >> data[i];
        lip_end_number[i] = INF;
    }
    lip_end_number[n] = INF;



    lip_position[0] = -1;
    lip_end_number[0] = -INF;


    for (int i = 0; i < n; ++i){
        int j = binSearchLeft(lip_end_number, data[i], n + 1);
        if ((lip_end_number[j - 1] < data[i]) && (data[i] < lip_end_number[j])){
            
            lip_end_number[j] = data[i];
            lip_position[j] = i;
            lip_prev[i] = lip_position[j - 1];
            if (LIP_lenght < j) LIP_lenght = j;
        }
        
    }

    
    vector<int> answer;
    cout << LIP_lenght << endl;
    int p = lip_position[LIP_lenght];
    while (p!=-1) {
        //cout << data[p] <<" ";
        answer.push_back(data[p]);
        p = lip_prev[p];
    }
    reverse(answer.begin(), answer.end());

    for (auto num: answer){
        cout << num << " ";
    }
    return 0;
}
