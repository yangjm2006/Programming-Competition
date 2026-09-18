#include <bits/stdc++.h>
using namespace std;

int k1, k2;

struct Hash {
	size_t operator()(const int& v) const {
		size_t h = v * 131;
		return h;
	}
};

void solve() {
	int n, q, cur = 0, ouput = 0;
	cin >> n;
	unordered_map<int, int, Hash> A, ans;
	for (int i = 1, t; i <= n; i++) {
		cin >> t;
		A[t]++;
	}
	for (int i = 0; i <= n; i++) {
		if (A.count(i)) {
			cur++;
			int temp1 = A[i]--;
			if (temp1 == 1) {
				A.erase(i);
			}
		} else {
			break;
		}
	}
	vector<int> temp;
	for (auto& [val, qqq] : A) {
		temp.push_back(val);
	}
	vector<int> del;
	for (auto& val : temp) {
		del.clear();
		int k = cur + val;
		int kcur = cur;
		for (int i = cur; i <= n; i++) {
			if (A.count(i)) {
				kcur++;
				int temp1 = A[i]--;
				del.push_back(i);
				if (temp1 == 1) {
					A.erase(i);
				}
			} else if (A.count(k - i)) {
				kcur++;
				int temp1 = A[k - i]--;
				del.push_back(k - i);
				if (temp1 == 1) {
					A.erase(k - i);
				}
			} else {
				break;
			}
		}
		for (auto& i : del) {
			A[i]++;
		}
		ans[k] = kcur;
	}
	cin >> q;
	for (int i = 1, t; i <= q; i++) {
		cin >> t;
		if (ans.count(t)) {
			ouput ^= ans[t];
		} else {
			ouput ^= cur;
		}
	}
	cout << ouput << "\n";
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	srand(time(nullptr));
	k1 = rand() % 5 + 3;
	k2 = rand() % 5 + 1;
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}