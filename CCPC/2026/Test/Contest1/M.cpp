#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 100;
typedef long long ll;
typedef __int128 i128;
const ll mod = 998244353;
void printi(i128 x) {
	if (x == 0) {
		cout << '0';
		return;
	}
	if (x < 0) {
		cout << '-';
		x = -x;
	}
	string s;
	while (x) {
		s += char(x % 10 + '0');
		x /= 10;
	}
	reverse(s.begin(), s.end());
	cout << s;
}
vector<int> e[N];
int n, q, dn, dfn[N], low[N], cn, col[N], stc[N], tp;
bool vis[N];
i128 a[N], val[N];
void dfs(int u) {
	dfn[u] = low[u] = ++dn;
	stc[++tp] = u;
	vis[u] = 1;
	for (int v : e[u]) {
		if (!dfn[v]) dfs(v);
		if (vis[v]) low[u] = min(low[u], low[v]);
	}
	if (dfn[u] == low[u]) {
		cn++;
		do {
			col[stc[tp]] = cn;
			vis[stc[tp]] = 0;
			val[cn] += a[stc[tp]];
		} while (stc[tp--] != u);
	}
}
void tarjan() {
	cn = dn = tp = 0;
	for (int i = 0; i <= 2 * n + 1; i++) val[i] = dfn[i] = low[i] = col[i] = stc[i] = 0;
	for (int i = 2; i <= 2 * n + 1; i++)
		if (!dfn[i]) dfs(i);
}
vector<pair<int, int>> vec[N];
bool fuck[N], used[N];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> q;
	int cnt = 0;
	while (q--) {
		int op;
		cin >> op;
		if (op == 1) {
			int u, v;
			bool k;
			cin >> u >> v >> k;
			cnt++;
			if (k) {
				vec[cnt].push_back(make_pair(u << 1, v << 1 | 1));
				vec[cnt].push_back(make_pair(u << 1 | 1, v << 1));
				vec[cnt].push_back(make_pair(v << 1, u << 1 | 1));
				vec[cnt].push_back(make_pair(v << 1 | 1, u << 1));
			} else {
				vec[cnt].push_back(make_pair(u << 1, v << 1));
				vec[cnt].push_back(make_pair(u << 1 | 1, v << 1 | 1));
				vec[cnt].push_back(make_pair(v << 1, u << 1));
				vec[cnt].push_back(make_pair(v << 1 | 1, u << 1 | 1));
			}
		} else if (op == 2) {
			int id;
			cin >> id;
			fuck[id] = 1;
		} else if (op == 3) {
			int u;
			cin >> u;
			ll x;
			cin >> x;
			a[u << 1] = x;
			cin >> x;
			a[u << 1 | 1] = x;
		} else {
			for (int i = 1; i <= 2 * n + 1; i++) {
				e[i].clear();
			}
			for (int i = 1; i <= cnt; i++) {
				if (fuck[i]) continue;
				for (auto [u, v] : vec[i]) {
					e[u].push_back(v);
				}
			}
			tarjan();
			for (int i = 1; i <= cn; i++) used[i] = 0;
			bool flg = 0;
			ll ans2 = 1;
			i128 ans1 = 0;
			for (int i = 1; i <= n; i++) {
				if (col[i << 1] == col[i << 1 | 1]) {
					flg = 1;
					break;
				}
				if (used[col[i << 1]]) continue;
				used[col[i << 1]] = used[col[i << 1 | 1]] = 1;
				if (val[col[i << 1]] == val[col[i << 1 | 1]]) {
					ans2 *= 2;
					ans2 %= mod;
				}
				ans1 += max(val[col[i << 1]], val[col[i << 1 | 1]]);
			}
			if (flg) {
				cout << "0\n";
			} else {
				printi(ans1);
				cout << " " << ans2 << '\n';
			}
		}
	}
	tarjan();
	return 0;
}