#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

int n, m, dis[110], D, cnt1[110], cnt2[110];
ll C, c[110];
vector<int> e1[110], e2[110], e3[110];

void bfs() {
	for (int i = 1; i <= n; i++) dis[i] = 1000;
	queue<int> q;
	dis[1] = 0;
	q.push(1);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : e1[u]) {
			if (dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				q.push(v);
			}
		}
	}
	D = dis[n];
}

vector<int> node[110];
vector<ll> path1[110], path2[110];
void solve() {
	cin >> n >> m >> C;
	for (int i = 1; i <= n; i++) cin >> c[i];
	for (int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		e1[u].push_back(v);
	}
	if (n == 1) {
		if (C >= c[1])
			cout << "1";
		else
			cout << "0";
		return;
	}
	bfs();
	if (D == 1000) {
		cout << "0";
		return;
	}
	for (int u = 1; u <= n; u++)
		for (int v : e1[u])
			if (dis[v] == dis[u] + 1) {
				e2[u].push_back(v);
				e3[v].push_back(u);
			}
	for (int i = 1; i <= n; i++)
		if (dis[i] < 1000) {
			cnt1[dis[i]]++;
			cnt2[dis[i]]++;
			node[dis[i]].push_back(i);
		}
	for (int i = 1; i <= D; i++) cnt1[i] += cnt1[i - 1];
	for (int i = D - 1; i >= 0; i--) cnt2[i] += cnt2[i + 1];
	int P = 1;
	for (int i = 1; i <= D; i++) {
		if (max(cnt1[i], cnt2[i]) < max(cnt1[P], cnt2[P])) {
			P = i;
		}
	}
	path1[1].push_back(c[1]);
	path2[n].push_back(c[n]);
	for (int i = 0; i <= P - 1; i++) {
		for (int u : node[i]) {
			sort(path1[u].begin(), path1[u].end());
			for (int v : e2[u]) {
				for (ll p : path1[u]) {
					if (c[v] + p <= C)
						path1[v].push_back(c[v] + p);
					else
						break;
				}
			}
		}
	}
	for (int i = D; i >= P + 1; i--) {
		for (int u : node[i]) {
			sort(path2[u].begin(), path2[u].end());
			for (int v : e3[u]) {
				for (ll p : path2[u]) {
					if (c[v] + p <= C)
						path2[v].push_back(c[v] + p);
					else
						break;
				}
			}
		}
	}
	ll ans = 0;
	for (int u : node[P]) {
		sort(path1[u].begin(), path1[u].end());
		sort(path2[u].begin(), path2[u].end());
		int R = path2[u].size() - 1;
		for (int i = 0; i < path1[u].size(); i++) {
			while (R >= 0 && path1[u][i] + path2[u][R] - c[u] > C) R--;
			ans += R + 1;
		}
	}
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
	return 0;
}