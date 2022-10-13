#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

int main ()
{
    freopen("garland.in", "r", stdin);
    freopen("garland.out", "w", stdout);

    int n;
    double a;
    cin>>n>>a;

    double left = 0;
    double right = a;
    double result = -1;

    while (true){
        double mid = (right + left)/2;
        if (mid == left || mid == right){
            break;
        }
        double prevHLamp = a;
        double curHLamp = mid;
        int lampsOnGround = 0;

        for (int i = 3; i <= n; i++){
            double nextHLamp = 2 * curHLamp - prevHLamp + 2;
            if (nextHLamp == 0){lampsOnGround++;}
            if (nextHLamp < 0){lampsOnGround = 100;} //just big number, nothing special
            prevHLamp = curHLamp;
            curHLamp = nextHLamp;
        }
        if (lampsOnGround <= 1) {
            right = mid;
            result = curHLamp;
        } else if (lampsOnGround > 1) {
            left = mid;
        }

    }
    cout<<fixed<<setprecision(2);
    cout<<result;

    return 0;

}
