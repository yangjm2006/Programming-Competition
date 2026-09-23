#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 100;
const int INF = 1e9;
struct edge {
	int v, c, nxt;
} e[N];
int _, head[N];
void adde(int u, int v, int c) {
	e[++_].v = v;
	e[_].c = c;
	e[_].nxt = head[u];
	head[u] = _;
	e[++_].v = u;
	e[_].c = 0;
	e[_].nxt = head[v];
	head[v] = _;
}
int s, t, cur[N], dis[N];
bool bfs() {
	for (int i = 1; i <= t; i++) {
		dis[i] = INF;
		cur[i] = head[i];
	}
	queue<int> q;
	q.push(s);
	dis[s] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v, c = e[i].c;
			if (c > 0 && dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				q.push(v);
			}
		}
	}
	return dis[t] != INF;
}
int dfs(int u, int flow) {
	if (u == t) return flow;
	int res = 0;
	for (int i = cur[u]; i && flow; i = e[i].nxt) {
		cur[u] = i;
		int v = e[i].v, c = e[i].c;
		if (c && dis[v] == dis[u] + 1) {
			int fw = dfs(v, min(flow, c));
			e[i].c -= fw;
			e[i ^ 1].c += fw;
			flow -= fw;
			res += fw;
		}
	}
	return res;
}
int dinic() {
	int res = 0, tmp;
	while (bfs() && (tmp = dfs(s, INF))) res += tmp;
	return res;
}
void __() {
	int n;
	cin >> n;
	_ = 1;
	s = 2 * n + 1;
	t = s + 1;
	for (int i = 1; i <= t; i++) {
		head[i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		adde(s, i, 1);
		adde(n + i, t, 1);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			bool f;
			cin >> f;
			if (f) adde(i, n + j, 1);
		}
	}
	if (dinic() == n)
		cout << "Yes\n";
	else
		cout << "No\n";
}
int main() {
	int T;
	cin >> T;
	while (T--) __();
	return 0;
}