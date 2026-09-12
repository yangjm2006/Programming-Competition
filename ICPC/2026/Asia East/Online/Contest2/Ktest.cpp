#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    ll T = 1, n = 5000, q = 5000;
    cout << T << endl;
    cout << n << endl;
    for (ll i = 1; i <= n; i++) {
        cout << i - 1 << " ";
    }
    cout << endl;
    cout << q << endl;
    for (ll i = 1; i <= q; i++) {
        cout << i << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    while (t--) {
        solve();
    }

    return 0;
}