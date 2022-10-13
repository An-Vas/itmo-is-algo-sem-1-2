#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
int counter = 0;

vector <bool> answer;
vector <bool> isCheckedFromMarkAnswer;
vector <bool> isCheckedFromIsTerm;
vector <vector <int>> conditions;//здесь хранятся все перходы в автомате.
vector <int> terminateCond;//здесь хранятся номера вершин, в которых заканчиваются данные подстроки.
vector <int> sufArr;
vector <int> parent;
vector <char> parChar; //по какому символу переходим из parent в это состояние
vector <int> isTerm; 
vector <int> TermFor; 
vector <vector <int>> terminateFor;


bool isTermFor (int CondNum);

int getLink(int n, char c);

void markAnswer (int cond){
    if (isCheckedFromMarkAnswer[cond]) return; //уже помечали значит все ответы, не нужно делать это еще раз
 
    isCheckedFromMarkAnswer[cond] = true;
    /*for (int i = 0; i < terminateCond.size(); i++) 
    if (terminateCond[i] == cond) {
        answer[i] = true;
    }*/
    for (int i = 0; i < terminateFor[cond].size(); i++){
        answer[terminateFor[cond][i]] = true;
    }
}

int getSuffLink(int n){
    markAnswer(n);
    if (sufArr[n] != -1) {
        return sufArr[n];
    } else {
        if (n == 0 || parent[n] == 0){
            sufArr[n] = 0;
        } else {
            sufArr[n] = getLink(getSuffLink(parent[n]), parChar[n]);
        }
    }
    
    markAnswer(sufArr[n]);
    return sufArr[n];
}

int getLink(int n, char c){
    markAnswer(n);

    if (conditions[n][c - 'a'] != -1) {
        markAnswer(conditions[n][c - 'a']);
        return conditions[n][c - 'a'];
    } else {
        if (n == 0){
            conditions[n][c - 'a'] = 0;
        } 
        else {
            conditions[n][c - 'a'] = getLink(getSuffLink(n), c);
        }
    }
    

    markAnswer(conditions[n][c - 'a']);
    return conditions[n][c - 'a'];
}
    

bool isTermFor (int CondNum) {
    if (isCheckedFromIsTerm[CondNum]) return true;
    isCheckedFromIsTerm[CondNum] = true;
    markAnswer(CondNum);

    if (CondNum == 0) return false;
    if (isTerm[CondNum] == 1){
        answer[TermFor[CondNum]] = true;
        bool temp = isTermFor(getSuffLink(CondNum));
        return true;
    } else if (isTerm[CondNum] == -1){
        bool temp = isTermFor(getSuffLink(CondNum));
        return false;
    } else if (isTerm[CondNum] == 0){
        bool temp = isTermFor(getSuffLink(CondNum));
        
        //if (temp) answer[CondNum] = true;
        return temp;
        //return isTermFor(SuffixFunction(CondNum));
    }
    //return -1;//никогда не вызывается, просто чтобы предупреждений от компилятора было поменьше
}


int main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("search4.in", "r", stdin);
    freopen("search4.out", "w", stdout); 

    int alphabet = 26; //размерность алфавита - прописные латинские буквы
    
    
    int n;
    cin >> n;

    
    answer.resize(n, false);
    
    terminateCond.resize(n);//здесь хранятся номера вершин, в которых заканчиваются данные подстроки.
    
    conditions.push_back(vector <int> (26, -1));
    parent.push_back(-1);
    parChar.push_back('0');
    isTerm.push_back(false);
    sufArr.push_back(-1);
    TermFor.push_back(-1); 
    terminateFor.push_back(vector <int> (0));
    isCheckedFromMarkAnswer.push_back(false);
    isCheckedFromIsTerm.push_back(false);

    
    //создание бора-автомата


    int CondCounter = 1; //- сколько вершин - состояний в графе
    for (int i = 0; i < n; i++){
        string str;
        cin  >> str;
        int CurCond = 0;
        for (int j = 0; j < str.length(); j++){
            if (conditions[CurCond][str[j]-'a'] == -1) { //тогда нужно создать новое состояние.
                conditions.push_back(vector <int> (26, -1));
                int newCondNum = conditions.size() - 1; //так как добавили в конец массива
                conditions[CurCond][str[j]-'a'] = newCondNum;
                parent.push_back(CurCond);
                parChar.push_back(str[j]);
                isTerm.push_back(false);
                isCheckedFromMarkAnswer.push_back(false);
                isCheckedFromIsTerm.push_back(false);
                terminateFor.push_back(vector <int> (0));

                sufArr.push_back(-1);
                TermFor.push_back(-1); 


                CurCond = newCondNum;
            } else { //тогда переходим по ссылке в следующее состояние
                CurCond = conditions[CurCond][str[j]-'a'];
            }
            if (j == str.length() - 1) {terminateCond[i] = CurCond; TermFor[CurCond] = i; terminateFor[CurCond].push_back(i);}
        }
        isTerm[CurCond] = 1;
        
    }



    sufArr[0] = 0;

    //запускаем нашу строку в бор - автомат
    string str;
    cin  >> str;
    int CurCond = 0;

    
    for (int i = 0; i < str.length(); i++){
        CurCond = getLink (CurCond, str[i]);
        int term = isTermFor(CurCond);
        markAnswer(CurCond);
    }
    CurCond = getSuffLink (CurCond);

    for (auto a: answer) if (a) cout << "YES\n"; else cout << "NO\n";

    return 0;
}