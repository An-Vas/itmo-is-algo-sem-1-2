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




int main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0); 

    int alphabet; //размерность алфавита
    cin  >> alphabet;
    string str;
    cin  >> str;
    int n = str.length();
    vector <long long> prefixTable (n + 1);
    BuildPrefixFunction(str, prefixTable);
    for (int i = 1; i < prefixTable.size(); i++) cout << prefixTable[i] << " ";

    vector <vector <int>> conditions  (n + 1, std::vector <int> (alphabet, 0)); //каждая строка отвечает за букву


    for (int i = 0; i < n + 1; i++){
        for (char ch = 'a'; ch < 'a' + alphabet; ch++){
            int charNum = ch - 'a';
            if (i == 0){ //стартовое состояние (условие входа в автомат)
                if (ch == str[i]) conditions[i][charNum] = 1;
                else conditions[i][charNum] = 0;
            }
            
            else if (i > 0 && ch != str[i]){
                conditions[i][charNum] = conditions[prefixTable[i]][charNum];
                cout<< "i = "<<i<<" char "<<charNum<<" pr = "<<prefixTable[i]<<" res ="<<conditions[i][charNum]<<'\n';
                }

            else if (i > 0 && ch == str[i])
                conditions[i][charNum] = i + 1;
        }
    }

    for (auto a: conditions){
        for (auto b: a){
            cout << b << " ";
        }
        cout << endl;
    }

 

    return 0;
}