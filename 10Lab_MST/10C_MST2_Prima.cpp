#include <iostream>
#include <iomanip>
#include <vector>
#include <set>


using namespace std;

void prim_MST( vector <pair <bool, vector <pair <int, int>>>> graph, vector <int> &WeightTable, set <pair <int, int>> q){

    while(!q.empty()) {

        int v = q.begin()->second;
        q.erase(q.begin());

        for (int i = 0; i < graph[v].second.size(); i++) {

            int finV = graph[v].second[i].second, curWeight = graph[v].second[i].first;

            if (!graph[finV].first && curWeight < WeightTable[finV]) {
                    q.erase({WeightTable[finV], finV});
                    WeightTable[finV] = curWeight;
                    q.insert({WeightTable[finV], finV});
            }
        }
        graph[v].first = true;
    }
}
int main() {
    std::ios_base::sync_with_stdio(0); 
    std::cin.tie(0);
    freopen("spantree3.in", "r", stdin);
    freopen("spantree3.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    vector <pair <bool, vector <pair <int, int>>>> graph (n); //использовано/нет + массив ребер (вес, куда идет)
    vector <int> WeightTable (n, 100001); //заполняем вектор с весами бесконечностями
    
    set <std::pair <int, int>> q;

    
    for (int i = 0; i < m; i++) {
        int a, b, w;

        cin >> a >> b >> w;
        graph[a - 1].second.push_back({w, b - 1});
        graph[b - 1].second.push_back({w, a - 1});
    }
    

    WeightTable[0] = 0;
    q.insert({0, 0});
    prim_MST(graph, WeightTable, q);

    long long weightMST = 0;
    for (int i = 0; i < WeightTable.size(); i++) {
        weightMST += WeightTable[i];
    }
    cout << weightMST;


    return 0;
}