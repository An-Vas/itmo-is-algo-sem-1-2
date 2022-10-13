#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

class Vertex {
    public:
    int color;   
};

class Edge {
    public:
    int value;
    int entrance;
    int exit;
    bool MST;
};

void QSort (Edge* & a, int left, int right){
     int lPointer, rPointer, tempEx, tempEn;
     int key, tempVal;
     key  = a [ ( left + right ) / 2 ].value ;
     lPointer = left;
     rPointer = right;
     while (rPointer >= lPointer) {
        while (a[lPointer].value < key) {
            lPointer++;
        }
        while (key < a[rPointer].value ){
            rPointer--;
        }
        if (lPointer <= rPointer){

            tempEn = a[lPointer].entrance;
            tempEx = a[lPointer].exit;
            tempVal = a[lPointer].value;

            a[lPointer].entrance = a[rPointer].entrance;
            a[lPointer].exit = a[rPointer].exit;
            a[lPointer].value = a[rPointer].value;

            a[rPointer].entrance = tempEn;
            a[rPointer].exit = tempEx;
            a[rPointer].value = tempVal;

            lPointer++;
            rPointer--;
        }
     }
     if (left < rPointer) { QSort(a, left, rPointer); }
     if (lPointer < right) { QSort(a, lPointer, right); }

}

void CountingSort (Edge* & A, const int & m){
    int* P = new int [100002];
    for (int i = 0; i < 100001; i++) P[i] = 0;

    for (int i = 0; i < m; i ++) P[A[i].value]++;

    int cash = 0;
    for (int i = 0; i < 100001; i++) {
        int tempInt = P[i];
        P[i] = cash;
        cash = cash + tempInt;     
    }
    Edge* B = new Edge [m+1];
    for (int i = 0; i < m; i ++){
        B[P[A[i].value]].value = A[i].value;
        B[P[A[i].value]].entrance = A[i].entrance;
        B[P[A[i].value]].exit = A[i].exit;
        P[A[i].value]++;
    }

    for  (int i = 0; i < m; i ++){
        A[i].value = B[i].value;
        A[i].entrance = B[i].entrance;
        A[i].exit = B[i].exit;
    }

    delete[] B;
    delete[] P;

}


void Inizialize_Vertexes(int* & arrColors, const int & n){

    for (int i = 0; i <= n; ++i){
        arrColors[i] = i;
    }
}

void Inizialize_Edges (Edge* & arrE, int* & arrColors, const int & m){
    for (int i = 0; i < m; i++){
        cin >> arrE[i].entrance >> arrE[i].exit >> arrE[i].value;
        arrE[i].MST = false;
    }
}

void UnionColor (int* & arrColors, const int & u, const int & v, const int & n){
    int newColor = arrColors[u];
    int oldColor = arrColors[v];
    for (int i = 0; i <= n; i++) {
        if (arrColors[i] == oldColor) arrColors[i] = newColor;
    }
}


void Kruskal_MST(Edge* & arrE, int* & arrColors, const int & n, const int & m){
    int maxRequiredEdges = n - 1, MST_EdgesCounter = 0;
    CountingSort(arrE, m);
    //QSort (arrE, 0, m - 1);

    //цикл для прохода по всем ребрам
    for (int i = 0; i < m; ++i) {
        int u = arrE[i].entrance;
        int v = arrE[i].exit;
        if (arrColors[u] != arrColors[v]) { //проверка на цикл
            arrE[i].MST = true;
            MST_EdgesCounter++;
            UnionColor(arrColors, u, v, n);
            if (MST_EdgesCounter >= maxRequiredEdges) break;
        }
    }
}

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("spantree3.in", "r", stdin);
    freopen("spantree3.out", "w", stdout);
    
    int n, m;
    cin >> n >> m;

    int* arrColors = new int [n+1];
    //Vertex* arrV = new Vertex[n + 1];
    Edge* arrE = new Edge[m];
    Inizialize_Vertexes(arrColors, n);
    Inizialize_Edges (arrE, arrColors, m);

    Kruskal_MST(arrE, arrColors, n, m);
    
    long long int result = 0;
    for (int i = 0; i < m; ++i) {
        if (arrE[i].MST) result += arrE[i].value;
    }


    cout << result;

    delete [] arrE;
    delete [] arrColors;
   
    return 0;
}
