#include <bits/stdc++.h>
using namespace std;
void __() {
	int n, k, ans = 0;
	cin >> n >> k;
	map<int, int> mp;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		mp[x]++;
	}
	for (auto [key, val] : mp) {
		if (val <= k) ans += val;
	}
	cout << ans << '\n';
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) __();
	return 0;
}