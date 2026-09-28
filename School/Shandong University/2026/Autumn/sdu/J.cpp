#include <bits/stdc++.h>
using namespace std;

const int TREIS = 10000;

double EX = 0;

int n;

int tot[300];

void solve() {
	double ans = 0;
	int cnt = n * n - n;
	vector<pair<int, int>> vec[2];
	for (int i = 1; i <= n; i++) {
		tot[i] = 0;
		for (int j = 1; j <= n; j++)
			if (i != j) {
				vec[0].push_back(make_pair(i, j));
			}
	}
	int tmp = 0;
	while (cnt) {
		ans += n * n * 1.0 / cnt;
		vec[tmp ^ 1].clear();
		int rnd = rand() % vec[tmp].size();
		int x = vec[tmp][rnd].first, y = vec[tmp][rnd].second;
		tot[x]++;
		tot[y]++;
		cnt = 0;
		for (auto [u, v] : vec[tmp]) {
			if (!((u == x && v == y) || (u == y && v == x) || tot[u] == 2 || tot[v] == 2)) {
				vec[tmp ^ 1].push_back(make_pair(u, v));
				cnt++;
			}
		}
		tmp ^= 1;
	}
	// cout << ans << '\n';
	EX += ans / TREIS;
	// cout << EX << '\n';
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= TREIS; i++) {
		solve();
	}
	cout << fixed << setprecision(9) << EX;
	return 0;
}
