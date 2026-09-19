#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
const int inf = 4e18;

void solve() {
    int w, x[3], y, u, v;
    cin >> w >> x[1] >> x[2] >> y >> u >> v;
    double t = (double)y / v;
    double xx1 = x[1] + u * t;
    double xx2 = x[2] + u * t;
    if (xx1 >= 0 || xx2 <= 0) {
        double ans = (double)w / v;
        printf("%.9f\n", ans);
        return;
    }
    double ans = inf;
    for (int i = 1; i <= 2; i++) {
        double a, b, c;
        a = u * u - v * v;
        b = 2 * x[i] * u;
        c = x[i] * x[i] + y * y;
        double delt = b * b - 4 * a * c;
        if (fabs(delt) < 0.00000000001) {
            delt = 0;
        }
        if (fabs(a) < 0.00000000001) {
            double t1, t2;
            t1 = -c / b;
            if (t1 > 0) {

                ans = min(t1 + ((double)w - y) / v, ans);
            }
            continue;
        }
        if (delt >= 0) {
            double t1, t2;
            t1 = (-b + sqrt(delt)) / 2 / a;
            t2 = (-b - sqrt(delt)) / 2 / a;

            // printf("%.9f %.9f\n", t1, t2);
            if (t1 > 0) {
                ans = min(t1 + ((double)w - y) / v, ans);
            }
            if (t2 > 0) {
                ans = min(t2 + ((double)w - y) / v, ans);
            }
        }
    }
    printf("%.9f\n", ans);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}