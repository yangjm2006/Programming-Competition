#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 100;
int n, m, q;
vector<int> e1[N], e2[N];
int dn, dfn[N], low[N], stc[N], top, cn;
void tarjan(int u) {
	dfn[u] = low[u] = ++dn;
	stc[++top] = u;
	for (int v : e1[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) {
				cn++;
				e2[cn].push_back(u);
				e2[u].push_back(cn);
				do {
					e2[cn].push_back(stc[top]);
					e2[stc[top]].push_back(cn);
				} while (stc[top--] != v);
			}
		} else {
			low[u] = min(low[u], dfn[v]);
		}
	}
}
int st[22][N], s[N];
void dfs(int u, int fa) {
	dfn[u] = ++dn;
	st[0][dn] = fa;
	if (u <= n) s[u]++;
	s[u] += s[fa];
	for (int v : e2[u]) {
		if (v == fa) continue;
		dfs(v, u);
	}
}
int get(int u, int v) { return dfn[u] < dfn[v] ? u : v; }
int lca(int u, int v) {
	if (u == v) return u;
	u = dfn[u];
	v = dfn[v];
	if (u > v) swap(u, v);
	u++;
	int x = __lg(v - u + 1);
	return get(st[x][u], st[x][v - (1 << x) + 1]);
}
int main() {
	cin >> n >> m >> q;
	cn = n;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		e1[u].push_back(v);
		e1[v].push_back(u);
	}
	tarjan(1);
	dn = 0;
	dfs(1, 0);
	for (int k = 1; k <= __lg(cn); k++) {
		for (int i = 1; i <= cn - (1 << k - 1); i++) {
			st[k][i] = get(st[k - 1][i], st[k - 1][i + (1 << k - 1)]);
		}
	}
	while (q--) {
		int u, v;
		cin >> u >> v;
		int ans = s[u] + s[v] - s[lca(u, v)] * 2;
		if (lca(u, v) <= n) ans++;
		cout << max(0, ans - 2) << '\n';
	}
	return 0;
}