#include <bits/stdc++.h>
using namespace std;
typedef int ll;
const ll N = 2e3 + 10;

ll n, t[N];
ll lb(ll x) { return x & -x; }
void add(ll x, ll k) {
    for (ll i = x; i <= n; i += lb(i)) {
        t[i] += k;
    }
}
ll query(ll x) {
    ll ret = 0;
    for (ll i = x; i >= 1; i -= lb(i)) {
        ret += t[i];
    }
    return ret;
}

ll check(ll *a) {
    ll cnt = 0;
    memset(t, 0, sizeof(t));
    for (ll i = n; i >= 1; i--) {
        cnt += query(a[i]);
        add(a[i], 1);
    }
    return cnt % 2;
}

void solve() {
    string s;
    cin >> s >> n;
    if (s == "first") {
        ll a[n + 10];
        for (ll i = 1; i <= n; i++) {
            cin >> a[i];
            cout << a[i] << " ";
        }
        cout << endl;
        ll jud = check(a), cnt = 0;
        // cout << jud << endl;
        ll s[2 * n + 10][n + 10];
        for (ll i = 1; i <= n; i++) {
            a[i] = i;
        }
        cnt++;
        for (ll j = 1; j <= n; j++) {
            s[cnt][j] = a[j];
        }
        for (ll i = 1; i <= n - 1; i++) {
            swap(a[i], a[i + 1]);
            cnt++;
            for (ll j = 1; j <= n; j++) {
                s[cnt][j] = a[j];
            }
            if (cnt > 2 * n) {
                break;
            }
        }
        for (ll i = 1; i <= n - 1; i++) {
            swap(a[i], a[i + 1]);
            cnt++;
            for (ll j = 1; j <= n; j++) {
                s[cnt][j] = a[j];
            }
            if (cnt > 2 * n) {
                break;
            }
        }
        for (ll i = 1; i <= n - 1; i++) {
            swap(a[i], a[i + 1]);
            cnt++;
            for (ll j = 1; j <= n; j++) {
                s[cnt][j] = a[j];
            }
            if (cnt > 2 * n) {
                break;
            }
        }

        if (jud == 1) {
            // cout << "ok" << endl;
            for (ll i = 1; i <= n * 2 - 2; i += 2) {
                for (ll j = 1; j <= n; j++) {
                    cout << s[i][j] << " ";
                }
                cout << endl;
            }
        } else {
            for (ll i = 2; i <= n * 2 - 2; i += 2) {
                for (ll j = 1; j <= n; j++) {
                    cout << s[i][j] << " ";
                }
                cout << endl;
            }
        }

    } else {
        ll s[n + 10][n + 10], cnt0 = 0, cnt1 = 0, p0 = 0, p1 = 0;
        ll *p[n + 10];
        for (ll i = 1; i <= n; i++) {
            p[i] = s[i];
        }
        for (ll i = 1; i <= n; i++) {
            for (ll j = 1; j <= n; j++) {
                cin >> s[i][j];
            }
            if (check(p[i]) == 0) {
                cnt0++;
                p0 = i;
            } else {
                cnt1++;
                p1 = i;
            }
            // cout << check(p[i]) << endl;
        }
        if (cnt0 == 1) {
            for (ll i = 1; i <= n; i++) {
                cout << s[p0][i] << " ";
            }
            cout << endl;
        } else {
            for (ll i = 1; i <= n; i++) {
                cout << s[p1][i] << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    while (t--) {
        solve();
    }
}