#include <iostream>
#include <iomanip>
using namespace std;

int main()
{   long long a, b;
    freopen("aplusbb.in", "r", stdin);
    freopen("aplusbb.out", "w", stdout);
    cin >> a >> b;
    cout << fixed << setprecision(0);
    cout << b * b + a  << endl;
    return 0;
}
