#include <bits/stdc++.h>

using namespace std;
const int N = 1e6 + 10;

vector<int> e[N];

int deg[N], fuc[N], xr[N], cnt;
bool vis[N];

void update(int u, int x) {
	cnt -= (fuc[u] > 2);
	fuc[u] += x;
	cnt += (fuc[u] > 2);
}

void del(int u) {
	for (int v : e[u])
		if (vis[v]) {
			if (deg[u] >= 2) update(v, -1);
			if (deg[v] == 2) update(xr[v], -1);
		}
	for (int v : e[u])
		if (vis[v]) {
			if (deg[v] >= 2) update(u, -1);
			deg[u]--;
			deg[v]--;
		}
	vis[u] = 0;
}

void add(int u) {
	vis[u] = 1;
	for (int v : e[u])
		if (vis[v]) {
			deg[u]++;
			deg[v]++;
			if (deg[v] >= 2) update(u, 1);
		}
	for (int v : e[u])
		if (vis[v]) {
			if (deg[u] >= 2) update(v, 1);
			if (deg[v] == 2) update(xr[v], 1);
			xr[v] = u;
			xr[u] = v;
		}
}

int ans[N];

int n, m, q;

void __() {
	cin >> n >> m >> q;
	for (int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) sort(e[i].begin(), e[i].end());
	for (int l = 1, r = 1; r <= n; r++) {
		add(r);
		while (cnt > 0) {
			del(l);
			l++;
		}
		ans[r] = l;
	}
	while (q--) {
		int l, r;
		cin >> l >> r;
		if (ans[r] <= l)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	__();
	return 0;
}