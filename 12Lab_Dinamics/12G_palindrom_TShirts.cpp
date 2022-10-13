#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

#define INF 1000000000


using namespace std;

int countOfPalindromes (int a, int b, vector <vector<int>>& palindrome, int* colors) {
    if (palindrome[a][b] != 0) { //если искомое значение уже найдено, то возращаем его.
        return palindrome[a][b];
    }
    
    else if (a == b) { //подпоследовательность из одного единственного цвета является палиндромом и полиндром в такой подпоследовательности единственен
        return 1;
    } else if (a > b) { //то подпоследовательность кончается раньше, чем заканчивается - полиндромов нет
        return 0;
    }  
    
    else if (colors[a] == colors[b]) { //то есть i и j, являющиеся концом и началом рассматриваемой подстроки, совпали и благодаря этому полиндромную подпоследовательность можно увеличить 
        palindrome[a][b] = (countOfPalindromes(a, b - 1, palindrome, colors) + countOfPalindromes(a + 1, b, palindrome, colors) + 1) % INF;
        return palindrome[a][b];
    } else if (colors[a] != colors[b]){
        palindrome[a][b] = (INF + (countOfPalindromes(a,b - 1, palindrome, colors) + countOfPalindromes(a + 1, b, palindrome, colors)) % INF - countOfPalindromes(a + 1, b - 1, palindrome, colors)) % INF;
        return palindrome[a][b];
    }
}



int main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0); 

    //freopen("knapsack.in", "r", stdin);
    //freopen("knapsack.out", "w", stdout);

    int n;
    cin >> n; //количество детей;

    vector <vector<int>> palindrome(n+1, vector<int> (n+1) );

    //int palindrome[n + 1][n + 1];
    int colors [n];

    
    for (int i = 0; i < n ; i++) cin >> colors[i];
    
   
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= n; j++){
            palindrome[i][j] = 0;
        }
    }

    int result = countOfPalindromes(0, n - 1, palindrome, colors);
    cout << result;
    return 0;
}