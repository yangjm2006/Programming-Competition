#include <bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;

void solve() {
	ll n, m;
	cin >> n >> m;
	ll b[n + 10] = {};
	for (ll i = 1, d; i <= m; i++) {
		cin >> d;
		if (b[d]) {
			cout << "the lights are already on!" << "\n";
		} else {
			ll ans = 0;
			for (ll j = d; j <= n; j += d) {
				if (b[j] == 0) {
					ans++;
				}
				b[j] = 1;
			}
			cout << ans << "\n";
		}
	}
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