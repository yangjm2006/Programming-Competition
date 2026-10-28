#include <bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;

void solve() {
	string A, B;
	cin >> A >> B;
	int tp1 = 0, tp2 = 0;
	for (int i = 1; i <= 10; i++) {
		string a, b;
		while (tp1 < A.size() && A[tp1] != '.') {
			a += A[tp1];
			tp1++;
		}
		while (tp2 < B.size() && B[tp2] != '.') {
			b += B[tp2];
			tp2++;
		}
		while (a.size() < b.size()) a = "0" + a;
		while (b.size() < a.size()) b = "0" + b;
		if (a == "") break;
		// cout << a << " " << b << "\n";
		if (a > b) {
			cout << "A\n";
			return;
		}
		if (a < b) {
			cout << "B\n";
			return;
		}
		tp1++;
		tp2++;
	}
	cout << "Equal\n";
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll T = 1;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
/*
4
1.0.2
1.1.0
123.0
2.100
0.1.2
0.1.2
0.1.12
0.1.8
*/