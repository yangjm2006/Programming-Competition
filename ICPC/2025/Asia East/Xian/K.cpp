#include <bits/stdc++.h>

using namespace std;
const int N = 2e7 + 10;
const int INF = 1e9;

struct Edge {
	int v, c, nxt;
} e[N];
int _ = 1, head[N];
void adde(int u, int v, int c) {
	e[++_].v = v, e[_].c = c, e[_].nxt = head[u], head[u] = _;
	e[++_].v = u, e[_].c = 0, e[_].nxt = head[v], head[v] = _;
}

int S, T, dis[N], cur[N];
bool bfs() {
	for (int i = 1; i <= T; i++) {
		dis[i] = INF;
		cur[i] = head[i];
	}
	queue<int> q;
	q.push(S);
	dis[S] = 0;
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
	return dis[T] != INF;
}

int dfs(int u, int flow) {
	if (u == T) return flow;
	int res = 0;
	for (int i = cur[u]; i && flow; i = e[i].nxt) {
		cur[u] = i;
		int v = e[i].v, c = e[i].c;
		if (c > 0 && dis[v] == dis[u] + 1) {
			int fw = dfs(v, min(flow, c));
			flow -= fw;
			res += fw;
			e[i].c -= fw;
			e[i ^ 1].c += fw;
		}
	}
	if (flow) cur[u] = 0;
	return res;
}

int dinic() {
	int res = 0, tmp;
	while (bfs() && (tmp = dfs(S, INF))) res += tmp;
	return res;
}

int n;

void init() {
	_ = 1;
	for (int i = 1; i <= T; i++) head[i] = 0;
}

int lowbit(int x) { return x & -x; }

int a[N], b[N];
void __() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	bool flg = 1;
	for (int i = 1; i <= n; i++) {
		if ((a[i] & b[i]) != b[i]) {
			cout << "NO" << '\n';
			return;
		}
		flg &= (a[i] == b[i]);
	}
	if (flg) {
		cout << "YES" << '\n';
		return;
	}
	init();
	S = 2 * n + 1;
	T = 2 * n + 2;
	for (int i = 1; i <= n; i++) {
		adde(S, i, 1);
		adde(i + n, T, 1);
	}
	for (int i = 1; i <= n; i++) {
		adde(b[i] + 1, i + n, 1);
		int x = i - 1;
		while (x) {
			adde(i, i - lowbit(x), INF);
			x -= lowbit(x);
		}
	}
	if (dinic() == n) {
		cout << "YES" << '\n';
	} else {
		cout << "NO" << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		__();
	}
	return 0;
}