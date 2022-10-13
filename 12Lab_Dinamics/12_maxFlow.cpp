#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <queue>
#define INF 1000000000
using namespace std;

bool BFS(int s, int t, vector<vector<int>>& arr, vector <int>& parents){ //возращает true если из истока можно попасть в сток + в массив предков сохраняет найденный путь
    int n = arr.size();
    queue <int> q;
    vector <int> color (n, 0);

    q.push(s);
    color[s] = 1;

    while (!q.empty()){
        int u = q.front(); 
        q.pop();
        for (int v = 0; v < n; v++){
            if (color[v] == 0 && arr[u][v] > 0){
                q.push(v);
                color[v] = 1;
                parents[v] = u;
            }
        }
        //color[u] = 2;
    }
    
    if (color[t] == 1) return true;
    else return false;
}

int maxFlow (int s, int t, vector <vector<int>>& arr, vector <int>& parents){ //Форд Фалкерсон
    long long int maxFlow = 0;
    while (BFS(s, t, arr, parents)){ //проверили и заодно в массив предков сохранили найденный путь
        int curFlow = INF;
        int cur = t;
        while (cur != s) {//проходимся по массиву предков, проверяя все ребра по дороге и среди них находим ребро с минимальной пропускной способносстью.
            int prev = parents[cur];
            if (arr[prev][cur] < curFlow) curFlow = arr[prev][cur];
            cur = parents[cur];
        }
    
        cur = t;
        while (cur != s){
            int prev = parents[cur];
            arr[prev][cur] -= curFlow; //уменьшаем все ребра на найденный поток
            arr[cur][prev] += curFlow; //добавляем соответствующие антиребра, хотя по заданию нам и необязательно восстанавливать путь максимального потока
            cur = parents[cur];
        }
        maxFlow += curFlow;
    }
    return maxFlow;
}


int main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0); 

    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);

    int n, m;
    cin >> n >> m; //количество вершин и ребер в графе;
    vector <vector<int>> arr (n, vector<int> (n)) ; //для каждой вершины будем хранить матрицу смежности
    vector <int> parents (n); //потребуется для сохранения находимых в BFS маршрутов

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            arr[i][j] = 0;
        }     
    }

    for (int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        arr[a - 1][b - 1] = c;
    }


    cout << maxFlow(0, n-1, arr, parents);

    return 0;
}