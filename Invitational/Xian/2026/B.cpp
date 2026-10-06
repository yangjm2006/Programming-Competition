#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 100;
ll n, x, y, k, m;
int a[N];
void __() {
	cin >> n >> x >> y;
	k = (x + y) / n;
	m = (x + y) % n;
	for (int i = 1; i <= n; i++) {
		char c;
		cin >> c;
		a[i] = c - '0';
	}
	if (k == 0) {
		for (int i = 1; i <= m; i++)
			if (a[i] == 1) y--;
		for (int i = m; i >= 1; i--)
			if (a[i] == 2) {
				if (y > 0) {
					a[i] = 1;
					y--;
				} else {
					a[i] = 0;
				}
			}
		for (int i = m + 1; i <= n; i++)
			if (a[i] == 2) a[i] = 0;
		if (y)
			cout << "-1\n";
		else {
			for (int i = 1; i <= n; i++) cout << a[i];
			cout << '\n';
		}
		return;
	}
	// for (int i = 1; i <= n; i++) cout << a[i];
	// cout << "\n";
	ll A = 0, B = 0;
	for (int i = 1; i <= m; i++)
		if (a[i] == 2)
			A++;
		else if (a[i] == 0)
			x -= k + 1;
	for (int i = m + 1; i <= n; i++)
		if (a[i] == 2)
			B++;
		else if (a[i] == 0)
			x -= k;
	// cout << x << " " << A << " " << B << "!!!\n";
	ll x1, x2 = -1;
	for (x1 = A; x1 >= 0; x1--) {
		if ((x - (k + 1) * x1) % k == 0) {
			x2 = (x - (k + 1) * x1) / k;
			if (x2 >= 0 && x2 <= B) break;
		}
	}
	if (x2 == -1 || x1 * (k + 1) + x2 * k != x) {
		cout << "-1\n";
		return;
	}
	for (int i = 1; i <= m; i++)
		if (a[i] == 2) {
			if (x1 > 0) {
				x1--;
				a[i] = 0;
			} else
				a[i] = 1;
		}
	for (int i = m + 1; i <= n; i++)
		if (a[i] == 2) {
			if (x2 > 0) {
				x2--;
				a[i] = 0;
			} else
				a[i] = 1;
		}
	for (int i = 1; i <= n; i++) cout << a[i];
	cout << '\n';
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) __();
	return 0;
}