#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 100;

struct Point {
	ll x, y, id;
	Point() {}
	Point(ll x, ll y) : x(x), y(y) {}
	Point(ll x, ll y, ll id) : x(x), y(y), id(id) {}
	Point operator-(const Point& other) const { return Point(x - other.x, y - other.y); }
	ll operator*(const Point& other) const { return x * other.x + y * other.y; }
	ll operator^(const Point& other) const { return x * other.y - y * other.x; }
	int are() const {
		Point op = Point(1, 0);
		ll x = op ^ *this, y = op * *this;
		if (x == 0 && y > 0) return 0;
		if (x > 0 && y > 0) return 1;
		if (x > 0 && y == 0) return 2;
		if (x > 0 && y < 0) return 3;
		if (x == 0 && y < 0) return 4;
		if (x < 0 && y < 0) return 5;
		if (x < 0 && y == 0) return 6;
		return 7;
	}
	bool operator<(const Point& other) const {
		int op1 = this->are(), op2 = other.are();
		if (op1 == op2) {
			if ((*this ^ other) == 0) return id < other.id;
			return (*this ^ other) > 0;
		}
		return op1 < op2;
	}
} p[N];

int n;
set<Point> st1, st2;

void add(int x) {
	if (x != 1) {
		Point op1 = p[x] - p[x - 1], op2 = p[x - 1] - p[x];
		op1.id = op2.id = x;
		if (op1 < op2)
			st1.insert(op1);
		else
			st1.insert(op2);
	}
	st2.insert(p[x]);
}

void del(int x) {
	if (x != n) {
		Point op1 = p[x] - p[x + 1], op2 = p[x + 1] - p[x];
		op1.id = op2.id = x + 1;
		if (op1 < op2)
			st1.erase(op1);
		else
			st1.erase(op2);
	}
	st2.erase(p[x]);
}

bool check() {
	if (st2.size() < 3) return 0;
	if ((*st1.begin() ^ *prev(st1.end())) == 0) return 0;
	if ((*st2.begin() ^ *prev(st2.end())) > 0) return 0;
	Point tp = *st2.begin();
	for (;;) {
		Point nxt;
		if (tp.are() >= 4)
			return 1;
		else
			nxt = *prev(st2.upper_bound(Point(-tp.x, -tp.y, 100000000)));
		if ((tp ^ nxt) == 0 && tp * nxt > 0) return 0;
		tp = nxt;
	}
}

void __() {
	st1.clear();
	st2.clear();
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> p[i].x >> p[i].y;
		p[i].id = i;
	}
	int l = 1, r = 0, ans = 100000000;
	while (l < n) {
		while (r < n && check() == 0) {
			r++;
			add(r);
		}
		if (check()) {
			ans = min(ans, r - l + 1);
			// cout << l << " " << r << "\n";
		}
		del(l);
		l++;
	}
	if (ans == 100000000)
		cout << "-1\n";
	else
		cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) __();
	return 0;
}