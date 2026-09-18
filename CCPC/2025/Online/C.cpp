#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e5 + 10;
int n;
ll k, a[N];
struct Edge {
	ll w;
	int u, v;
	bool operator<(const Edge& other) const { return w > other.w; }
};
bool vis[N];
void __() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i] %= k;
		vis[i] = 0;
	}
	sort(a + 1, a + 1 + n);
	set<pair<ll, int>> st;
	priority_queue<Edge> q;
	for (int i = 2; i <= n; i++) {
		st.insert({a[i], i});
	}
	q.push({(a[1] + a[2]) % k, 1, 2});
	auto it = st.lower_bound({k - a[1], 0});
	if (it != st.end()) q.push({((*it).first + a[1]) % k, 1, (*it).second});
	vis[1] = 1;
	ll sum = 0;
	int cnt = 1;
	while (cnt < n) {
		int u = q.top().u, v = q.top().v;
		ll w = q.top().w;
		q.pop();
		if (vis[v]) {
			if ((*st.begin()).second == v) {
				q.push({((*st.begin()).first + a[u]) % k, u, (*st.begin()).second});
			} else {
				auto it = st.lower_bound({k - a[u], 0});
				if (it != st.end()) q.push({((*it).first + a[u]) % k, u, (*it).second});
			}
			continue;
		}
		vis[v] = 1;
		sum += w;
		if ((*st.begin()).second == v) {
			st.erase(st.lower_bound({a[v], 0}));
			q.push({((*st.begin()).first + a[u]) % k, u, (*st.begin()).second});
		} else {
			st.erase(st.lower_bound({a[v], 0}));
			auto it = st.lower_bound({k - a[u], 0});
			if (it != st.end()) q.push({((*it).first + a[u]) % k, u, (*it).second});
		}
		q.push({((*st.begin()).first + a[v]) % k, v, (*st.begin()).second});
		auto it = st.lower_bound({k - a[v], 0});
		if (it != st.end()) q.push({((*it).first + a[v]) % k, v, (*it).second});
		cnt++;
	}
	cout << sum << '\n';
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) __();
	return 0;
}