#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 100;

struct Point {
	ll x, y;
	Point() {}
	Point(ll x, ll y) : x(x), y(y) {}

	Point operator+(const Point& other) const { return Point(x + other.x, y + other.y); }
	Point operator-(const Point& other) const { return Point(x - other.x, y - other.y); }
	ll operator*(const Point& other) const { return x * other.x + y * other.y; }
	ll operator^(const Point& other) const { return x * other.y - y * other.x; }
	bool operator<(const Point& other) const { return (*this ^ other) > 0; }

	ll cross(const Point& a, const Point& b) const { return (a - *this) ^ (b - *this); }
} p[N];

void __() {
	int n;
	cin >> n;
	Point P, Q;
	cin >> P.x >> P.y >> Q.x >> Q.y;
	for (int i = 1; i <= n; i++) cin >> p[i].x >> p[i].y;
	vector<Point> vecp1, vecp2, vecq1, vecq2;
	for (int i = 1; i <= n; i++) {
		if (P.cross(Q, p[i]) > 0) {
			vecp1.push_back(p[i] - P);
			vecq1.push_back(p[i] - Q);
		} else {
			vecp2.push_back(p[i] - P);
			vecq2.push_back(p[i] - Q);
		}
	}
	sort(vecp1.begin(), vecp1.end());
	sort(vecp2.begin(), vecp2.end());
	sort(vecq1.begin(), vecq1.end());
	sort(vecq2.begin(), vecq2.end());

	auto cal = [&](Point O, Point R, const vector<Point>& vec) -> int {
		int l = 0, r = vec.size();
		while (l < r) {
			int mid = l + r >> 1;
			if (((R - O) ^ vec[mid]) > 0)
				l = mid + 1;
			else
				r = mid;
		}
		return l;
	};

	ll ans = 0, m1 = vecp1.size(), m2 = vecp2.size();
	for (int i = 1; i <= n; i++) {
		if (P.cross(Q, p[i]) > 0) {
			ll g = abs(cal(P, p[i], vecp2) - cal(Q, p[i], vecq2));
			ans += g * (m2 - g);
		} else {
			ll g = abs(cal(P, p[i], vecp1) - cal(Q, p[i], vecq1));
			ans += g * (m1 - g);
		}
	}
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