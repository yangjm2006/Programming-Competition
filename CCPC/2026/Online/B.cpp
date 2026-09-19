#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a[10], b[10], k;
bool check() {
    int sum = 0;
    for (int i = 1; i <= 6; i++)
        for (int j = 1; j <= 6; j++) {
            if (b[j] >= a[i])
                sum++;
            if (sum > 18)
                return 1;
        }
    return 0;
}
void solve() {
    for (int i = 1; i <= 6; i++) {
        cin >> a[i];
        a[i]++;
    }
    a[7] = 1;
    cin >> k;
    for (int k1 = 1; k1 <= 7; k1++) {
        b[1] = a[k1];
        for (int k2 = 1; k2 <= 7; k2++) {
            b[2] = a[k2];
            for (int k3 = 1; k3 <= 7; k3++) {
                b[3] = a[k3];
                for (int k4 = 1; k4 <= 7; k4++) {
                    b[4] = a[k4];
                    for (int k5 = 1; k5 <= 7; k5++) {
                        b[5] = a[k5];
                        b[6] = k - b[1] - b[2] - b[3] - b[4] - b[5];
                        if (b[6] <= 0)
                            continue;
                        if (check()) {
                            cout << "YES\n";
                            for (int i = 1; i <= 6; i++)
                                cout << b[i] << " ";
                            return;
                        }
                    }
                }
            }
        }
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
}