#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>


using namespace std;


int max_available_number (vector <vector<int>>& data, vector<int>& cost, vector<int>& numbers, int u) {
    
    if (numbers[u] != 0) return numbers[u]; //если мы уже считали значение, то еще раз считать не будем
    else {
        int children_sum = 0;
        int grand_children_sum = 0;
        //для каждого ребенка находим его значение
        for (int a: data[u]){
            children_sum = children_sum + (max_available_number(data, cost, numbers, a));
            for (int b: data[a]) { //это уже grandchildren
                grand_children_sum += (max_available_number(data, cost, numbers, b));
            }
        }
        //cout << "u " << u << " gch " <<grand_children_sum << " ch " << children_sum <<" res " <<max(cost[u] + grand_children_sum, children_sum) << " cost[u] " <<cost[u]<<endl;
        if (cost[u] >= 0) {
            numbers[u] = max(cost[u] + grand_children_sum, children_sum);
            return max(cost[u] + grand_children_sum, children_sum);
        } else {
            numbers[u] = max(0 + grand_children_sum, children_sum);
            return max(0 + grand_children_sum, children_sum);
        }
        
    }
}



int main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0); 

    freopen("selectw.in", "r", stdin);
    freopen("selectw.out", "w", stdout);
    
    
    int n; //количество вершин в графе
    cin >> n;
    int root;

    
    vector <vector<int>> data (n + 1); //здесь хранится исходный граф. Для каждой вершины хранится вектор номеров ее детей
    vector <int> cost (n + 1);
    vector <int> numbers (n + 1, 0); //для каждой вершины здесь хранится число-ответ для случая, если бы она была корнем рассматриваемого дерева

    for (int i = 1; i <= n; i++){
        int b, c;
        cin >> b >> c;
        
        if (b == 0) {
            root = i;
            cost[i] = c;
        }
        else {
            cost[i] = c;
            data[b].push_back(i);
        }
    }


 
    cout << max_available_number(data, cost, numbers, root);
    
    return 0;
}
