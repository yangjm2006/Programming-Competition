#include <bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;

const int N = 1e6 + 100;

int n, a[N];
struct Edge {
	int v, id;
};
vector<Edge> e[N];

int dn, dfn[N], low[N], stc[N], top, cn;
vector<int> vec[N];
void dfs(int u, int eid) {
	dfn[u] = low[u] = ++dn;
	stc[++top] = u;
	for (auto [v, id] : e[u]) {
		if (id == eid) continue;
		if (!dfn[v]) {
			dfs(v, id);
			low[u] = min(low[u], low[v]);
		} else
			low[u] = min(low[u], dfn[v]);
	}
	if (low[u] >= dfn[u]) {
		cn++;
		do vec[cn].push_back(stc[top]);
		while (stc[top--] != u);
	}
}

int f[N][2];
bool vis[N];

void dfs2(int u, int fa) {
	for (auto [v, id] : e[u]) {
		if (v == fa || vis[v]) continue;
		dfs2(v, u);
		f[u][0] += max(f[v][0], f[v][1]);
		f[u][1] += f[v][0];
	}
	f[u][1]++;
}

int ans, fuck[N][2][2];
void tarjan() {
	vector<int> fuc;
	for (int o = 1; o <= n; o++)
		if (!dfn[o]) {
			for (int i = 1; i <= cn; i++) {
				vec[i].clear();
			}
			cn = 0;
			dfs(o, 0);
			fuc.clear();
			for (int i = 1; i <= cn; i++)
				if (vec[i].size() >= 2 || vec[i][0] == a[vec[i][0]]) {
					fuc = vec[i];
					for (int x : vec[i]) {
						vis[x] = 1;
					}
				}
			for (int i = 0; i < fuc.size(); i++) {
				dfs2(fuc[i], 0);
				if (i == 0) {
					fuck[i][0][0] = f[fuc[i]][0];
					fuck[i][1][1] = f[fuc[i]][1];
				} else {
					fuck[i][0][0] = f[fuc[i]][0] + max(fuck[i - 1][0][0], fuck[i - 1][0][1]);
					fuck[i][0][1] = f[fuc[i]][1] + fuck[i - 1][0][0];
					fuck[i][1][0] = f[fuc[i]][0] + max(fuck[i - 1][1][0], fuck[i - 1][1][1]);
					fuck[i][1][1] = f[fuc[i]][1] + fuck[i - 1][1][0];
				}
			}
			ans += max(max(fuck[fuc.size() - 1][1][0], fuck[fuc.size() - 1][0][1]), fuck[fuc.size() - 1][0][0]);
		}
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		e[i].push_back(Edge{a[i], i});
		e[a[i]].push_back(Edge{i, i});
	}
	tarjan();
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll T = 1;
	// cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
/*
6
4 1 1 5 6 5

6
2 3 4 1 6 5

4
2 3 4 1

8
2 1 1 1 1 2 2 2
*/