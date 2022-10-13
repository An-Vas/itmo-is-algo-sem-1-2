#include <iostream>
#include <iomanip>

using namespace std;

//просто проверяю по очереди два условия: неориентированный граф - симметричный, а диагональ таблицы простого графа далжна состоять из нулей
int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n; // n - size of the table;
    cin>>n;

    int table[n][n];
    //i - rows(-); j - columns(|)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            cin>>table[i][j];
        }   
    }

    bool ItIsOrientedGraph = true;

    //тут в скобках фора сразу проверяется, не пора ли выйти из массива - если вдруг ответ уже "нет"
    for (int i = 0; (i < n)&&(ItIsrientedGraph); i++) {
        for (int j = 0; j < i; j++){
            if (table[i][j] != table[j][i]){
                ItIsrientedGraph = false;
                break;
            }
        }   
    }

    for (int i = 0; (i < n)&&(ItIsrientedGraph); i++) {
        if (table[i][i] != 0){
            ItIsrientedGraph = false;
            break;
        }
    }
    if (ItIsrientedGraph == true) {
        cout <<"YES"<<endl;
    } else cout<<"NO"<<endl;

    
    return 0;
}
