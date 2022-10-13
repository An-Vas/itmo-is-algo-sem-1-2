#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;


int main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0); 

    freopen("search1.in", "r", stdin);
    freopen("search1.out", "w", stdout);

    string str, substr;
    cin >> substr >> str;

    int counter = 0;
    vector<int> numbers;

    int n = str.length();
    int m = substr.length();


    /*for (int i = 0; i <= str.length() - substr.length(); i++){
            bool is_substr = true;
            for (int j = 0; j < substr.length(); j++){
                if (str[j + i] != substr[j]){ 
                    is_substr = false; 
                    break; 
                }
            }
            if (is_substr) {
                numbers.push_back(i + 1);
                counter++;
            }
    }
    */

    for (int i = 0; i <= n - m; i++){
        bool isSubStr = true;
        for (int j = 0; j < m; j++){
            //cout << j + i <<" " << str[j + i] << " " <<j << " " << substr[j] << endl;
            if (str[j + i] != substr[j]){ 
                isSubStr = false;
                break; 
            }
        }
        
        if (isSubStr) {
            numbers.push_back(i + 1);
            counter++;
        }
    }

    cout << counter << endl;
    if (counter > 0) for (auto a: numbers) cout << a << " ";

    return 0;
}