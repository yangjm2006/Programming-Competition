#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    ll n, m;
    string s;
    cin >> n >> m >> s;
    string s1 = s.substr(0, 2);
    // cout << s1 << endl;
    if (m >= 50 || 5 * m >= n || (s1 == "04" || s1 == "05")) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}