#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;

ll a[N], b[N], ans1[N], ans2[N];
void solve() {
	ll k, n, m;
	cin >> k >> n >> m;
	priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q1, q2;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		q1.push(make_pair(a[i], a[i]));
	}
	for (int i = 1; i <= k; i++) {
		ans1[i] = q1.top().first;
		q1.push(make_pair(q1.top().first + q1.top().second, q1.top().second));
		q1.pop();
	}
	for (int i = 1; i <= m; i++) {
		cin >> b[i];
		q2.push(make_pair(b[i], b[i]));
	}
	for (int i = 1; i <= k; i++) {
		ans2[i] = q2.top().first;
		q2.push(make_pair(q2.top().first + q2.top().second, q2.top().second));
		q2.pop();
	}
	ll ans = 0;
	for (int i = 1; i <= k; i++) {
		ans = max(ans, ans1[i] + ans2[k + 1 - i]);
	}
	cout << ans << "\n";
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T = 1;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
	return 0;
}
