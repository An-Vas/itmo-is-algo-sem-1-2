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

void Knutt_Morris_Pratt_matcher(string str, string substr){   
    int n = str.length();
    int m = substr.length();  
    vector <long long> prefixTable (m+1);
    BuildPrefixFunction(substr, prefixTable);
    
    int i = 0; int j = 0;
    
    while (i < n){
        if (str[i] == substr[j]){
            i++;
            j++;
        }
        if (j == m) {
            answer.push_back(i - j + 1);
            j = prefixTable[j];
        } else if (i < n && str[i] != substr[j]){
        if (j > 0){
            j = prefixTable[j];
        }
        else
            i++;
        }
    }
     
    
}




int main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0); 

    freopen("search2.in", "r", stdin);
    freopen("search2.out", "w", stdout);

    string str, substr;
    cin  >> substr >> str;
    int n = str.length();
    int m = substr.length();
    if (n < m) {
        cout << 0 << endl;
        return 0;
    }
    
    //BuildPrefixFunction(str, prefixTable);
    Knutt_Morris_Pratt_matcher(str,substr);
    
    cout << answer.size()<<endl;
    for (int i = 0; i < answer.size(); i++) cout << answer[i] << " ";

    return 0;
}