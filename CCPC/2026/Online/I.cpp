#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    ll n;
    cin >> n;
    if (n % 2) {
        cout << -1 << endl;
    } else {
        cout << n / 2 << " 1 -1" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}