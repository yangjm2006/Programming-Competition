#include <bits/stdc++.h>
using namespace std;
const int N = 330;
const int INF = 1e9;
int E[N][N];
vector<int> e[N];
int n, m, S, T;
vector<int> road[N];
int dis[N];
vector<int> circle;
vector<pair<int, int>> p;
void make() {
	p.clear();
	for (int i = 1; i <= n; i++) {
		dis[i] = INF;
	}
	queue<int> q;
	q.push(S);
	dis[S] = 0;
	p.push_back(make_pair(0, S));
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : e[u]) {
			if (dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				q.push(v);
				p.push_back(make_pair(dis[v], v));
			}
		}
	}
	sort(p.begin(), p.end());
}
bool check() {
	for (int i = 1; i <= n; i++) {
		dis[i] = INF;
		road[i].clear();
	}
	queue<int> q;
	q.push(S);
	dis[S] = 0;
	road[S].push_back(S);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (u == T) {
			circle = road[u];
			return 1;
		}
		for (int v : e[u]) {
			if (u == S && v == T) continue;
			if (dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				road[v] = road[u];
				road[v].push_back(v);
				q.push(v);
			}
		}
	}
	return 0;
}
int fat[N], form[N];
void bfs(int s) {
	for (int i = 1; i <= n; i++) {
		dis[i] = INF;
	}
	queue<int> q;
	dis[s] = 0;
	for (int u : e[s]) {
		dis[u] = 1;
		fat[u] = s;
		form[u] = u;
		q.push(u);
	}
	int minn = INF;
	int a = -1, b = -1;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : e[u]) {
			if (v == s) continue;
			if (dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				fat[v] = u;
				form[v] = form[u];
				q.push(v);
			} else if (form[u] != form[v]) {
				int len = dis[u] + dis[v] + 1;
				if (len < minn) {
					minn = len;
					a = u;
					b = v;
				}
			}
		}
	}
	if (a == -1) return;
	circle.clear();
	for (; a != s; a = fat[a]) circle.push_back(a);
	circle.push_back(s);
	reverse(circle.begin(), circle.end());
	for (; b != s; b = fat[b]) circle.push_back(b);
}
bool vis[N];
void getLoad() {
	for (int i = 1; i <= n; i++) {
		dis[i] = INF;
		road[i].clear();
	}
	queue<int> q;
	q.push(S);
	dis[S] = 0;
	road[S].push_back(S);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : e[u]) {
			if (dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				road[v] = road[u];
				road[v].push_back(v);
				q.push(v);
				if (vis[v]) {
					for (int i = 0; i < road[v].size() - 1; i++) {
						E[road[v][i]][road[v][i + 1]] = -1;
						E[road[v][i + 1]][road[v][i]] = -2;
					}
					for (int w : road[v]) {
						vis[w] = 1;
					}
					return;
				}
			}
		}
	}
}
void __() {
	cin >> n >> m >> S >> T;
	circle.clear();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) E[i][j] = 0;
		e[i].clear();
		vis[i] = 0;
	}
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		E[u][v] = E[v][u] = i;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	make();
	if (E[S][T] == 0) {
		cout << "Yes\n";
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				if (E[i][j]) {
					if ((j == S || j == T) || (i != S && i != T && i < j)) cout << i << " " << j << '\n';
				}
		}
		return;
	}
	if (!check()) {
		for (auto [fk, u] : p) {
			bfs(u);
			if (circle.size()) break;
		}
	}
	if (circle.size() == 0) {
		cout << "No\n";
		return;
	}
	for (int i = 0; i < circle.size(); i++) {
		vis[circle[i]] = 1;
		E[circle[i]][circle[(i + 1) % circle.size()]] = -1;
		E[circle[(i + 1) % circle.size()]][circle[i]] = -2;
	}
	if (E[S][T] > 0) {
		if (vis[S]) {
			E[T][S] = -1;
			E[S][T] = -2;
		} else if (vis[T]) {
			E[S][T] = -1;
			E[T][S] = -2;
		} else {
			getLoad();
		}
		if (E[T][S] > 0) {
			E[T][S] = -1;
			E[S][T] = -2;
		}
	}
	vis[S] = vis[T] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (E[i][j] > 0 && vis[j]) {
				E[i][j] = -1;
				E[j][i] = -2;
			}
		}
	}
	cout << "Yes\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (E[i][j] == -1 || (E[i][j] > 0 && i < j)) cout << i << " " << j << '\n';
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) __();
	return 0;
}