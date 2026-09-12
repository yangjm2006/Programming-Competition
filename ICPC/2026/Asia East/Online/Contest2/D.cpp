#include <bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int, int>

int n, q;
int a[1000005];
int siz[1000005];
int nn;
int b[1000005];
const int p = 998244353;
int fac[1000005];
int ifac[1000005];
int m2[1000005];

int ksm(int a, int b) {
    int ans = 1;
    while (b > 0) {
        if ((b & 1) == 1) {
            ans *= a;
            ans %= p;
        }
        b >>= 1;
        a *= a;
        a %= p;
    }
    return ans;
}

int inc(int x) { return ksm(x, p - 2); }

int C(int n, int m) {
    if (m < 0 || n < 0 || n - m < 0)
        return 0;
    if (m == 0)
        return 1;
    return fac[n] * ifac[m] % p * ifac[n - m] % p;
}

int mmax[1000005];

int dfs(int x) {
    int ls = 2 * x, rs = 2 * x + 1;
    if (rs <= nn) {
        int d1 = dfs(ls);
        int d2 = dfs(rs);
        if (d1 == 0 || d2 == 0) {
            return 0;
        }
        mmax[x] = max(mmax[ls], mmax[rs]);
        if (a[ls] != -1 && a[rs] != -1) {
            int ans = max(a[ls], a[rs]);
            if (a[x] != -1 && ans != a[x]) {
                return 0;
            }
            a[x] = ans;
        }
        if (mmax[x] > a[x] && a[x] != -1) {
            return 0;
        }
    } else {
        mmax[x] = a[x];
    }
    return 1;
}

bool cmp(PII a, PII b) {
    if (a.second == b.second) {
        return a.first > b.first;
    }
    return a.second < b.second;
}

void solve() {
    cin >> n >> q;

    for (int i = 0; i <= 1000000; i++) {
        a[i] = -1;
    }
    nn = m2[n + 1] - 1;

    for (int i = nn; i >= 1; i--) {
        if (2 * i > nn) {
            siz[i] = 1;
        } else {
            siz[i] = siz[2 * i] + siz[2 * i + 1];
        }
    }

    vector<PII> qq;
    int f1 = 0;
    while (q--) {
        int v, x;
        cin >> v >> x;
        int t1 = m2[n] - 1;
        if (a[v] != -1 && a[v] != x) {
            f1 = 1;
        }
        if (v <= t1) {
            a[v] = x;
            qq.push_back({v, x});
        } else {
            a[v] = x;
            if (b[x] != 0 && b[x] != v) {
                f1 = 1;
            }
            if (b[x] == 0) {
                b[x] = v;
                int now = v;
                while (now >= 1) {
                    siz[now]--;
                    now /= 2;
                }
            }
        }
    }
    if (f1) {
        cout << 0;
        return;
    }

    int it = 1, sum = 0;

    int d1 = dfs(1);
    if (d1 == 0) {
        cout << 0 << endl;
        return;
    }
    int ans = 1;
    sort(qq.begin(), qq.end(), cmp);
    for (auto [v, x] : qq) {
        while (it < x) {
            if (b[it] == 0) {
                sum++;
            }
            it++;
        }
        int ll = v, rr = v;
        while (ll * 2 <= nn) {
            ll *= 2;
            rr = 2 * rr + 1;
        }
        if (b[x] != 0) { // you
            int pos = b[x];
            if (pos >= ll && pos <= rr) {
                // you

                int ss = siz[v];

                ans *= C(sum, ss) % p * fac[ss] % p;
                ans %= p;
                sum -= ss;

                if (sum < 0) {
                    cout << 0;
                    return;
                }

                int now = v;
                while (now >= 1) {
                    siz[now] -= ss;
                    now /= 2;
                }
            } else {
                cout << 0;
                return;
            }
        } else {
            int ss = siz[v];

            ans *= C(sum, ss - 1) % p * fac[ss] % p;
            ans %= p;

            sum -= ss - 1;
            if (sum < 0) {
                cout << 0;
                return;
            }

            int now = v;
            while (now >= 1) {
                siz[now] -= ss;
                now /= 2;
            }
            b[x] = ll;
        }
    }
    while (it <= m2[n]) {
        if (b[it] == 0) {
            sum++;
        }
        it++;
    }
    ans *= fac[sum] % p;
    ans %= p;
    cout << ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    fac[0] = 1;
    for (int i = 1; i <= 1000000; i++) {
        fac[i] = fac[i - 1] * i % p;
    }
    ifac[1000000] = ksm(fac[1000000], p - 2);
    for (int i = 1000000 - 1; i >= 0; i--) {
        ifac[i] = ifac[i + 1] * (i + 1) % p;
    }
    m2[0] = 1;
    for (int i = 1; i <= 1000000; i++) {
        m2[i] = 2 * m2[i - 1] % p;
    }
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}