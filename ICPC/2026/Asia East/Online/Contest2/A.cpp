#include <bits/stdc++.h>
using namespace std;

struct Basis {
	static const int M = 20;
	int a[M]{};
	int rank = 0;

	int insert(int x) {
		for (int j = M - 1; j >= 0; j--) {
			if (!(x >> j & 1)) continue;
			if (a[j]) {
				x ^= a[j];
			} else {
				a[j] = x;
				rank++;
				return x;
			}
		}
		return 0;
	}

	bool contain(int x) const {
		for (int j = M - 1; j >= 0; j--) {
			if (!(x >> j & 1)) continue;
			if (!a[j]) return 0;
			x ^= a[j];
		}
		return 1;
	}

	vector<int> basis() const {
		vector<int> res;
		for (int j = 0; j < M; j++)
			if (a[j]) res.push_back(a[j]);
		return res;
	}

	vector<int> values() const {
		vector<int> res;
		res.push_back(0);
		for (int i = 0; i < M; i++) {
			if (!a[i]) continue;
			int oldLen = res.size();
			for (int j = 0; j < oldLen; j++) {
				res.push_back(res[j] ^ a[i]);
			}
		}
		return res;
	}
};

void solve() {
	int n, m;
	cin >> n >> m;
	int V = 1 << m;
	vector<Basis> bas(n + 1);
	vector<int> cnt(V, 0), tag(V, 0);
	Basis U;
	for (int i = 1, c; i <= n; i++) {
		cin >> c;
		for (int j = 1, x; j <= c; j++) {
			cin >> x;
			bas[i].insert(x);
			cnt[x]++;
			tag[x] = i;
		}
		if (2 * c >= (1 << bas[i].rank)) {
			vector<int> vals = bas[i].values();
			for (int& x : vals) {
				if (tag[x] != i) U.insert(x);
			}
		} else {
			vector<int> bs = bas[i].basis();
			for (int& x : bs) {
				U.insert(x);
			}
		}
	}
	for (int i = 0; i < V; i++)
		if (cnt[i] == n) U.insert(i);

	vector<int> used(n + 1, 0);
	queue<int> q;
	for (int i = 0; i < m; i++) {
		if (U.a[i]) q.push(U.a[i]);
	}
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = 1; i <= n; i++) {
			if (used[i]) continue;
			if (!bas[i].contain(u)) {
				vector<int> bs = bas[i].basis();
				for (int& x : bs) {
					int newb = U.insert(x);
					if (newb) {
						q.push(newb);
					}
				}
				used[i] = 1;
			}
		}
	}

	vector<int> ans, vals = U.values();
	for (int i = 0; i < vals.size(); i++) {
		if (cnt[vals[i]] != n) ans.push_back(vals[i]);
	}
	cout << ans.size() << '\n';
	for (int x : ans) cout << x << " ";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
	while (t--) {
		solve();
	}
	return 0;
}