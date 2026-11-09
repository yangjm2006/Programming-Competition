#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Point {
	ll x, y, id;
	Point() {}
	Point(ll x, ll y) : x(x), y(y) {}
	Point(ll x, ll y, int id) : x(x), y(y), id(id) {}
	Point operator+(const Point& other) const { return Point(x + other.x, y + other.y); }
	Point& operator+=(const Point& other) { return *this = *this + other; }
	Point operator-(const Point& other) const { return Point(x - other.x, y - other.y); }
	bool operator<(const Point& other) const { return x < other.x || (x == other.x && y < other.y); }
	ll operator*(const Point& other) const { return x * other.x + y * other.y; }
	ll operator^(const Point& other) const { return x * other.y - y * other.x; }
	friend bool is_parallel(const Point& a, const Point& b) { return a.x * b.y == a.y * b.x; }
};
typedef Point Vector;

vector<Point> Convex_hull(vector<Point> p) {
	sort(p.begin(), p.end());
	vector<Point> ch;
	for (int i = 0; i < p.size(); i++) {
		while (ch.size() > 1 && ((ch[ch.size() - 1] - ch[ch.size() - 2]) ^ (p[i] - ch[ch.size() - 1])) <= 0)
			ch.pop_back();
		ch.push_back(p[i]);
	}
	int tmp = ch.size();
	for (int i = p.size() - 2; i >= 0; i--) {
		while (ch.size() > tmp && ((ch[ch.size() - 1] - ch[ch.size() - 2]) ^ (p[i] - ch[ch.size() - 1])) <= 0)
			ch.pop_back();
		ch.push_back(p[i]);
	}
	if (ch.size() > 1) ch.pop_back();
	return ch;
}

int in_Convex_hull(Vector p, const vector<Point>& ch) {
	int n = ch.size();
	p = p - ch[0];
	ll c1 = (ch[1] - ch[0]) ^ p, c2 = (ch[n - 1] - ch[0]) ^ p;
	if (c1 < 0 || c2 > 0) return -2;
	int l = 1, r = n - 2;
	while (l < r) {
		int mid = (l + r + 2) >> 1;
		if (((ch[mid] - ch[0]) ^ p) >= 0)
			l = mid;
		else
			r = mid - 1;
	}
	ll c3 = (ch[l + 1] - ch[l]) ^ (p + ch[0] - ch[l]);
	if (c3 < 0) return -2;
	if (c3 == 0 || c1 == 0 || c2 == 0) return -1;
	return l;
}

void __() {
	int n, q;
	cin >> n >> q;
	vector<Point> p;
	for (int i = 1; i <= n; i++) {
		ll x, y;
		cin >> x >> y;
		p.push_back(Point(x, y, i));
	}
	vector<Point> ch = Convex_hull(p), f1, f2;
	f1.push_back(ch[0]);
	f1.push_back(ch[1]);
	f1.push_back(ch[2]);
	f2.push_back(ch[1]);
	f2.push_back(ch[2]);
	f2.push_back(ch[3]);
	bool flg = 0;
	Point ansp;
	for (int i = 0; i < n; i++) {
		if (in_Convex_hull(p[i], f1) == -2 && in_Convex_hull(p[i], f2) == -2) {
			ansp = p[i];
			flg = 1;
			break;
		}
	}
	while (q--) {
		Point o;
		cin >> o.x >> o.y;
		int op = in_Convex_hull(o, ch);
		if (op == -2 || op == -1) {
			cout << "-1\n";
			continue;
		}
		vector<Point> Ch;
		Ch.push_back(ch[0]);
		Ch.push_back(ch[op]);
		Ch.push_back(ch[op + 1]);
		if (in_Convex_hull(o, Ch) > 0) {
			cout << 3 << '\n' << Ch[0].id << " " << Ch[1].id << " " << Ch[2].id << '\n';
			continue;
		}
		if (op != 1) {
			Ch.clear();
			Ch.push_back(ch[1]);
			Ch.push_back(ch[op]);
			Ch.push_back(ch[op + 1]);
			if (in_Convex_hull(o, Ch) > 0) {
				cout << 3 << '\n' << Ch[0].id << " " << Ch[1].id << " " << Ch[2].id << '\n';
				continue;
			}
		}
		if (op != 1) {
			Ch.clear();
			Ch.push_back(ch[0]);
			Ch.push_back(ch[op - 1]);
			Ch.push_back(ch[op + 1]);
			if (in_Convex_hull(o, Ch) > 0) {
				cout << 3 << '\n' << Ch[0].id << " " << Ch[1].id << " " << Ch[2].id << '\n';
				continue;
			}
		}
		if (flg) {
			cout << 3 << '\n' << ch[1].id << " " << ch[2].id << " " << ansp.id << '\n';
			continue;
		}
		cout << 4 << '\n' << ch[0].id << " " << ch[1].id << " " << ch[2].id << " " << ch[3].id << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) __();
	return 0;
}
