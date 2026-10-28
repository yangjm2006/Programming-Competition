
#include <bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;

const int N = 1e6 + 100;
const int INF = 1e9;

int n, m, k;
vector<int> vec[100];
vector<int> e[N];
int dis[N][2], from[N][2];

struct State {
	int u, frm, d;
};

int fuck(int c) {
	for (int i = 1; i <= n; i++) {
		dis[i][0] = dis[i][1] = INF;
		from[i][0] = from[i][1] = 0;
	}
	queue<State> q;
	for (int u : vec[c]) {
		q.push(State{u, u, 1});
		dis[u][0] = 1;
		dis[u][1] = INF;
		from[u][0] = u;
		from[u][1] = 0;
	}
	int minn = INF;
	while (!q.empty()) {
		int u = q.front().u, frm = q.front().frm, d = q.front().d;
		// cout << u << " " << frm << " " << d << "++\n";
		q.pop();
		if (dis[u][0] == 1 && dis[frm][0] == 1 && frm != u) {
			// cout << u << " " << frm << "!!!!\n";
			return 0;
		}
		if (d == k) continue;
		for (int v : e[u]) {
			if (d + 1 < dis[v][0]) {
				dis[v][0] = d + 1;
				from[v][0] = frm;
				q.push(State{v, frm, d + 1});
			} else if (d + 1 < dis[v][1] && frm != from[v][0]) {
				dis[v][1] = d + 1;
				from[v][1] = frm;
				q.push(State{v, frm, d + 1});
			}
		}
	}
	return 1;
}

void solve() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		e[i].clear();
	}
	for (int i = 1; i <= 50; i++) {
		vec[i].clear();
	}
	for (int i = 1; i <= n; i++) {
		int c;
		cin >> c;
		vec[c].push_back(i);
	}
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
	}
	for (int i = 1; i <= 50; i++) {
		if (!fuck(i)) {
			cout << "NO\n";
			return;
		}
	}
	cout << "YES\n";
}

signed main() {
	ios::sync_with_stdio(0);
	ll T = 1;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
/*
3
3 2 2
1 2 1
1 2
2 3
3 3 2
1 2 1
1 2
2 3
1 3
3 3 50
1 1 2
1 2
2 3
1 3

*/