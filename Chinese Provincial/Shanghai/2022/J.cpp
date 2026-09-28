#include <bits/stdc++.h>
using namespace std;

double F[220][220][220];

int n;
double f(int n1, int n2, int n3) {
	if (F[n1][n2][n3] >= -1) return F[n1][n2][n3];
	if ((n1 + n2 <= 1) && n3 == 0) return F[n1][n2][n3] = 0;
	double ans = 0;
	int sum = (n1 * (n1 - 1) + 2 * n1 * 2 * n2 + 2 * n2 * (2 * n2 - 2) + 2 * n1 * 2 * n3 + 2 * 2 * n2 * 2 * n3 +
			   2 * n3 * (2 * n3 - 1));
	if (n1 >= 2) ans += 1.0 / sum * n1 * (n1 - 1) * f(n1 - 2, n2 + 1, n3);
	if (n1 >= 1 && n2 >= 1) ans += 1.0 / sum * 2 * n1 * 2 * n2 * f(n1 - 1, n2 - 1, n3 + 1);
	if (n2 >= 2) ans += 1.0 / sum * 2 * n2 * (2 * n2 - 2) * f(n1, n2 - 2, n3 + 1);
	if (n1 >= 1 && n3 >= 1) ans += 1.0 / sum * 2 * n1 * 2 * n3 * f(n1 - 1, n2, n3);
	if (n2 >= 1 && n3 >= 1) ans += 1.0 / sum * 2 * 2 * n2 * 2 * n3 * f(n1, n2 - 1, n3);
	if (n3 >= 1) ans += 1.0 / sum * 2 * n3 * (2 * n3 - 1) * f(n1, n2, n3 - 1);
	ans += 1.0 * n * n / sum;
	return F[n1][n2][n3] = ans;
}

void solve() {
	cin >> n;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			for (int k = 0; k <= n; k++) {
				F[i][j][k] = -2;
			}
		}
	}
	cout << fixed << setprecision(9) << f(n, 0, 0) << "\n";
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
	return 0;
}
