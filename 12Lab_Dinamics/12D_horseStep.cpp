#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;
#define INF 1000000001

int main (){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    
    freopen("knight2.in", "r", stdin);
    freopen("knight2.out", "w", stdout);
    int n, m;
    cin >> n >> m;



    int arr[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i][j] = 0;
        }
    }
    arr[0][0] = 1;
    
    
    for (int k = 0; k < n + m; k++){ //идем по  клеточкам в форме треугольника, то есть в порядке увеличения цифр
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i + j == k) {
                    if (i - 2 >= 0 && j + 1 < m) {
                        arr[i][j] += arr[i - 2][j + 1];
                    } 
                    if (i - 2 >= 0 && j - 1 >= 0) {
                        arr[i][j] += arr[i - 2][j - 1];
                    }
                    if (i - 1 >= 0 && j - 2 >= 0) {
                        arr[i][j] += arr[i - 1][j - 2];
                    }
                    if (i + 1 < n && j - 2 >= 0) {
                        arr[i][j] += arr[i + 1][j - 2];
                    }
                }
            }
        }

    }

    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout<<arr[i][j];
        }
        cout<<"\n";
    }*/
    cout << arr [n-1][m-1] << "\n";


   

   
    return 0;
}
