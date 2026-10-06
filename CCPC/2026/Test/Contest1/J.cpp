#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2020;

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
ll n, a[N];
int main(int argc, char* argv[]) {
	ll id = argc > 1 ? atoi(argv[1]) : 0;
	if (id == 0) {
		int n;
		cin >> n;
		vector<Point> vec;
		for (int i = 1; i <= n; i++) {
			Point p;
			cin >> p.x >> p.y;
			vec.push_back(p);
		}
		cin >> n;
		for (int i = 1; i <= n; i++) {
			Point p;
			cin >> p.x >> p.y;
			vec.push_back(p);
		}
		cin >> n;
		for (int i = 1; i <= n; i++) {
			Point p;
			cin >> p.x >> p.y;
			vec.push_back(p);
		}
		cin >> n;
		for (int i = 1; i <= n; i++) {
			Point p;
			cin >> p.x >> p.y;
			vec.push_back(p);
		}
		vec = Convex_hull(vec);
		cout << vec.size() << endl;
		ll ans1 = 0, ans2 = 0;
		for (int i = 0; i < vec.size(); i++) {
			ans1 += (vec[i] ^ vec[(i + 1) % vec.size()]);
			ans2 += (vec[i] - vec[(i + 1) % vec.size()]) * (vec[i] - vec[(i + 1) % vec.size()]);
		}
		cout << ans1 << endl << ans2 << endl;
	} else {
		int n;
		cin >> n;
		vector<Point> vec;
		for (int i = 1; i <= n; i++) {
			Point p;
			cin >> p.x >> p.y;
			vec.push_back(p);
		}
		vec = Convex_hull(vec);
		cout << vec.size() << endl;
		for (Point p : vec) {
			cout << p.x << " " << p.y << endl;
		}
	}
	return 0;
}
