#include <bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;

void solve() {
	ll n;
	cin >> n;
	ll a[n + 10] = {};
	string ans;
	for (ll i = 0; i <= n; i++) {
		cin >> a[i];
	}
	for (ll i = 0; i <= n; i++) {
		if (i == 0 || i == n) {
			a[i] -= 1;
		} else {
			a[i] -= 2;
		}
		if (a[i] < 0) {
			cout << "Impossible\n";
			return;
		}
	}
	for (ll i = 0; i < n; i++) {
		while (a[i] >= 1 && a[i + 1] >= 1) {
			a[i]--;
			a[i + 1]--;
			ans.push_back('R');
			ans.push_back('L');
		}
		if (a[i] >= 1) {
			cout << "Impossible\n";
			return;
		}
		ans.push_back('R');
	}
	if (a[n] >= 1) {
		cout << "Impossible\n";
		return;
	}
	for (ll i = 1; i <= n; i++) {
		ans.push_back('L');
	}
	cout << ans << "\n";
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll T = 1;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}