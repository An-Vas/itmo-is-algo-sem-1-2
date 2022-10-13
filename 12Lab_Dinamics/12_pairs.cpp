#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <queue>

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
        color[u] = 2;
    }
    
    if (color[t] == 2) return true;
    else return false;
}

int maxFlow (int s, int t, vector <vector<int>>& arr, vector <int>& parents){ //Форд Фалкерсон
    long long int maxFlow = 0;
    while (BFS(s, t, arr, parents)){ //проверили и заодно в массив предков сохранили найденный путь
        int curFlow = 1;
        int cur = t;
        //минимальный вес ребра искать не надо, он заведомо равен 1
        while (cur != s){
            int prev = parents[cur];
            arr[prev][cur] -= curFlow; //уменьшаем все ребра на найденный поток
            arr[cur][prev] += curFlow; //добавляем соответствующие антиребра, хотя по заданию нам и необязательно восстанавливать путь максимального потока
            cur = parents[cur];
        }
        maxFlow += curFlow;
        //cout << maxFlow << endl;
         
    }

    return maxFlow;
}


int main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0); 

    //freopen("maxflow.in", "r", stdin);
    //freopen("maxflow.out", "w", stdout);

    int n, m, k;
    cin >> n >> m >> k; //количество вершин в долях и количество ребер в графе;
    vector <vector<int>> arr (n + m + 2, vector<int> (n + m + 2, 0)) ; //для каждой вершины будем хранить список смежности
    vector <int> parents (n + m + 2); //потребуется для сохранения находимых в BFS маршрутов

    /*for (int i = 0; i < n + m + 2; i++){
        for (int j = 0; j < n + m + 2; j++){
            arr[i][j] = 0;
        }     
    }*/

    for (int i = 0; i < k; i++){
        int a, b, c = 1;
        cin >> a >> b;
        arr[a][b + n] = c;
    }

    

    //вершинка истока соединена со всеми вершинами второй доли
    for (int i = 1; i <= n; i++) {
        arr[0][i] = true;
    }

    //вершинка стока соединена со всеми вершинами второй доли
    for (int i = n + 1; i <= n + m; i++){
        arr[i][n + m + 1] = 1;
    }

        

    cout << maxFlow(0, n + m + 1, arr, parents);

    return 0;
}