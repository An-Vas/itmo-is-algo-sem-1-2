#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main ()
{

  freopen("smallsort.in", "r", stdin);
  freopen("smallsort.out", "w", stdout);

  int n;
    cin >> n;
    vector <int> a (n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        }

    for (int j = 0; j < n; j++) {
        int numMin = j;
        for (int i = j; i < n; i++) {
            if (a[i] < a[numMin]) {
                numMin = i;
            }
        }

        int temp;
        temp = a[j];
        a[j] = a[numMin];
        a[numMin] = temp;
    }

    for (int i=0; i<n; i++) {
        cout << a[i] << " ";
    }

      return 0;
}
