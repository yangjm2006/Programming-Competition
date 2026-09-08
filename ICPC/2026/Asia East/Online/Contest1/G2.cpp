#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, dis[110];
ll C, c[110];
vector<int> e[110];
void bfs() {
	for (int i = 1; i <= n; i++) dis[i] = 1000;
	queue<int> q;
	dis[1] = 0;
	q.push(1);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : e[u]) {
			if (dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				q.push(v);
			}
		}
	}
}

void solve() {
	cin >> n >> m >> C;
	for (int i = 1; i <= n; i++) cin >> c[i];
	for (int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		e[u].push_back(v);
	}
	bfs();
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
	return 0;
}