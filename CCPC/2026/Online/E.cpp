#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 10;

mt19937_64 rnd(198372983ll);

ll s[N];

void solve() {
    ll n;
    cin >> n;
    set<ll> ans;
    ll a[n + 10], b[n + 10], c[n + 10];
    for (ll i = 1, x; i <= n; i++) {
        cin >> x;
        a[i] = s[x];
    }
    for (ll i = 1, x; i <= n; i++) {
        cin >> x;
        b[i] = s[x];
    }
    for (ll i = 1, x; i <= n; i++) {
        cin >> x;
        c[i] = s[x];
    }
    ll L = 0, R = 0;
    for (ll i = 1; i <= n; i++) {
        L ^= a[i];
        R ^= b[i];
        if (L == R) {
            ans.insert(i);
        }
    }
    L = 0, R = 0;
    for (ll i = 1; i <= n; i++) {
        L ^= b[i];
        R ^= c[i];
        if (L == R) {
            ans.insert(i);
        }
    }
    L = 0, R = 0;
    for (ll i = 1; i <= n; i++) {
        L ^= a[i];
        R ^= c[i];
        if (L == R) {
            ans.insert(i);
        }
    }
    cout << ans.size() << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    for (ll i = 1; i <= 200000; i++) {
        s[i] = rnd();
    }
    while (t--) {
        solve();
    }
}