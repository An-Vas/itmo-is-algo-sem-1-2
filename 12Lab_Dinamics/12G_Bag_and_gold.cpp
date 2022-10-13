#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>


using namespace std;



int main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0); 

    freopen("knapsack.in", "r", stdin);
    freopen("knapsack.out", "w", stdout);
    
    
    int BagCapacity, n;
    cin >> BagCapacity >> n;

    vector <int> gold(n + 1);
    for (int i = 1; i <= n; i++) cin >> gold[i]; gold[0] = 0;

    int arr [n + 1][BagCapacity+1];
    for (int i = 0; i <= n; i++){ 
        for (int j = 0; j <= BagCapacity; j++){
            arr[i][j] = 0;
        }
    }
    //заполняем по строкам сверху вниз
    for (int i = 1; i <= n; i++){ 
        for (int j = 1; j <= BagCapacity; j++){
            //cout << "j = " << j << " max " <<arr[i - 1][j] << ", " << arr[i - 1][j - 1] <<" + " << gold[i] << " ||";
            if (j >= gold[i] /*&& j >= max (arr[i - 1][j], arr[i - 1][j - 1] + gold[i])*/ ) {
                arr[i][j] = max (arr[i - 1][j], arr[i - 1][j - gold[i]] + gold[i]);
                //cout << "done " <<i << " " << j<< " || " << arr[i][j];
            }
            else 
                arr[i][j] = arr[i - 1][j];
            //cout << endl;

            
        }
        
    }


    /*for (int i = 0; i <= n; i++){ 
        for (int j = 0; j <= BagCapacity; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }*/



    cout << arr [n][BagCapacity];

    
    
    return 0;
}
