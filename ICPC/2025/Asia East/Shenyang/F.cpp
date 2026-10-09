#include <bits/stdc++.h>
using namespace std;
const int N = 330;
const int INF = 1e9;
int E[N][N];
vector<int> e[N];
int n, m, S, T;
vector<int> road[N];
int dis[N], minn;
vector<int> circle;
void bfs(int s) {
	for (int i = 1; i <= n; i++) {
		dis[i] = INF;
		road[i].clear();
	}
	queue<int> q;
	q.push(s);
	dis[s] = 0;
	road[s].push_back(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : e[u]) {
			if (dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				road[v] = road[u];
				road[v].push_back(v);
				q.push(v);
			} else if (dis[v] == dis[u] + 1 || dis[v] == dis[u]) {
				if (minn > dis[u] + dis[v]) {
					minn = dis[u] + dis[v];
					circle.clear();
					for (int w : road[u]) {
						circle.push_back(w);
					}
					for (int i = road[v].size() - 1; i >= 1; i--) {
						circle.push_back(road[v][i]);
					}
				}
			}
		}
	}
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
					return;
				}
			}
		}
	}
}
void __() {
	cin >> n >> m >> S >> T;
	minn = INF;
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
	for (int i = 1; i <= n; i++) {
		bfs(i);
	}
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
	if (circle.size() == 0) {
		cout << "No\n";
		return;
	}
	// cout << circle.size() << '\n';
	// for (int u : circle) {
	// 	cout << u << " ";
	// }
	// cout << '\n';
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
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (E[i][j] > 0 && (vis[j] || j == S || j == T)) {
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