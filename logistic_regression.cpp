// https://codefun2000.com/ide/P4344
// 交叉熵
#include <bits/stdc++.h>
using namespace std;

#define Dim 3

double lambda;

double sigmoid(double w[], double x[], double b) {
    double sum = b;
    for (int i = 0; i < Dim; i++) {
        sum += w[i] * x[i];
    }
    return 1 / (1 + exp(- sum));
}

double loss(int n, double p[], double y[], double w[]){
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += - y[i] * log(p[i]) - (1 - y[i]) * log(1 - p[i]);
    }
    sum = sum / (double)n;
    for (int i = 0; i < Dim; i++) {
        sum += lambda * w[i] * w[i] / (2.0 * n);
    }
    return sum;
}

double g_w(int n, int d, double p[], double y[], double x[][Dim], double w) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (p[i] - y[i]) * x[i][d];
    }
    return sum / (double)n + lambda * w / (double)n;
}

double g_b(int n, double p[], double y[]) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (p[i] - y[i]);
    }
    return sum / (double)n; 
}

int main() {
    int n, max_iter;
    double a, tol;
    cin >> n >> max_iter >> a >> lambda >> tol;
    double x[n][Dim], y[n];
    for (int i = 0; i < n; i++) {
        for (int d = 0; d < Dim; d++) {
            cin >> x[i][d];
        }
        cin >> y[i];
    }
    double w[Dim] = {0.0}, b = 0.0;
    int m;
    cin >> m;
    double input[m][Dim];
    for (int i = 0; i < m; i++) {
        for (int d = 0; d < Dim; d++) {
            cin >> input[i][d];
        }
    }
    double l_old = 0;
    for (int iter = 0; iter < max_iter; iter++) {
        // 预测
        double p[n];
        for (int i = 0; i < n; i++) {
            p[i] = sigmoid(w, x[i], b);
        }
        // loss
        double l = loss(n, p, y, w);
        if (abs(l - l_old) < tol) break;
        l_old = l;
        // update
        double gw[Dim], gb;
        for (int d = 0; d < Dim; d++) {
            gw[d] = g_w(n, d, p, y, x, w[d]);
            w[d] = w[d] - a * gw[d];
        }
        gb = g_b(n, p, y);
        b -= a * gb; 
    }
    int cl;
    double output;
    for (int i = 0; i < m; i++){
        output = sigmoid(w, input[i], b);
        cl = output >= 0.5 ? 1 : 0;
        printf("%d %.4f\n",cl, output);
    }
    return 0;
}