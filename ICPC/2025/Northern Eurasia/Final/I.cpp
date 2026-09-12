#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Point {
	ll x, y, id;
	Point() {}
	Point(ll x, ll y) : x(x), y(y) {}
	Point(ll x, ll y, int id) : x(x), y(y), id(id) {}
	Point operator+(const Point& other) const { return Point(x + other.x, y + other.y); }
	Point& operator+=(const Point& other) { return *this = *this + other; }
	Point operator-(const Point& other) const { return Point(x - other.x, y - other.y); }
	bool operator<(const Point& other) const { return x < other.x || (x == other.x && y < other.y); }
	bool operator==(const Point& other) const { return x == other.x && y == other.y; }
	ll operator*(const Point& other) const { return x * other.x + y * other.y; }
	ll operator^(const Point& other) const { return x * other.y - y * other.x; }
	friend bool is_parallel(const Point& a, const Point& b) { return a.x * b.y == a.y * b.x; }
};
typedef Point Vector;

int sgn(ll x) { return (x > 0) - (x < 0); }

bool on_Segment(const Point& p, const Point& a, const Point& b) {
	return ((a - p) ^ (b - p)) == 0 && min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y &&
		   p.y <= max(a.y, b.y);
}

bool Intersect(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
	if (on_Segment(b1, a1, a2) || on_Segment(b2, a1, a2) || on_Segment(a1, b1, b2) || on_Segment(a2, b1, b2)) return 1;
	return sgn((b1 - a1) ^ (b2 - a1)) * sgn((b1 - a2) ^ (b2 - a2)) < 0 &&
		   sgn((a1 - b1) ^ (a2 - b1)) * sgn((a1 - b2) ^ (a2 - b2)) < 0;
}

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

// outside:-1; boundary:0; inside:1
int Location(const Point& p, const vector<Point>& ch) {
	if (ch.size() == 1) return p == ch[0] ? 0 : -1;
	if (ch.size() == 2) return on_Segment(p, ch[0], ch[1]) ? 0 : -1;
	ll a = (ch[1] - ch[0]) ^ (p - ch[0]), b = (ch[ch.size() - 1] - ch[0]) ^ (p - ch[0]);
	if (a < 0 || b > 0) return -1;
	if (a == 0) return on_Segment(p, ch[0], ch[1]) ? 0 : -1;
	if (b == 0) return on_Segment(p, ch[0], ch[ch.size() - 1]) ? 0 : -1;
	int l = 1, r = ch.size() - 2;
	while (l < r) {
		int mid = (l + r >> 1) + 1;
		if (((ch[mid] - ch[0]) ^ (p - ch[0])) >= 0)
			l = mid;
		else
			r = mid - 1;
	}
	return ((ch[l + 1] - ch[l]) ^ (p - ch[l]));
}

int work1(const vector<Point>& ch1, const vector<Point>& ch2) {
	bool flg1 = 0, flg2 = 0;
	Point p1, p2;
	int n = ch1.size(), m = ch2.size();
	for (int i = 0; i < m; i++) {
		int L = Location(ch2[i], ch1);
		if (L == 1) {
			flg1 = 1;
			p1 = ch2[i];
		} else if (L == -1) {
			flg2 = 1;
			p2 = ch2[i];
		} else {
			flg1 = flg2 = 1;
			p1 = ch2[i];
			p2 = ch2[(i + 1) % m];
		}
	}
	if (flg1 && flg2) {
		for (int i = 0; i < n; i++) {
			if (Intersect(p1, p2, ch1[i], ch1[(i + 1) % n])) {
				cout << p1.id << " " << p2.id << " " << ch1[i].id << " " << ch1[(i + 1) % n].id << '\n';
			}
		}
		return 1;
	}
	if (flg1) return 2;
	return 3;
}

pair<Point, Point> Find_Tangent(Point p, const vector<Point>& ch) {}

void work2() {}

void __() {
	int n, m;
	vector<Point> p1, p2, ch1, ch2;
	cin >> n;
	for (int i = 1, x, y; i <= n; i++) {
		cin >> x >> y;
		p1.push_back(Point(x, y, i));
	}
	ch1 = Convex_hull(p1);
	cin >> m;
	for (int i = 1, x, y; i <= m; i++) {
		cin >> x >> y;
		p2.push_back(Point(x, y, i));
	}
	ch2 = Convex_hull(p2);
	int flg1 = work1(ch1, ch2);
	if (flg1 == 1) return;
	if (flg1 == 2) {
		int flg2 = work1(ch2, ch1);
		if (flg2 == 1) return;
	}
	work2();
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) __();
	return 0;
}