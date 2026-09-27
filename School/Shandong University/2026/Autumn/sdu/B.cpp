#include <bits/stdc++.h>
using namespace std;

#define int long long
#define PII pair<int, int>

bool cmp(PII a, PII b) { return a.first < b.first; }

void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    vector<PII> aa;
    aa.push_back({a, 1});
    aa.push_back({b, 2});
    aa.push_back({c, 3});
    sort(aa.begin(), aa.end());
    a = aa[2].first;
    b = aa[1].first;
    c = aa[0].first;

    cout << aa[1].first * aa[2].first << "\n";

    int m[a + 1][b + 1];
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            m[i][j] = (i + j - 1 - 1) % c + 1;
            int tmp[4];
            tmp[aa[2].second] = i;
            tmp[aa[1].second] = j;
            tmp[aa[0].second] = m[i][j];
            cout << tmp[1] << ' ' << tmp[2] << ' ' << tmp[3] << "\n";
        }
    }
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
