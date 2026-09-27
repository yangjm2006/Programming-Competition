#include <bits/stdc++.h>
using namespace std;

#define int long long
#define PII pair<int, int>

void solve() {
    int n;
    cin >> n;
    int det[10] = {};
    int ans[10] = {};
    int m1 = 0, m2 = 0;
    for (int i = 0; i < 10; i++) {
        vector<int> a;
        vector<int> b;
        for (int num = 1; num <= n; num++) {
            if (((num >> i) & 1) == 1) {
                a.push_back(num);
            } else {
                b.push_back(num);
            }
        }

        string s = "NO";
        if (a.size() != 0) {

            cout << "? " << a.size();
            for (int num : a) {
                cout << " " << num;
            }
            cout << endl;

            cin >> s;
        }

        if (s == "YES") {
            det[i] = 1;
            ans[i] = 1;
        } else {
            s = "NO";
            if (b.size() != 0) {
                cout << "? " << b.size();
                for (int num : b) {
                    cout << " " << num;
                }
                cout << endl;

                cin >> s;
            }
            if (s == "YES") {
                det[i] = 1;
                ans[i] = 0;
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        if (det[i] == 1) {
            if (ans[i] == 1) {
                m1 += (1 << i);
            } else {
                m2 += (1 << i);
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        if (det[i] == 1) {
            continue;
        }

        vector<int> a;
        for (int num = 1; num <= n; num++) {
            int f = 1;
            for (int j = 0; j < 10; j++) {
                if (det[j] == 1) {
                    if (((num >> j) & 1) == ans[j]) {

                    } else {
                        f = 0;
                    }
                }
                if (j == i) {
                    if (((num >> j) & 1) == 1) {

                    } else {
                        f = 0;
                    }
                }
            }
            if (f) {
                a.push_back(num);
            }
        }

        string s = "NO";
        if (a.size() != 0) {

            cout << "? " << a.size();
            for (int num : a) {
                cout << " " << num;
            }
            cout << endl;
            cin >> s;
        }

        det[i] = 1;
        if (s == "YES") {
            ans[i] = 1;
            m1 += (1 << i);
            m2 += (1 << i);
        } else {
            ans[i] = 0;
        }
    }
    cout << "! " << m1 << ' ' << m2 << endl;
}

signed main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}
