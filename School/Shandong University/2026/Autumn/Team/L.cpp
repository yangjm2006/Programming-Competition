#include <bits/stdc++.h>
using namespace std;

#define int long long

#define PII pair<int, int>

void solve() {
    string s[4];
    cin >> s[1] >> s[2] >> s[3];
    int m;
    cin >> m;
    int a[4][4];
    for (int i = 1; i <= 3; i++) {
        a[i][1] = s[i][0] - '0';
        a[i][2] = s[i][1] - '0';
        a[i][3] = s[i][2] - '0';
        // cout << a[i][1] << endl;
        // cout << a[i][2] << endl;
        // cout << a[i][3] << endl;
    }
    int x = 0, y = 0, z = 0;
    for (int i = 1; i <= 3; i++) {
        x += a[1][i];
    }
    for (int i = 1; i <= 3; i++) {
        y += a[2][i];
    }
    for (int i = 1; i <= 3; i++) {
        z += a[3][i];
    }

    if (m % 3 >= 1) {
        x += a[1][1] - a[1][2];
        y += a[2][1] - a[2][2];
        z += a[3][1] - a[3][2];
    }
    if (m % 3 >= 2) {
        x += a[1][2] - a[1][3];
        y += a[2][2] - a[2][3];
        z += a[3][2] - a[3][3];
    }
    cout << (int)x << ' ' << (int)y << ' ' << (int)z;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}
