#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 100;
int n;
ll a[N], s[N], x;
void __() {
	cin >> n;
	ll sum = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	if (sum % n) {
		cout << "-1\n";
		return;
	}
	x = sum / n;
	for (int i = 2; i <= n; i++) {
		ll v = x - a[i - 1];
		s[i] = v;
		a[i - 1] += v;
		a[i] -= v;
		if (v < 0) {
			cout << "-1\n";
			return;
		}
	}
	ll ans = 0;
	for (int i = 2; i <= n; i++) {
		ans += max(0ll, s[i] - s[i - 2]);
	}
	cout << ans << '\n';
}
int main() {
	int T;
	cin >> T;
	while (T--) __();
	return 0;
}