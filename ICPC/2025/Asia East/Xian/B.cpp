#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;

int n, cnt[10], a[N];

int sL, sR;

bool fuck() {
	for (int i = 1; i <= n; i++) {
		if (a[i] != a[i - 1])
			sL = i;
		else
			break;
	}
	for (int i = n; i >= 1; i--) {
		if (a[i] != a[i + 1])
			sR = i;
		else
			break;
	}
	// cout << sL << " " << sR << "!!!!\n";
	return sL >= sR;
}

int L, R;

int res[10];
bool check() {
	// cout << L << " " << R << "!!!\n";
	res[1] = res[2] = res[3] = 0;
	if (L > 1) res[a[L - 1]]++;
	if (R < n) res[a[R + 1]]++;
	int tot1 = cnt[1] + cnt[2] + cnt[3], tot2 = res[1] + res[2] + res[3];
	for (int i = 1; i <= 3; i++) {
		if (cnt[i] > (tot1 + 1) / 2) return 0;
	}
	for (int i = 1; i <= 3; i++) {
		if (cnt[i] + res[i] > (tot1 + tot2 + 1) / 2) return 0;
		if (cnt[i] * 2 == tot1 + 1 && res[i] > 0) return 0;
	}
	return 1;
}

void add(int x) { cnt[a[x]]++; }

void del(int x) { cnt[a[x]]--; }

int ans[N];

bool canmake(int len, int left, int right) {
	for (int i = 1; i <= 3; i++) {
		if (2 * cnt[i] > len + 1 - (i == left) - (i == right)) return 0;
	}
	return 1;
}

void make(int l, int r) {
	cnt[1] = cnt[2] = cnt[3] = 0;
	for (int i = l; i <= r; i++) {
		cnt[a[i]]++;
	}
	for (int i = 1; i <= l - 1; i++) ans[i] = a[i];
	for (int i = r + 1; i <= n; i++) ans[i] = a[i];
	for (int i = l; i <= r; i++) {
		for (int k = 1; k <= 3; k++) {
			cnt[k]--;
			if (k != ans[i - 1] && cnt[k] >= 0 && canmake(r - i, k, a[r + 1])) {
				ans[i] = k;
				break;
			}
			cnt[k]++;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (ans[i] == 1)
			cout << 'C';
		else if (ans[i] == 2)
			cout << 'W';
		else if (ans[i] == 3)
			cout << 'P';
		else
			cout << "X";
	}
	cout << "\n";
}

void __() {
	cin >> n;
	cnt[1] = cnt[2] = cnt[3] = 0;
	for (int i = 0; i <= n + 2; i++) {
		a[i] = ans[i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		char c;
		cin >> c;
		if (c == 'C') {
			a[i] = 1;
		} else if (c == 'W') {
			a[i] = 2;
		} else {
			a[i] = 3;
		}
		cnt[a[i]]++;
		// cout << a[i] << " ";
	}
	if (fuck()) {
		cout << "Beautiful\n";
		return;
	}
	L = 1, R = n;
	int ans = n + 1, ansl, ansr;
	while (L <= sL + 1) {
		while (R < n && R < L + ans - 2) {
			R++;
			add(R);
		}
		while (max(L, sR - 1) <= R && check()) {
			ans = R - L + 1;
			ansl = L;
			ansr = R;
			del(R);
			R--;
		}
		del(L);
		L++;
	}
	if (ans > n)
		cout << "Impossible\n";
	else {
		cout << "Possible\n";
		cout << ansl << " " << ansr << "\n";
		make(ansl, ansr);
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		__();
	}
	return 0;
}