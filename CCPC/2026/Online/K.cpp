#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const ll INF = 1e18;
const int N = 2e5 + 100;
ll ksm(ll a, ll b) {
    ll ans = 1;
    while (b > 0) {
        if ((b & 1) == 1) {
            ans *= a;
            ans %= mod;
        }
        b >>= 1;
        a *= a;
        a %= mod;
    }
    return ans;
}
ll inv(ll x) { return ksm(x, mod - 2); }
struct Edge {
    int v;
    ll w;
    bool is_short;
};
struct Node {
    int u;
    ll d;
    bool operator<(const Node &other) const { return d > other.d; }
};
vector<Edge> e[N];
bool vis[N];
ll ans[N], cnt1[N], cnt2[N];
ll dis[N];
int n, m, T;
void dij() {
    priority_queue<Node> q;
    for (int i = 1; i <= n; i++)
        dis[i] = INF;
    dis[T] = 0;
    cnt1[T] = 1;
    q.push(Node{T, 0});
    while (!q.empty()) {
        int u = q.top().u;
        ll d = q.top().d;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = 1;
        for (auto &[v, w, is_short] : e[u]) {
            if (dis[v] > d + w) {
                dis[v] = d + w;
                q.push(Node{v, d + w});
                cnt1[v] = cnt1[u];
            } else if (dis[v] == d + w) {
                cnt1[v] += cnt1[u];
            }
            cnt1[v] %= mod;
        }
    }
}
int in[N];
bool xh[N];
void solve() {
    cin >> n >> m >> T;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        if (c == '1')
            xh[i] = 1;
        else
            xh[i] = 0;
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        e[v].push_back(Edge{u, w});
        in[u]++;
    }
    dij();
    for (int u = 1; u <= n; u++) {
        for (auto &[v, w, is_short] : e[u]) {
            if (dis[v] == dis[u] + w) {
                is_short = 1;
            }
            cnt2[v]++;
        }
    }
    // for (int i = 1; i <= n; i++) {
    //     cout << i << ": " << cnt1[i] << " " << cnt2[i] << "\n";
    // }
    queue<int> q;
    q.push(T);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w, is_short] : e[u]) {
            in[v]--;
            if (xh[v] && is_short) {
                (ans[v] += (ans[u] + w) * cnt1[u] % mod * inv(cnt1[v]) % mod) %=
                    mod;
            } else if (xh[v] == 0) {
                (ans[v] += (ans[u] + w) * inv(cnt2[v]) % mod) %= mod;
            }
            if (in[v] == 0) {
                q.push(v);
            }
        }
    }
    ans[T] = 0;
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}