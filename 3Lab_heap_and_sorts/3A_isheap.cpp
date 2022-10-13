#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    //freopen("isheap.in", "r", stdin);
    //freopen("isheap.out", "w", stdout);

    int n;
    cin >> n;
    bool isHeap = true;

    vector <long long> a (n+1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++){
        if ((2*i <= n) && !(a[i]<=a[2*i])){ isHeap = false; break;}
        if ((2*i + 1 <= n) && !(a[i]<=a[2*i + 1])) {isHeap = false; break;}

    }

    if (isHeap == true) {
        cout<<"YES";
    } else {
        cout<<"NO";
    }


    return 0;

}
