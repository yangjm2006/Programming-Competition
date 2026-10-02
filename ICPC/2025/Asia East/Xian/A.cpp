#include <bits/stdc++.h>

using namespace std;
const int N = 4e5 + 10;

int a[N], b[N];

struct Node {
	int a, b, id;
	bool operator<(const Node& other) const {
		if (b == other.b) {
			if (a == other.a) return id < other.id;
			return a < other.a;
		}
		return b < other.b;
	}
};
multiset<Node> stt;
bool is_have(int b) { return stt.lower_bound({0, b, 0}) != stt.end() && stt.lower_bound({0, b, 0})->b == b; }

int tr1[N * 16], sum1[N * 16];

void pushup1(int u) {
	tr1[u] = max(tr1[u << 1], tr1[u << 1 | 1]);
	sum1[u] = sum1[u << 1] + sum1[u << 1 | 1];
}

void add1(int u, int l, int r, int pos, int val, int id) {
	if (l == r) {
		tr1[u] = max(tr1[u], val);
		sum1[u]++;
		stt.insert({val, pos, id});
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
		add1(u << 1, l, mid, pos, val, id);
	else
		add1(u << 1 | 1, mid + 1, r, pos, val, id);
	pushup1(u);
}

void del1(int u, int l, int r, int pos, int val, int id) {
	if (l == r) {
		sum1[u]--;
		stt.erase({val, pos, id});
		auto it = stt.lower_bound({0, pos + 1, 0});
		if (it != stt.begin() && prev(it)->b == pos) {
			tr1[u] = prev(it)->a;
		} else {
			tr1[u] = 0;
		}
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
		del1(u << 1, l, mid, pos, val, id);
	else
		del1(u << 1 | 1, mid + 1, r, pos, val, id);
	pushup1(u);
}

pair<int, int> merge1(pair<int, int> a, pair<int, int> b) {
	return make_pair(max(a.first, b.first), a.second + b.second);
}

pair<int, int> query1(int u, int l, int r, int L, int R) {
	if (L <= l && r <= R) {
		return make_pair(tr1[u], sum1[u]);
	}
	int mid = (l + r) >> 1;
	pair<int, int> res = {0, 0};
	if (L <= mid) res = merge1(res, query1(u << 1, l, mid, L, R));
	if (R > mid) res = merge1(res, query1(u << 1 | 1, mid + 1, r, L, R));
	return res;
}

int find1(int u, int l, int r, int val) {
	if (l == r) return l;
	int mid = (l + r) >> 1;
	if (tr1[u << 1] >= val) return find1(u << 1, l, mid, val);
	return find1(u << 1 | 1, mid + 1, r, val);
}

int tr2[N * 16], tag[N * 16];

void pushup2(int u) { tr2[u] = min(tr2[u << 1], tr2[u << 1 | 1]); }

void pushdown2(int u) {
	if (tag[u]) {
		tr2[u << 1] += tag[u];
		tr2[u << 1 | 1] += tag[u];
		tag[u << 1] += tag[u];
		tag[u << 1 | 1] += tag[u];
		tag[u] = 0;
	}
}

void update2(int u, int l, int r, int L, int R, int val) {
	if (L <= l && r <= R) {
		tr2[u] += val;
		tag[u] += val;
		return;
	}
	pushdown2(u);
	int mid = (l + r) >> 1;
	if (L <= mid) update2(u << 1, l, mid, L, R, val);
	if (R > mid) update2(u << 1 | 1, mid + 1, r, L, R, val);
	pushup2(u);
}

int query2(int u, int l, int r, int L, int R) {
	if (L <= l && r <= R) {
		return tr2[u];
	}
	pushdown2(u);
	int mid = (l + r) >> 1, res = INT_MAX;
	if (L <= mid) res = min(res, query2(u << 1, l, mid, L, R));
	if (R > mid) res = min(res, query2(u << 1 | 1, mid + 1, r, L, R));
	return res;
}

int n, q;

struct UPD {
	int u, a, b;
} U[N];

void __() {
	cin >> n >> q;
	vector<int> vec;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
		vec.push_back(a[i]);
		vec.push_back(b[i]);
	}
	for (int i = 1; i <= q; i++) {
		cin >> U[i].u >> U[i].a >> U[i].b;
		vec.push_back(U[i].a);
		vec.push_back(U[i].b);
	}
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	for (int i = 1; i <= n; i++) {
		a[i] = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin() + 1;
		b[i] = lower_bound(vec.begin(), vec.end(), b[i]) - vec.begin() + 1;
	}
	for (int i = 1; i <= q; i++) {
		U[i].a = lower_bound(vec.begin(), vec.end(), U[i].a) - vec.begin() + 1;
		U[i].b = lower_bound(vec.begin(), vec.end(), U[i].b) - vec.begin() + 1;
	}
	int cnt = vec.size();

	for (int i = 1; i <= n; i++) {
		add1(1, 1, cnt, b[i], a[i], i);
		if (b[i] < a[i]) update2(1, 1, cnt, b[i] + 1, a[i], 1);
	}
	int M = query1(1, 1, cnt, 1, cnt).first, A = query1(1, 1, cnt, M + 1, cnt).first, B = find1(1, 1, cnt, M);
	int ans = query1(1, 1, cnt, 1, M).second;
	if (M >= B) {
		ans--;
		if (A >= B) {
			ans++;
		} else {
			if (query2(1, 1, cnt, A + 1, B) > 0) {
				ans++;
			}
		}
	}
	cout << n - ans << '\n';

	for (int i = 1; i <= q; i++) {
		del1(1, 1, cnt, b[U[i].u], a[U[i].u], U[i].u);
		if (b[U[i].u] < a[U[i].u]) update2(1, 1, cnt, b[U[i].u] + 1, a[U[i].u], -1);
		a[U[i].u] = U[i].a;
		b[U[i].u] = U[i].b;
		add1(1, 1, cnt, b[U[i].u], a[U[i].u], U[i].u);
		if (b[U[i].u] < a[U[i].u]) update2(1, 1, cnt, b[U[i].u] + 1, a[U[i].u], 1);
		M = query1(1, 1, cnt, 1, cnt).first, A = query1(1, 1, cnt, M + 1, cnt).first, B = find1(1, 1, cnt, M);
		ans = query1(1, 1, cnt, 1, M).second;
		if (M >= B) {
			ans--;
			if (A >= B) {
				ans++;
			} else {
				if (query2(1, 1, cnt, A + 1, B) > 0) {
					ans++;
				}
			}
		}
		cout << n - ans << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	__();
	return 0;
}