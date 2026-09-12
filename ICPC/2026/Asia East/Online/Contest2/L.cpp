#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int n;
    cin >> n;
    int a[n + 5];
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int ans = n * a[1] + (n - 1) * a[2];
    ans = min(ans, (n * a[1] + (n - 1) * a[n]));

    int b[n + 5] = {};
    for (int i = 1; i <= n; i++) {
        b[i] = b[i - 1] + a[i];
    }

    for (int i = 1; i <= n - 2; i++) {
        int temp = 0;
        // for (int j = 1; j <= i; j++) {
        //     temp += a[j];
        // }
        temp += b[i];
        temp *= 2;
        temp += (n - i) * a[1 + i] + (n - 1 - i) * a[2 + i];
        ans = min(ans, temp);
    }
    for (int i = 1; i <= n - 2; i++) {
        int temp = 0;
        // for (int j = 1; j <= i; j++) {
        //     if (j == 1)
        //         temp += a[1];
        //     else {
        //         temp += a[n - j + 2];
        //     }
        // }
        temp += a[1];
        temp += b[n] - b[n - i + 1];
        temp *= 2;
        temp += (n - i) * a[n - i + 1] + (n - 1 - i) * a[n - i];
        ans = min(ans, temp);
    }
    cout << ans << endl;
}

signed main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}