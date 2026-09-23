#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

const int M = 4000;

int prime[M + 5], tot;
bool vis[M + 5];

bool isSquare(ll n) {
	ll x = sqrtl((long double)n);
	while ((i128)x * x < n) ++x;
	while ((i128)x * x > n) --x;
	return (i128)x * x == n;
}

bool isCube(ll n) {
	ll x = cbrtl((long double)n);
	while ((i128)x * x * x < n) ++x;
	while ((i128)x * x * x > n) --x;
	return (i128)x * x * x == n;
}

bool isFourth(ll n) {
	ll x = sqrtl(sqrtl((long double)n));
	while ((i128)x * x * x * x < n) ++x;
	while ((i128)x * x * x * x > n) --x;
	return (i128)x * x * x * x == n;
}

void solve() {
	ll n;
	cin >> n;

	ll ans = 1e9;

	for (int i = 1; i <= tot; i++) {
		ll p = prime[i];

		if ((i128)p * p * p * p * p > n) break;

		int cnt = 0;

		while (n % p == 0) {
			n /= p;
			++cnt;
		}

		if (cnt) ans = min(ans, (ll)cnt);
	}

	if (n != 1) {
		if (isFourth(n))
			ans = min(ans, 4LL);
		else if (isCube(n))
			ans = min(ans, 3LL);
		else if (isSquare(n))
			ans = min(ans, 2LL);
		else
			ans = min(ans, 1LL);
	}

	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// 1e18^(1/5) ≈ 3981
	for (int i = 2; i <= M; i++) {
		if (!vis[i]) prime[++tot] = i;

		for (int j = 1; j <= tot && prime[j] * i <= M; j++) {
			vis[prime[j] * i] = true;

			if (i % prime[j] == 0) break;
		}
	}

	int T;
	cin >> T;

	while (T--) solve();

	return 0;
}