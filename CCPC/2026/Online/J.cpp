#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
const int inf = 4e18;

void solve() {
	int n, m, k;
	cin >> n >> m >> k;
	int a[2 * n + 5];
	int b[2 * n + 10];
	int sum = 0;
	b[0] = 0;
	mt19937 rn;
	int rnd = rn();
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		a[(i + rnd) % n + 1] = x;
		a[(i + rnd) % n + 1 + n] = x;
		sum += x;
	}
	for (int i = 1; i <= 2 * n; i++) {
		b[i] = b[i - 1] + a[i];
	}
	int mmax = 0;
	int ii = 1, iin = 1;
	while (ii <= n) {
		int ssum = 0;
		int nnum = iin * n / k;
		while (ii <= nnum) {
			ssum += a[ii];
			ii++;
		}
		iin++;
		mmax = max(ssum, mmax);
	}
	int l = sum / k, r = mmax;
	while (l < r) {
		int mid = (l + r) >> 1;
		int f = -1;
		int flag = 0;
		int ind = 1;
		while (ind <= f || f == -1) {
			int cnt = 0;
			int now = ind;
			while (cnt < k) {
				int temp = b[now - 1] + mid;
				int nex = upper_bound(b + now, b + ind + n + 1 + 1, temp) - b;
				cnt++;
				if (now == nex) {
					break;
				}
				now = nex;
				if (f == -1) {
					f = now;
				}
				if (now >= ind + n) {
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				break;
			}
			ind++;
		}
		if (flag == 0) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}

	int ans = sum + l * (m - 1);
	cout << ans;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) {
		solve();
	}
}