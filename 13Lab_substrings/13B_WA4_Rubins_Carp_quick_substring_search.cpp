#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
int x = 2;
int k = 100000;
int n, m;



unsigned long long hashF (string str, int start, int end) {
   
    unsigned long long res = 0;
    for (int i = start; i < end; i++){
        res += (str[i] - 'A' + 1)*pow(x, (end - i - 1));
    }
    //res = res % k;
    return res;
}

vector <unsigned long long> answer;

void BuildH(string str, string substr, vector <unsigned long long>& hashTable){ //вычисление хэша для текста (str)
    
    hashTable[0] = hashF(str, 0, m);
    for (int i = 0; i < n - m; i++){
        unsigned long long int temp = (hashTable[i]*x - (str[i] - 'A' + 1)*(pow(x, m)) + (str[i + m]- 'A' + 1));
        hashTable[i+1] = temp;
        
    }


}

void Rubins_Carp(string str, string substr, vector <unsigned long long>& hashTable){
    BuildH(str, substr, hashTable);
    
    unsigned long long patternHash = hashF(substr, 0, m);
    
    for (int i = 0; i <= n - m; i++){
        if (hashTable[i] != patternHash){
            continue;
        }
        bool isSubStr = true;
        
        for (int j = 0; j < m; j++){
            if (str[i+j] != substr[j]){
                isSubStr = false;
                break;
            }
        }
        if (isSubStr) answer.push_back(i+1);
    }

}


int main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0); 

    freopen("search2.in", "r", stdin);
    freopen("search2.out", "w", stdout);

    string str, substr;
    
   
    cin >> substr >> str;
    n = str.length();
    m = substr.length();

    if (n < m) {
        cout << 0 << endl;
        return 0;
    }

    vector <unsigned long long> hashTable (n - m + 1);
    
    Rubins_Carp(str, substr, hashTable);
    
    cout << answer.size()<<endl;
    for (int i = 0; i < answer.size(); i++) cout << answer[i] << " ";

    return 0;
}