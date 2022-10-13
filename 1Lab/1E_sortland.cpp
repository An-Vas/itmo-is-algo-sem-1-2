#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main ()
{

    freopen("sortland.in", "r", stdin);
    freopen("sortland.out", "w", stdout);
    int n;
    cin>>n;

    vector <double> notSorted(n);
    vector <double> sorted(n);

    for (int i = 0; i<n; i++){
        cin>>notSorted[i];
        sorted[i]=notSorted[i];
    }


    for (int j = 0; j < n; j++) {
        int numMin = j;
        for (int i = j; i < n; i++) {
            if (sorted[i] < sorted[numMin]) {
                numMin = i;
            }
        }

        double temp;
        temp = sorted[j];
        sorted[j] = sorted[numMin];
        sorted[numMin] = temp;
    }



    int numPoor;
    int numMid;
    int numWealthy;



    for (int i = 0; i<n; i++){


        if (notSorted[i] == sorted [0]) {
            numPoor = i+1;
        }
        if (notSorted[i] == sorted [n/2]) {
            numMid = i+1;
        }
        if (notSorted[i] == sorted [n-1]) {
            numWealthy = i+1;
        }
    }

    cout<<numPoor<<" "<<numMid<<" "<<numWealthy;

    return 0;
}
