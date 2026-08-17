// https://codefun2000.com/ide/P4532
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N; 
    double w[4] = {0};
    double x[N][4], y[N];
    for (int i = 0; i < N; i++) {
        cin >> x[i][0] >> x[i][1] >> x[i][2] >> y[i];
        x[i][3] = 1;
    }
    int K;
    cin >> K;
    double input[K][4];
    for (int i = 0; i < K; i++) { 
        cin >> input[i][0] >> input[i][1] >> input[i][2];
        input[i][3] = 1;
    }
    double lw[4][5] = {0};
    // 偏导矩阵
    for (int i = 0; i < N; i++) {
        for (int di = 0; di < 4; di++) {
            for (int dj = 0; dj < 4; dj++) {
                lw[di][dj] += x[i][di] * x[i][dj];
            }
            lw[di][4] += x[i][di] * y[i];
        }
    }
    // 高斯消元
    for (int i = 0; i < 4; i++) {
        // 第i位变1
        double lwi = lw[i][i];
        for (int j = 0; j < 5; j++) {
            lw[i][j] /= lwi;
        }
        // 消元
        for (int j = 0; j < 4; j++) {
            if (i != j) {
                double bit = lw[j][i]; 
                for (int k = 0; k < 5; k++) {
                    lw[j][k] -= bit * lw[i][k];
                }
            }
        }
    }
    // 得解
    for (int i = 0; i < 4; i++) {
        w[i] = lw[i][4];
    }
    // 预测
    for (int i = 0; i < K; i++) {
        double output = 0;
        for (int d = 0; d < 4; d++) {
            output += w[d] * input[i][d];
        }
        cout << round(output) << " ";
    }
    return 0;
}