#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
	ll x, y;
	Point() {}
	Point(ll x, ll y) : x(x), y(y) {}
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

ll Sum(vector<Point> p) {
	ll sum = 0;
	for (int i = 0; i < p.size(); i++) {
		sum += (p[i] ^ p[(i + 1) % p.size()]);
	}
	return abs(sum);
}

vector<Point> Mincowsky(vector<Point> p1, vector<Point> p2) {
	vector<Vector> v, sum;
	int n1 = p1.size(), n2 = p2.size();
	for (int i = 0, j = 0;; i++) {
		while (j < n2 && ((p2[(j + 1) % n2] - p2[j]) ^ (p1[(i + 1) % n1] - p1[i])) >= 0) {
			v.push_back(p2[(j + 1) % n2] - p2[j]);
			j++;
		}
		v.push_back(p1[(i + 1) % n1] - p1[i]);
		if (i == n1 - 1) {
			while (j < n2) {
				v.push_back(p2[(j + 1) % n2] - p2[j]);
				j++;
			}
			break;
		}
	}
	sum.push_back(p1[0] + p2[0]);
	sum.push_back(sum[0] + v[0]);
	for (int i = 1; i < n1 + n2; i++) {
		if (is_parallel(v[i], v[i - 1])) {
			sum[sum.size() - 1] += v[i];
		} else {
			sum.push_back(sum[sum.size() - 1] + v[i]);
		}
	}
	if (sum.size() > 1) sum.pop_back();
	return sum;
}

void __() {
	vector<Point> p1, p2, ch1, ch2;
	int n, m;
	cin >> n >> m;
	for (int i = 0, x, y; i < n; i++) {
		cin >> x >> y;
		p1.push_back(Point(x, y));
	}
	for (int i = 0, x, y; i < m; i++) {
		cin >> x >> y;
		p2.push_back(Point(-x, -y));
	}
	ch1 = Convex_hull(p1);
	ch2 = Convex_hull(p2);
	cout << fixed << setprecision(9) << 0.5 * Sum(ch1) / Sum(Mincowsky(ch1, ch2)) * Sum(ch2) << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) __();
	return 0;
}
