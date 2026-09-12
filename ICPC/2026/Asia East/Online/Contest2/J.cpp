#include <bits/stdc++.h>
using namespace std;
#define int long long

const string rev[] = {"WrongProblem",
                      "SameProblem",
                      "UnreasonableProblemArrangement",
                      "UnreasonableLimitForProblem",
                      "WeakTestsForProblem",
                      "BadProblem"};

const int poi[] = {100, 30, 10, 5, 3, 1};

void solve() {
    int n, p;
    cin >> n >> p;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        string tmp;
        char c;
        cin >> tmp;
        if (tmp == rev[2]) {
            ans += poi[2];
        } else {
            c = tmp.back();
            tmp.pop_back();
            if (c >= 'A' && c <= 'L') {
                for (int j = 0; j <= 5; j++) {
                    if (j == 2) {
                        continue;
                    }
                    if (tmp == rev[j]) {
                        ans += poi[j];
                    }
                }
            }
        }
    }
    // cout << ans << endl;
    if (ans > p) {
        cout << "Joker" << endl;
    } else {
        cout << "Judger" << endl;
    }
}

signed main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}