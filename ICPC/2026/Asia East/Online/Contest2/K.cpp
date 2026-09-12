#include <bits/stdc++.h>
using namespace std;
#define ll int

ll myhash(ll x) { return x % 100007; }
ll A[100010];

void solve() {
    ll n, q, cur = 0, ouput = 0;
    cin >> n;
    unordered_map<ll, ll> B, ans;
    for (ll i = 1, t; i <= n; i++) {
        cin >> t;
        B[t]++;
    }
    for (ll i = 0; i <= n; i++) {
        if (B.count(i)) {
            cur++;
            B[i]--;
            if (B[i] <= 0) {
                B.erase(i);
            }
        } else {
            break;
        }
    }
    vector<ll> temp;
    for (auto &[val, qqq] : B) {
        temp.push_back(val);
        A[myhash(val)] = qqq;
    }
    vector<ll> del;
    for (auto &val : temp) {
        del.clear();
        ll k = cur + val;
        ll kcur = cur;
        for (ll i = cur; i <= n; i++) {
            if (A[myhash(i)] >= 1) {
                kcur++;
                A[myhash(i)]--;
                del.push_back(i);
            } else if (k - i >= 0 && A[myhash(k - i)] >= 1) {
                kcur++;
                A[myhash(k - i)]--;
                del.push_back(k - i);
            } else {
                break;
            }
        }
        for (auto &i : del) {
            A[myhash(i)]++;
        }
        ans[k] = kcur;
    }
    for (auto &val : temp) {
        A[myhash(val)] = 0;
    }
    cin >> q;
    for (ll i = 1, t; i <= q; i++) {
        cin >> t;
        if (ans.count(t)) {
            ouput ^= ans[t];
            // cout << ans[t] << " ";
        } else {
            ouput ^= cur;
            // cout << cur << " ";
        }
    }
    cout << ouput << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

// #include <bits/stdc++.h>
// using namespace std;
// #define ll int

// struct Hash {
//     size_t operator()(const ll &v) const {
//         size_t h = v * 1317ll % 100007;
//         return h;
//     }
// };

// void solve() {
//     ll n, q, cur = 0, ouput = 0;
//     cin >> n;
//     unordered_map<ll, ll, Hash> A, ans;
//     for (ll i = 1, t; i <= n; i++) {
//         cin >> t;
//         A[t]++;
//     }
//     for (ll i = 0; i <= n; i++) {
//         if (A.count(i)) {
//             cur++;
//             int temp1 = A[i]--;
//             if (temp1 == 1) {
//                 A.erase(i);
//             }
//         } else {
//             break;
//         }
//     }
//     vector<ll> temp;
//     for (auto &[val, qqq] : A) {
//         temp.push_back(val);
//     }
//     vector<ll> del;
//     for (auto &val : temp) {
//         del.clear();
//         ll k = cur + val;
//         ll kcur = cur;
//         for (ll i = cur; i <= n; i++) {
//             if (A.count(i)) {
//                 kcur++;
//                 int temp1 = A[i]--;
//                 del.push_back(i);
//                 if (temp1 == 1) {
//                     A.erase(i);
//                 }
//             } else if (A.count(k - i)) {
//                 kcur++;
//                 int temp1 = A[k - i]--;
//                 del.push_back(k - i);
//                 if (temp1 == 1) {
//                     A.erase(k - i);
//                 }
//             } else {
//                 break;
//             }
//         }
//         for (auto &i : del) {
//             A[i]++;
//         }
//         ans[k] = kcur;
//     }
//     cin >> q;
//     for (ll i = 1, t; i <= q; i++) {
//         cin >> t;
//         if (ans.count(t)) {
//             ouput ^= ans[t];
//             // cout << ans[t] << " ";
//         } else {
//             ouput ^= cur;
//             // cout << cur << " ";
//         }
//     }
//     cout << ouput << "\n";
// }

// signed main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     cout.tie(nullptr);
//     int t;
//     cin >> t;
//     while (t--) {
//         solve();
//     }

//     return 0;
// }