
#include <bits/stdc++.h>
#define ll long long
#define int long long
#define double long double
using namespace std;

const int N = 100;
const int INF = 1e15;

ll n, k, l[N];

ll check(double x) {
	ll cnt = 0;
	for (ll i = 1; i <= n; i++) {
		cnt += max(0ll, (ll)(((double)l[i] - x * 100) / (l[i] * x)));
		if (cnt > k) {
			return 1;
		}
	}
	if (cnt == k) {
		return 0;
	}
	return -1;
}

void solve() {
	cin >> n >> k;
	for (ll i = 1; i <= n; i++) {
		cin >> l[i];
	}
	double L = 0, R = 1, res;
	double ans = 1;
	for (ll i = 1; i <= 1000; i++) {
		double mid = (L + R) / 2;
		if (check(mid) == 1) {
			L = mid;
		} else if (check(mid) == -1) {
			R = mid;
			res = mid;
		} else {
			res = mid;
			break;
		}
	}
	ll fuck = k;
	vector<double> fk;
	for (ll i = 1; i <= n; i++) {
		ll cnt = max(0ll, (ll)(((double)l[i] - res * 100) / (l[i] * res)));
		fuck -= cnt;
		ans *= ((double)l[i] * cnt / 100 + 1);
		fk.push_back(((double)l[i] * (cnt + 1) / 100 + 1) / ((double)l[i] * cnt / 100 + 1));
	}
	sort(fk.begin(), fk.end(), greater<double>());
	for (int i = 0; i < fuck; i++) {
		ans *= fk[i];
	}
	cout << fixed << setprecision(10) << ans << "\n";
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	ll T = 1;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}