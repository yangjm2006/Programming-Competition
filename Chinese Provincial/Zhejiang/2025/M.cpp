
#include <bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
#define PII pair<int, int>

void solve() {
	int n;
	cin >> n;
	int a[n + 5] = {};
	for (int i = 3; i < n; i++) {
		cout << "? " << 1 << ' ' << i << endl;
		cin >> a[i];
	}
	stack<int> s;

	vector<PII> ans;
	for (int i = 3; i <= n; i++) {
		if (a[i] > a[i - 1]) {
			int x = a[i] - a[i - 1];
			while (x--) {
				s.push(i - 1);
			}
		} else if (a[i] < a[i - 110]) {
			int x = a[i - 1] - a[i];
			while (x--) {
				ans.push_back({s.top(), i});
				s.pop();
			}
		}
		if (a[i] == 0 && i != n) {
			ans.push_back({1, i});
		}
	}
	cout << "! ";
	for (auto [x, y] : ans) {
		cout << x << ' ' << y << ' ';
	}
	cout << endl;
	int op;
	cin >> op;
}

signed main() {
	ll T = 1;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
/*


*/