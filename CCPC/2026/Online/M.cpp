#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long

int fac[200005];

int ifac[200005];
const int p = 998244353;
const int inf = 4e18;
int ksm(int a, int b) {
	int ans = 1;
	while (b > 0) {
		if ((b & 1) == 1) {
			ans *= a;
			ans %= p;
		}
		b >>= 1;
		a *= a;
		a %= p;
	}
	return ans;
}

int inv(int x) { return ksm(x, p - 2); }

int C(int n, int m) {
	if (m == 0) return 1;
	return fac[n] * ifac[m] % p * ifac[n - m] % p;
}

int f(int a, int b) { return C(a + b, a); }

int f2(int a, int b) { return C(a + b, b - 1); }

bool cmp(int a, int b) { return a < b; }

int a[200005], b[200005], s1[200005], s2[200005];
map<int, int> mp;
void solve() {
	int n, k;
	cin >> n >> k;
	mp.clear();
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		mp[a[i]]++;
	}
	int cnt = 0;
	for (auto [x, num] : mp) {
		a[++cnt] = x;
		b[cnt] = num;
	}
	for (int i = 1; i <= cnt; i++) {
		s1[i] = s1[i - 1] + b[i];
	}
	s2[cnt + 1] = 0;
	for (int i = cnt; i >= 1; i--) {
		s2[i] = s2[i + 1] + b[i];
	}
	int L = 1, R = cnt;
	int ans = 0;
	while (L < R) {
		while (L < R && a[R] + a[L] > k * 2) {
			R--;
		}
		if (L == R) break;
		if (a[L] + a[R] == 2 * k) {
			(ans += f(s1[L], s2[R]) - f(s1[L - 1], s2[R]) - f(s1[L], s2[R + 1]) + f(s1[L - 1], s2[R + 1])) %= p;
		}
		L++;
	}
	if (a[L] == k) {
		for (int i = 1; i < b[L]; i++) {
			(ans += f2(s1[L - 1] + i - 1, s2[L + 1] + b[L] - i) - f2(s1[L - 1] + i - 1, s2[L + 1])) %= p;
		}
		for (int i = 1; i <= b[L]; i++) {
			(ans += f(s1[L - 1] + i - 1, s2[R + 1] + (b[L] - i))) %= p;
		}
	}
	ans %= p;
	ans += p;
	ans %= p;
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	fac[0] = 1;
	for (int i = 1; i <= 200000; i++) {
		fac[i] = fac[i - 1] * i % p;
	}
	ifac[200000] = ksm(fac[200000], p - 2);
	for (int i = 200000 - 1; i >= 0; i--) {
		ifac[i] = ifac[i + 1] * (i + 1) % p;
	}
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}