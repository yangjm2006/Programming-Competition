#include <bits/stdc++.h>
using namespace std;

#define int long long
#define PII pair<int, int>

bool cmp(int a, int b) { return a < b; }

void solve() {
    int n;
    cin >> n;
    vector<int> a;
    map<int, int> m;
    int mmax = -1;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        mmax = max(mmax, x);
        // a.push_back(x);
        m[x]++;
        if (m[x] > 2) {
            m[x] -= 2;
        }
    }
    for (auto [x, cnt] : m) {
        for (int i = 0; i < cnt; i++) {
            a.push_back(x);
        }
    }
    sort(a.begin(), a.end(), cmp);
    int tot = a.size();

    int ans = 4e18;
    int now = -1;
    int cost = 0;
    for (int i = 0; i < tot; i++) {
        if (now == -1) {
            now = a[i];
        } else {
            if (a[i] == now) {
                now = -1;
            } else {
                cost += a[i] - now;
                now = a[i];
            }
        }
    }
    ans = min(ans, cost);

    if (m[mmax] == 2) {
        int llo = -1;

        now = -1;
        cost = 0;
        for (int i = 0; i < tot; i++) {
            if (now == -1) {
                now = a[i];
            } else {
                if (a[i] == now) {
                    now = -1;
                } else {
                    cost += a[i] - now;
                    llo = max(llo, a[i] - now);
                    now = a[i];
                }
            }
        }
        cost -= llo;
        ans = min(ans, cost);
    }
    cout << ans;
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
