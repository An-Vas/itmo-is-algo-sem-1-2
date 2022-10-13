#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>


using namespace std;


int max_available_number (vector <vector<int>>& data, vector<int>& numbers, int u) {
    if (numbers[u] != 0) return numbers[u]; //если мы уже считали значение, то еще раз считать не будем
    else {
        int children_sum = 0;
        int grand_children_sum = 0;
        //для каждого ребенка находим его значение
        for (int a: data[u]){
            children_sum = children_sum + (max_available_number(data, numbers, a));
            for (int b: data[a]) { //это уже grandchildren
                grand_children_sum += (max_available_number(data, numbers, b));
            }
        }
        numbers[u] = max(1 + grand_children_sum, children_sum);
        return max(1 + grand_children_sum, children_sum);
    }
}



int main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0); 
    
    
    int n; //количество вершин в графе
    cin >> n;
    int root;

    
    vector <vector<int>> data (n + 1); //здесь хранится исходный граф. Для каждой вершины хранится вектор номеров ее детей


    for (int i = 1; i <= n; i++){
        int a, b;
        a = i;
        cin >> b;
        
        if (b == 0) root = i;
        else data[b].push_back(i);
    }

    vector <int> numbers (n + 1, 0); //для каждой вершины здесь хранится число-ответ для случая, если бы она была корнем рассматриваемого дерева
 
    cout << max_available_number(data, numbers, root);
    
    return 0;
}
