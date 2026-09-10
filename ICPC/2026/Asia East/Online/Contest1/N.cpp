#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 100;
const int INF = 1e6;

int BEST;

class Segment_Tree {
private:
	int tot;

	struct Node {
		int maxx, ls, rs;
	} tr[N * 100];

	void update(int& u, int l, int r, const int& pos, const int& val) {
		if (!u) {
			u = ++tot;
			tr[u].maxx = -INF;
		}
		tr[u].maxx = max(tr[u].maxx, val);
		if (l == r) return;
		int mid = l + r >> 1;
		if (pos <= mid)
			update(tr[u].ls, l, mid, pos, val);
		else
			update(tr[u].rs, mid + 1, r, pos, val);
	}

	int query(int u, int l, int r, const int& L, const int& R) {
		if (!u) return -INF;
		if (l >= L && r <= R) return BEST = max(BEST, tr[u].maxx);
		if (BEST == 0 || BEST >= tr[u].maxx) return BEST;
		int mid = l + r >> 1, ans = -INF;
		if (L <= mid) ans = max(ans, query(tr[u].ls, l, mid, L, R));
		if (R > mid) ans = max(ans, query(tr[u].rs, mid + 1, r, L, R));
		return ans;
	}

public:
	Segment_Tree() { tr[0].maxx = -INF; }

	void update(int& root, const int& pos, const int& val) { update(root, -INF, INF, pos, val); }

	int query(int root, const int& L, const int& R) { return query(root, -INF, INF, L, R); }
} inner_tree;

class Tree {
private:
	int root, tot;

	struct Node {
		int root, ls, rs;
	} tr[N * 4];

	void update(int& u, int l, int r, const int& x, const int& y, const int& val) {
		if (!u) u = ++tot;
		inner_tree.update(tr[u].root, y, val);
		if (l == r) return;
		int mid = l + r >> 1;
		if (x <= mid)
			update(tr[u].ls, l, mid, x, y, val);
		else
			update(tr[u].rs, mid + 1, r, x, y, val);
	}

	int query(int u, int l, int r, const int& Lx, const int& Rx, const int& Ly, const int& Ry) {
		if (!u) return -INF;
		if (l >= Lx && r <= Rx) return inner_tree.query(tr[u].root, Ly, Ry);
		int mid = l + r >> 1, ans = -INF;
		if (Lx <= mid) ans = max(ans, query(tr[u].ls, l, mid, Lx, Rx, Ly, Ry));
		if (Rx > mid) ans = max(ans, query(tr[u].rs, mid + 1, r, Lx, Rx, Ly, Ry));
		return ans;
	}

public:
	void update(int x, int y, const int& val) { update(root, -INF, INF, x, y, val); }

	int query(const int& Rx, const int& Ry) { return query(root, -INF, INF, -INF, Rx, -INF, Ry); }
} outer_tree;

int n, dp[N], suma, sumb;
void solve() {
	cin >> n;
	outer_tree.update(0, 0, 0);
	for (int i = 1, x, y, z; i <= n; i++) {
		cin >> x >> y >> z;
		suma += x - y;
		sumb += x - z;
		BEST = -INF;
		dp[i] = max(dp[i - 1], i + outer_tree.query(suma, sumb));
		outer_tree.update(suma, sumb, dp[i] - i);
	}
	cout << dp[n];
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
	return 0;
}