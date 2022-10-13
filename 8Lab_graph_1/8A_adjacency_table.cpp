#include <iostream>
#include <iomanip>
/*#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <cstring>
#include <cmath>*/

using namespace std;

//просто считываются числа и в соответстыующие ячейки таблицызаносятся единицы
//Да, я переназываю все вершины.
int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n = 1, m; // n - count of vertexes; m - count of Edges of Graph;
    cin>>n>>m;

    int table[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            table[i][j] = 0;
        }   
    }

    for (int i = 0; i < m; i++){
        int a, b; //a - begin of the edge, b - end of the edge
        cin>>a>>b;
        a--;
        b--; //because array starts from zero-number-element
        table[a][b] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            cout<<table[i][j]<<" ";
        }   
        cout<<endl;
    }

    
    return 0;
}
