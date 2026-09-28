#include <bits/stdc++.h>
using namespace std;

#define int __int128_t
#define ll long long
#define PII pair<int, int>

ll p, q, k;
vector<ll> ans;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int d;
void solve2() {
    if (d == 1) {
        ans.push_back(1);
        return;
    }
    ll a, b;
    cin >> a >> b;
    int k1 = a / q;
    int k2 = a % q;
    // int x = a;
    k1 %= d;
    // map<int, int> cnt;
    map<int, vector<int>> m;
    map<PII, int> vis;
    int aans = 0;
    while (1) {
        int md = k2;
        if (vis[{k1, k2}] == 3) {
            break;
        }
        int ff = 0;
        vis[{k1, k2}]++;
        //
        //
        for (int n1 : m[md]) {
            if (gcd(((k1 - n1) % d + d) % d, d) == 1) {
                ff = 1;
                aans = 1;
                break;
            }
        }
        if (ff) {
            break;
        }
        m[md].push_back(k1);
        //
        int nk1 = (k1 * k1 % d * q) % d + 2 * k1 % d * k2 % d;
        int nk2 = (k2 * k2 + b);
        nk1 += nk2 / q;
        nk2 = nk2 % q;
        k1 = nk1 % d;
        k2 = nk2;
    }
    int ff = 0;
    for (auto [md, v] : m) {
        for (int i = 0; i < v.size(); i++) {
            for (int j = i + 1; j < v.size(); j++) {
                if (gcd(((v[j] - v[i]) % d + d) % d, d) == 1) {
                    aans = 1;
                    ff = 1;
                    break;
                }
            }
            if (ff) {
                break;
            }
        }
        if (ff) {
            break;
        }
    }
    ans.push_back((ll)(aans));
}

void solve() {
    cin >> p >> q >> k;
    d = p / q;
    while (k--) {
        solve2();
    }
    for (ll c : ans) {
        cout << c;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
