#include <bits/stdc++.h>
using namespace std;

#define int long long
#define PII pair<int, int>
const int N = 2e5 + 10;
const int INF = 1e17;

int n, m;
struct Edge {
    int v, w, eid;
};
vector<Edge> e[N];
int vis[N], vis2[N];
int ans;
int getans(vector<int> vec) {
    // cout << vec.size() << "!!!!!!\n";
    // for (auto x : vec) {
    // cout << x << " ";
    // }
    // cout << "\n";
    sort(vec.begin(), vec.end());
    if (vec.size() == 2)
        return vec[0] + vec[1];
    return min(vec[0] + vec[1], vec[2]);
}
vector<Edge> vec;
void dfs(int u, int Eid) {
    vis[u] = -1;
    for (auto [v, w, eid] : e[u]) {
        if (eid == Eid)
            continue;
        if (vis2[eid])
            continue;
        vec.push_back(Edge{u, w, eid});
        if (vis[v] == 0) {
            dfs(v, eid);
        } else {
            vector<int> yjm;
            for (int i = vec.size() - 1; i >= 0; i--) {
                yjm.push_back(vec[i].w);
                vis2[vec[i].eid] = 1;
                if (vec[i].v == v)
                    break;
            }
            // cout << getans(yjm) << "??\n";
            ans = min(ans, getans(yjm));
        }
        vec.pop_back();
    }
}
int val[N];
void solve() {
    cin >> n >> m;
    for (int i = 1; i <= max(n, m); i++) {
        e[i].clear();
        vis[i] = vis2[i] = 0;
    }
    ans = INF;
    vec.clear();
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].push_back(Edge{v, w, i});
        e[v].push_back(Edge{u, w, i});
        val[i] = w;
    }
    dfs(1, 0);
    for (int i = 1; i <= m; i++) {
        if (vis2[i] == 0) {
            ans = min(ans, val[i]);
            // cout << i << "??\n";
        }
    }
    cout << ans << '\n';
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
