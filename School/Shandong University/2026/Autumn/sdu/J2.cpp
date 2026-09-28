#include <bits/stdc++.h>
using namespace std;

double F[220][220][220];

int n;
double f(int n1, int n2, int n3) {
	if (F[n1][n2][n3] >= -1) return F[n1][n2][n3];
	return F[n1][n2][n3] = 1 + 1.0 / n / n * (n1 * (n1 - 1) / 2 * f(n1 - 2, n2 + 1, n3) + f);
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {
				F[i][j][k] = -2;
			}
		}
	}
	cout << fixed << setprecision(9) << f(n, 0, 0) << "\n";
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	return 0;
}
