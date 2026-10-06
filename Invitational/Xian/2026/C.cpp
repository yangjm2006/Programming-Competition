#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const ll mod = 1e9 + 7;
const ll base = 131;
const int N = 1e4 + 100;
ll n, power[N], hash1[N], hash2[N];
ll getHash1(int l, int r) {
	if (l > r) return 0;
	return (hash1[r] - hash1[l - 1] * power[r - l]);
}
ll getHash2(int l, int r) {
	if (l > r) return 0;
	return (hash2[l] - hash2[r + 1] * power[r - l]);
}
int vis[N];
void __() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		char c;
		cin >> c;
		if (c == '(')
			vis[i] = 1;
		else
			vis[i] = 2;
	}
	for (int i = 1; i <= n; i++) {
		hash1[i] = hash1[i - 1] * base + vis[i];
	}
	hash2[n + 1] = 0;
	for (int i = 1; i <= n; i++) {
		hash2[i] = hash2[i + 1] * base + vis[i];
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int s = 0;
		for (int j = i; j <= n; j++) {
			s += (vis[j] == 1 ? 1 : -1);
			if (s < 0) break;
			if (s == 0) {
				cout << i << " " << j << "++\n";
				int len = (j - i + 1) / 2;
				if (getHash1(i + 1, i + len - 1) == getHash2(i + len, j - 1)) {
					ans = max(ans, j - i + 1);
				}
			}
		}
	}
	cout << ans << '\n';
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	power[0] = 1;
	for (int i = 1; i <= 10000; i++) {
		power[i] = power[i] * base;
	}
	int T;
	cin >> T;
	while (T--) __();
	return 0;
}