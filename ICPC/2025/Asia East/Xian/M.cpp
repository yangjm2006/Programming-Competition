#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 2e6 + 10;
const ll mod = 1e9 + 7;

ll n, m, a[N], dp[N][2];
void __() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	ll tot = 1;
	bool f = 1;
	for (int i = 1; i <= n; i++) {
		if (a[i] == -1) (tot *= m) %= mod;
		if (a[i] != -1 && a[i] != 1) f = 0;
	}
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		if (a[i] == -1) {
			dp[i][1] = dp[i - 1][0];
			dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) * max(0ll, m - (n - 1));
		} else {
			if (a[i] == 1) {
				dp[i][1] = dp[i - 1][0];
			} else if (a[i] >= n) {
				dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
			} else {
				dp[i][0] = dp[i][1] = 0;
			}
		}
		if (i == 1 || i == n) dp[i][1] = 0;
		dp[i][0] %= mod;
		dp[i][1] %= mod;
	}
	if (f && n % 2 == 1) dp[n][1]++;
	tot -= dp[n][1] + dp[n][0];
	((tot %= mod) += mod) %= mod;
	cout << tot << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	__();
	return 0;
}