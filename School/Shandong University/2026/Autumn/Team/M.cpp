#include <bits/stdc++.h>
using namespace std;

#define int long long
#define PII pair<int, int>
const int N = 2e5 + 10;

int n, m;
vector<int> e[N];
int dn, dfn[N], low[N], stc[N], top, cn;
vector<int> ans[N];
void minn(int &x, int y) {
    if (y < x)
        x = y;
}
void tj(int u) {
    dfn[u] = low[u] = ++dn;
    stc[++top] = u;
    for (int v : e[u]) {
        if (!dfn[v]) {
            tj(v);
            minn(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                cn++;
                do {
                    ans[cn].push_back(stc[top]);
                } while (stc[top--] != v);
                ans[cn].push_back(u);
            } else {
                minn(low[u], low[v]);
            }
        }
    }
}
void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].push_back(v);
        e[v].push_back(u);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
