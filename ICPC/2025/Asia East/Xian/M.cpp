#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 2e6 + 10;
const ll mod = 1e9 + 7;

ll n, m, a[N];
void __() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	ll tot = 1, fuc = 1;
	bool f = 1;
	for (int i = 1; i <= n; i++) {
		if (a[i] != -1) (tot *= m) %= mod;
		if (a[i] != -1 || a[i] != 1) f = 0;
	}
	if (f && n % 2 == 1) fuc++;
	cout << tot - fuc << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	__();
	return 0;
}