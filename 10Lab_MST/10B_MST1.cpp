#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

class Vertex {
    public:
    short int x;
    short int y;
    short int color;
    
};

class Edge {
    public:
    float value;
    short int entrance;
    short int exit;
    bool MST;
};

void QSort (Edge* & a, int left, int right){
     int lPointer, rPointer, tempEx, tempEn;
     float key, tempVal;
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

double distance (const int & x1, const int & y1, const int & x2, const int & y2){
    return sqrt(pow((x1 - x2),2)+pow((y1 - y2),2));
}

void Inizialize_Vertexes(Vertex* & arrV, const int & n){

    for (int i = 0; i < n; ++i){
        cin >> arrV[i].x >> arrV[i].y ;
        arrV[i].color = i;
    }
}

void Inizialize_Edges (Edge* & arrE, Vertex* & arrV, const int & n){
    int k = 0;
    for (int i = 0; i < n; i ++){
        for (int j = i+1; j < n; j++){
            arrE[k].value = distance(arrV[i].x, arrV[i].y, arrV[j].x, arrV[j].y);
            arrE[k].entrance = i;
            arrE[k].exit = j;
            arrE[k].MST = false;
            k++;
        }
    }
}

void UnionColor (Vertex* & arrV, const int & u, const int & v, const int & n){
    int newColor = arrV[u].color;
    int oldColor = arrV[v].color;
    for (int i = 0; i < n; i++) {
        if (arrV[i].color == oldColor) arrV[i].color = newColor;
    }
}


void Kruskal_MST(Edge* & arrE, Vertex* & arrV, const int & n){
    short int maxRequiredEdges = n - 1, MST_EdgesCounter = 0;
    QSort (arrE, 0, (n*(n-1))/2 - 1);

    //цикл для прохода по всем ребрам
    for (int i = 0; i < (n*(n-1))/2; ++i) {
        int u = arrE[i].entrance;
        int v = arrE[i].exit;
        if (arrV[u].color != arrV[v].color) { //проверка на цикл
            arrE[i].MST = true;
            MST_EdgesCounter++;
            UnionColor(arrV, u, v, n);
            if (MST_EdgesCounter > maxRequiredEdges) break;
        }
    }
}

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    freopen("spantree.in", "r", stdin);
    freopen("spantree.out", "w", stdout);
    
    short int n;
    cin >> n;

    Vertex* arrV = new Vertex[n];
    Edge* arrE = new Edge[(n*(n-1))/2];
    Inizialize_Vertexes(arrV, n);
    Inizialize_Edges (arrE, arrV, n);

    Kruskal_MST(arrE, arrV, n);
    
    double result = 0;
    for (int i = 0; i < (n*(n-1))/2; ++i) {
        if (arrE[i].MST) result += arrE[i].value;
    }
    cout << fixed << setprecision (20) << result;
    
    delete [] arrE;
    delete [] arrV;
   
    return 0;
}
