#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 100;

struct Node {
	int u, v, c, d;
};

void __() {
	int n, m;
	cin >> n >> m;
	vector<Node> vec(m);
	vector<bool> vis(n + 1, 0);
	for (auto& [u, v, c, d] : vec) {
		cin >> u >> v >> c >> d;
		vis[d] = 1;
	}
	set<pair<int, int>> st;
	vector<int> tot(n + 1, 0);
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (vis[i] == 0) {
			st.insert(make_pair(0, i));
			tot[i] = 0;
		}
	}
	for (int i = m - 1; i >= 0; i--) {
		int u = vec[i].u, v = vec[i].v, c = vec[i].c, d = vec[i].d;
		st.insert(make_pair(tot[d] = (*st.begin()).first, d));
		if (c) {
			cnt++;
			st.insert(make_pair(--tot[u], u));
			st.insert(make_pair(--tot[v], v));
		} else {
			st.insert(make_pair(++tot[u], u));
			st.insert(make_pair(++tot[v], v));
		}
		while (st.size() && tot[(*st.begin()).second] != (*st.begin()).first) st.erase(st.begin());
		cout << '\n';
	}
	cout << (*st.begin()).first + cnt << '\n';
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	__();
	return 0;
}