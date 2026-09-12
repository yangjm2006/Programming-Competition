#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

struct Point {
	ll x, y;
	int id;
	Point operator-(Point b) const { return {x - b.x, y - b.y, 0}; }
};

i128 cross(Point a, Point b) { return (i128)a.x * b.y - (i128)a.y * b.x; }
i128 cross(Point a, Point b, Point c) { return cross(b - a, c - a); }
int sign(i128 x) { return (x > 0) - (x < 0); }

bool onSegment(Point a, Point b, Point p) {
	return cross(a, b, p) == 0 && min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y &&
		   p.y <= max(a.y, b.y);
}

bool intersect(Point a, Point b, Point c, Point d) {
	if (onSegment(a, b, c) || onSegment(a, b, d) || onSegment(c, d, a) || onSegment(c, d, b)) return true;
	return sign(cross(a, b, c)) * sign(cross(a, b, d)) < 0 && sign(cross(c, d, a)) * sign(cross(c, d, b)) < 0;
}

// Counterclockwise convex hull; remove intermediate collinear points.
vector<Point> convexHull(vector<Point> a) {
	sort(a.begin(), a.end(), [](Point a, Point b) { return tie(a.x, a.y) < tie(b.x, b.y); });
	vector<Point> h;
	for (Point p : a) {
		while (h.size() > 1 && cross(h[h.size() - 2], h.back(), p) <= 0) h.pop_back();
		h.push_back(p);
	}
	int lowerSize = h.size();
	for (int i = (int)a.size() - 2; i >= 0; --i) {
		while ((int)h.size() > lowerSize && cross(h[h.size() - 2], h.back(), a[i]) <= 0) h.pop_back();
		h.push_back(a[i]);
	}
	h.pop_back();
	return h;
}

// -1: outside; 0: boundary; 1: strictly inside.
int location(const vector<Point>& h, Point p) {
	int k = h.size();
	if (k == 2) return onSegment(h[0], h[1], p) ? 0 : -1;
	i128 a = cross(h[0], h[1], p);
	i128 b = cross(h[0], h[k - 1], p);
	if (a < 0 || b > 0) return -1;
	if (a == 0) return onSegment(h[0], h[1], p) ? 0 : -1;
	if (b == 0) return onSegment(h[0], h[k - 1], p) ? 0 : -1;
	int l = 1, r = k - 1;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (cross(h[0], h[mid], p) >= 0)
			l = mid;
		else
			r = mid;
	}
	return sign(cross(h[l], h[r], p));
}

// Open CCW arc of directions d satisfying cross(d, b-p) > 0 for every b.
pair<Point, Point> separatingArc(const vector<Point>& h, Point p) {
	int k = h.size(), s, e;
	if (k == 2) {
		s = 0;
		e = 1;
		if (cross(h[0] - p, h[1] - p) > 0) swap(s, e);
	} else {
		auto edgeSign = [&](int i) { return sign(cross(h[i], h[(i + 1) % k], p)); };
		// Find the fan sector containing ray h[0] -> q.
		auto sector = [&](Point q) {
			int l = 1, r = k - 1;
			while (r - l > 1) {
				int mid = (l + r) / 2;
				if (cross(h[0], h[mid], q) >= 0)
					l = mid;
				else
					r = mid;
			}
			return l;
		};

		// v is a visible edge (<0); w is a strictly invisible edge (>0).
		int v, w;
		if (edgeSign(0) < 0)
			v = 0;
		else if (edgeSign(k - 1) < 0)
			v = k - 1;
		else
			v = sector(p);

		if (edgeSign(0) > 0)
			w = 0;
		else if (edgeSign(k - 1) > 0)
			w = k - 1;
		else
			w = sector({2 * h[0].x - p.x, 2 * h[0].y - p.y, 0});

		// Visible edges form one consecutive circular block.
		int l = 0, r = (w - v + k) % k;
		while (r - l > 1) {
			int mid = (l + r) / 2;
			if (edgeSign((v + mid) % k) < 0)
				l = mid;
			else
				r = mid;
		}
		e = (v + r) % k;

		l = 0;
		r = (v - w + k) % k;
		while (r - l > 1) {
			int mid = (l + r) / 2;
			if (edgeSign((w + mid) % k) < 0)
				r = mid;
			else
				l = mid;
		}
		s = (w + r) % k;
	}
	return {p - h[s], h[e] - p};
}

int half(Point a) { return a.y > 0 || (a.y == 0 && a.x > 0) ? 0 : 1; }
bool angleLess(Point a, Point b) {
	if (half(a) != half(b)) return half(a) < half(b);
	return cross(a, b) > 0;
}

struct Interval {
	int l, r, id;
};

array<int, 4> solve(vector<Point> a, vector<Point> b) {
	bool swapped = false;
	for (int turn = 0; turn < 2; ++turn) {
		vector<Point> h = convexHull(b);
		auto recover = [&](int x, int y) -> array<int, 4> {
			for (int i = 0; i < (int)h.size(); ++i) {
				Point u = h[i], v = h[(i + 1) % h.size()];
				if (intersect(a[x], a[y], u, v)) {
					array<int, 4> ans = {a[x].id, a[y].id, u.id, v.id};
					if (swapped) {
						swap(ans[0], ans[2]);
						swap(ans[1], ans[3]);
					}
					return ans;
				}
			}
			abort();  // Unreachable by the geometric proof.
		};

		int inside = -1, outside = -1;
		for (int i = 0; i < (int)a.size(); ++i) {
			int type = location(h, a[i]);
			if (type == 0) return recover(i, i == 0 ? 1 : 0);
			if (type > 0)
				inside = i;
			else
				outside = i;
		}
		if (inside >= 0 && outside >= 0) return recover(inside, outside);
		if (outside < 0) {
			swap(a, b);
			swapped = true;
			continue;
		}

		vector<Point> directions;
		vector<pair<Point, Point>> arcs;
		for (Point p : a) {
			auto arc = separatingArc(h, p);
			arcs.push_back(arc);
			directions.push_back(arc.first);
			directions.push_back(arc.second);
		}
		sort(directions.begin(), directions.end(), angleLess);
		directions.erase(unique(directions.begin(), directions.end(),
								[](Point a, Point b) { return !angleLess(a, b) && !angleLess(b, a); }),
						 directions.end());

		int K = directions.size();
		vector<Interval> intervals;
		for (int i = 0; i < (int)a.size(); ++i) {
			int l = lower_bound(directions.begin(), directions.end(), arcs[i].first, angleLess) - directions.begin();
			int r = lower_bound(directions.begin(), directions.end(), arcs[i].second, angleLess) - directions.begin();
			if (r <= l) r += K;
			intervals.push_back({l, r, i});
			intervals.push_back({l + K, r + K, i});
		}

		auto byEnd = intervals;
		sort(intervals.begin(), intervals.end(), [](Interval a, Interval b) { return a.l < b.l; });
		sort(byEnd.begin(), byEnd.end(), [](Interval a, Interval b) { return a.r < b.r; });
		int ptr = 0, best = -1;
		for (Interval cur : intervals) {
			while (ptr < (int)byEnd.size() && byEnd[ptr].r <= cur.l) {
				if (best < 0 || byEnd[ptr].l > byEnd[best].l) best = ptr;
				++ptr;
			}
			if (best >= 0 && byEnd[best].l >= cur.r - K) return recover(byEnd[best].id, cur.id);
		}
		return {-1, -1, -1, -1};
	}
	abort();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n;
		vector<Point> a(n);
		for (int i = 0; i < n; ++i) {
			cin >> a[i].x >> a[i].y;
			a[i].id = i + 1;
		}
		cin >> m;
		vector<Point> b(m);
		for (int i = 0; i < m; ++i) {
			cin >> b[i].x >> b[i].y;
			b[i].id = i + 1;
		}
		auto ans = solve(a, b);
		if (ans[0] < 0)
			cout << -1 << '\n';
		else
			cout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << ' ' << ans[3] << '\n';
	}
	return 0;
}
