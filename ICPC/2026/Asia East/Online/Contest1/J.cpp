#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 4e6 + 100;

int tr[N], tag[N], a[N];

void pushup(int u) { tr[u] = tr[u << 1] + tr[u << 1 | 1]; }

void build(int u, int l, int r) {
	if (l == r) {
		tr[u] = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	pushup(u);
}

void pushdown(int u, int l, int r) {
	tag[u << 1] ^= tag[u];
	tag[u << 1 | 1] ^= tag[u];
	int mid = l + r >> 1;
	if (tag[u]) {
		tr[u << 1] = (mid - l + 1) - tr[u << 1];
		tr[u << 1 | 1] = (r - mid) - tr[u << 1 | 1];
		tag[u] = 0;
	}
}

void update(int u, int l, int r, int L, int R) {
	if (l >= L && r <= R) {
		tag[u] ^= 1;
		tr[u] = r - l + 1 - tr[u];
		return;
	}
	pushdown(u, l, r);
	int mid = l + r >> 1;
	if (L <= mid) update(u << 1, l, mid, L, R);
	if (R > mid) update(u << 1 | 1, mid + 1, r, L, R);
	pushup(u);
}

int query(int u, int l, int r, int L, int R) {
	if (l >= L && r <= R) {
		return tr[u];
	}
	pushdown(u, l, r);
	int mid = l + r >> 1, res = 0;
	if (L <= mid) res += query(u << 1, l, mid, L, R);
	if (R > mid) res += query(u << 1 | 1, mid + 1, r, L, R);
	pushup(u);
	return res;
}

int n, m;

int queryR(int u, int l, int r, int pos) {
	if (r < pos || tr[u] == r - l + 1) return n + 1;
	if (l == r) return l;
	pushdown(u, l, r);
	int mid = l + r >> 1, ans = 0;
	ans = queryR(u << 1, l, mid, pos);
	if (ans == n + 1) ans = queryR(u << 1 | 1, mid + 1, r, pos);
	pushup(u);
	return ans;
}

int findR(int pos) { return queryR(1, 1, n, pos); }

int queryL(int u, int l, int r, int pos) {
	if (l > pos || tr[u] == r - l + 1) return 0;
	if (l == r) return l;
	pushdown(u, l, r);
	int mid = l + r >> 1, ans = 0;
	ans = queryL(u << 1 | 1, mid + 1, r, pos);
	if (ans == 0) ans = queryL(u << 1, l, mid, pos);
	pushup(u);
	return ans;
}

int findL(int pos) { return queryL(1, 1, n, pos); }

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		char c;
		cin >> c;
		if (c == 'N')
			a[i] = 0;
		else
			a[i] = 1;
	}
	build(1, 1, n);
	while (m--) {
		int op, p;
		ll k;
		cin >> op >> p >> k;
		if (op == 1) {
			for (; p <= n && k; p++) {
				if (k & 1) {
					update(1, 1, n, p, min(n, findR(p)));
				}
				k /= 2;
			}
		} else if (op == 2) {
			update(1, 1, n, 1, n);
			for (; p <= n && k; p++) {
				if (k & 1) {
					update(1, 1, n, p, min(n, findR(p)));
				}
				k /= 2;
			}
			update(1, 1, n, 1, n);
		} else if (op == 3) {
			for (; p >= 1 && k; p--) {
				if (k & 1) {
					update(1, 1, n, max(1, findL(p)), p);
				}
				k /= 2;
			}
		} else {
			update(1, 1, n, 1, n);
			for (; p >= 1 && k; p--) {
				if (k & 1) {
					update(1, 1, n, max(1, findL(p)), p);
				}
				k /= 2;
			}
			update(1, 1, n, 1, n);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (query(1, 1, n, i, i) == 1)
			cout << "H";
		else
			cout << "N";
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
	return 0;
}