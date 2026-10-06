#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4e5 + 10;
const ll mod = 998244353;
ll n, a[100], ans[100][100];
void __() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) {
		ans[i][i]++;
		for (int j = 1; j <= n; j++) (ans[i][j] += a[j]) %= mod;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) cout << ans[i][j] << " ";
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	__();
	return 0;
}