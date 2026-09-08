#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
const ll mod = 998244353;
#define PII pair<int, int>

void solve() {
	int n;
	cin >> n;
	// unordered_map<int, int> m;
	vector<char> ans;
	char op[n + 5];
	int x[n + 5];
	for (int i = 1; i <= n; i++) {
		cin >> op[i] >> x[i];
	}
	int ky[n + 5];
	for (int i = 1; i <= n; i++) {
		ky[i] = i;
	}
	unordered_map<int, int> las;
	for (int i = 1; i <= n; i++) {
		if (op[i] == 'T') {
			if (las[x[i]] != 0) {
				ky[las[x[i]]] = i;
			}
		} else if (op[i] == '+') {
			las[x[i]] = i;
		}
	}
	stack<PII> s;
	for (int i = 1; i <= n; i++) {
		ans.push_back(op[i]);
		if (op[i] == '+') {
			s.push({x[i], ky[i]});
		} else if (op[i] == 'T') {
		} else if (op[i] == 'F') {
		}
		while (!s.empty() && s.top().second <= i) {
			s.pop();
			ans.push_back('-');
		}
	}
	for (char c : ans) {
		if (c == 'T' || c == 'F') {
			c = '?';
		}
		cout << c;
	}
	cout << endl;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	ll T = 1;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}