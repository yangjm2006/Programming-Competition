#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    vector<int> aa;
    aa.push_back(a);
    aa.push_back(b);
    aa.push_back(c);
    sort(aa.begin(), aa.end());
    cout << aa[1] * aa[2] << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {

        solve();
    }
    return 0;
}
