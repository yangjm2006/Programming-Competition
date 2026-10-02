#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 10;
int a[N][N], n, in[N], dis[N];
vector<int> e[N];
vector<pair<int, int>> ans;
void __() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			cin >> a[i][j];
			a[j][i] = a[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i != j) {
				if ((a[1][i] ^ a[i][j] ^ a[i][i]) == a[1][j]) {
					e[i].push_back(j);
					in[j]++;
				}
			}
		}
	}
	queue<int> q;
	q.push(1);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : e[u]) {
			dis[v] = max(dis[v], dis[u] + 1);
			in[v]--;
			if (in[v] == 0) q.push(v);
		}
	}
	for (int u = 1; u <= n; u++) {
		for (int v : e[u]) {
			if (dis[v] == dis[u] + 1) ans.push_back({u, v});
		}
	}
	for (auto [u, v] : ans) cout << u << " " << v << "\n";
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	__();
	return 0;
}