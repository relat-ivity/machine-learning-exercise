// https://codefun2000.com/ide/P3842
#include <bits/stdc++.h>
using namespace std;

struct Anchor{
    int w;
    int h;
    int cl;
};

double iou(Anchor a1, Anchor a2) {
    double i = min(a1.w, a2.w) * min(a1.h, a2.h);
    double u = a1.w * a1.h + a2.w * a2.h - i;
    return 1 - i / (u + 1e-16);
}

int main() {
    int N, K, T;
    cin >> N >> K >> T;
    Anchor a[N], center[K];
    for (int i = 0; i < N; i++) {
        cin >> a[i].w >> a[i].h;
        if (i < K) {
            center[i].w = a[i].w;
            center[i].h = a[i].h;
        }
    }
    // k-means
    for(int iter = 0; iter < T; iter++) {
        // 聚类
        for (int i = 0; i < N; i++) {
            double min_iou = iou(a[i], center[0]);
            a[i].cl = 0; 
            for (int k = 1; k < K; k++) {
                double iou_ = iou(a[i], center[k]);
                if(iou_ < min_iou) {
                    min_iou = iou_;
                    a[i].cl = k; 
                }
            }
        }
        // 更新
        double sum_w[K] = {0}, sum_h[K] = {0};
        int num[K] = {0};
        for (int i = 0; i < N; i++) {
            sum_w[a[i].cl] += a[i].w;
            sum_h[a[i].cl] += a[i].h;
            num[a[i].cl]++;
        }
        // 迭代
        double sum = 0;
        for (int k = 0; k < K; k++) {
            Anchor new_center = { (int)(sum_w[k] / num[k]), (int)(sum_h[k] / num[k])};
            sum += iou(new_center, center[k]);
            center[k].w = new_center.w;
            center[k].h = new_center.h;
        }
        if (sum < 1e-4) break;
    }
    // 排序
    for (int i = 0; i < K; i++) {
        for (int j = i; j < K; j++) {
            if (center[i].w * center[i].h < center[j].w * center[j].h) {
                int wi = center[i].w;
                int hi = center[i].h;
                center[i].w = center[j].w;
                center[i].h = center[j].h;
                center[j].w = wi;
                center[j].h = hi;
            }
        }
    }
    // 输出
    for (int k = 0; k < K; k++) {
        cout << center[k].w << " " << center[k].h << endl;
    }
    return 0;
}