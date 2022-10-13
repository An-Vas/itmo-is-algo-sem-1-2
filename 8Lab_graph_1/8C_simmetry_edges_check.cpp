#include <iostream>
#include <iomanip>

using namespace std;

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    
    int n, m; // n - count of vertexes; m - count of Edges of Graph;
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
        a--; b--; //because array starts from zero-number-element
        int min, max; //min number of the raw, max - number of the column. //because i want to fill only half of the table
        if (a>=b) {
            min = b; max = a;
        } else { min = a; max = b;}
        table[min][max]++;
    }



    bool ThereAreSimmEdges = false;

    for (int i = 0; (i < n)&&(!ThereAreSimmEdges); i++) {
        for (int j = 0; j <= i; j++){
            if (table[j][i] > 1){
                ThereAreSimmEdges = true;
                break;
            }
        }   
    }

   
    if (ThereAreSimmEdges == true) {
        cout <<"YES"<<endl;
    } else cout<<"NO"<<endl;

    
    return 0;
}
