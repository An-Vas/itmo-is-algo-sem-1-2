#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main ()
{

    freopen("turtle.in", "r", stdin);
    freopen("turtle.out", "w", stdout);
    int h,w;
    cin>>h>>w;

    double field[h][w];
    double maxReward[h][w];

    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            cin >> field[i][j];
            maxReward[i][j]=0;
        }
    }

    //��������� ������
    maxReward[h-1][0] = field [h-1][0];

    //������ �� ����� �������� ����� ����
    for (int i = h - 2; i >= 0; i--){
        maxReward[i][0] = maxReward[i + 1][0] + field [i][0];
    }

    //������ �� ������ �������� ����� �������
    for (int j = 1; j < w; j++){
        maxReward[h-1][j] = maxReward[h-1][j - 1] + field [h-1][j];
    }


    //��������� ������
    for (int i = h - 2; i >= 0; i--){ //������ ����� �����
        for (int j = 1; j <= w - 1; j++){ //������� (����� ������� � ������) ����� �������
            int max; //������� ������������ �����, ������� ����� ���� �������� �� ������� � ������� ������
            if (maxReward[i+1][j]>maxReward[i][j-1]){
                max = maxReward[i+1][j];
            } else {
            max = maxReward[i][j-1];
            }

            maxReward[i][j] = max + field[i][j];
        }
    }

    cout << maxReward[0][w - 1];
    return 0;
}
