#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

vector <long long> answer;

void BuildPrefixFunction(string str, vector <long long>& prefixTable){     
    int i = 1; int j = 0;
    int n = str.length();
    while (i < n){
        cout << "i = "<<i<<" j = " <<j <<endl; 
        if (str[i] == str[j]){
            prefixTable[i + 1] = j + 1;
            i++;
            j++;
        } else {
            if (j > 0) {
                j = prefixTable[j];
            } else {
                prefixTable[i + 1] = 0;
                i++;
            }
        }
    }
}




int main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0); 

    //freopen("prefix.in", "r", stdin);
    //freopen("prefix.out", "w", stdout);

    string str;
    cin  >> str;
    int n = str.length();
    vector <long long> prefixTable (n + 1);
    BuildPrefixFunction(str, prefixTable);

    for (int i = 1; i < prefixTable.size(); i++) cout << prefixTable[i] << " ";

    return 0;
}