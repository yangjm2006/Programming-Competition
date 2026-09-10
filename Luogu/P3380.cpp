#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 100;
const int INF = 2147483647;
int rng() {
	static int x = 11451419;
	x ^= x << 13;
	x ^= x << 17;
	x ^= x << 5;
	return x;
}
class Treap {
private:
	struct Treap_Node {
		Treap_Node* ch[2];
		int val, prio, cnt, siz;

		Treap_Node(int val) : val(val), cnt(1), siz(1) {
			ch[0] = ch[1] = nullptr;
			prio = rng();
		}

		void update_size() {
			siz = cnt;
			if (ch[0] != nullptr) siz += ch[0]->siz;
			if (ch[1] != nullptr) siz += ch[1]->siz;
		}
	};

	Treap_Node* root = nullptr;

	const bool LEFT = 1;
	const bool RIGHT = 0;

	void Treap_Rotate(Treap_Node*& cur, bool dir) {
		Treap_Node* tmp = cur->ch[dir];
		cur->ch[dir] = tmp->ch[!dir];
		tmp->ch[!dir] = cur;
		cur->update_size();
		tmp->update_size();
		cur = tmp;
	}

	void Treap_Insert(Treap_Node*& cur, int val) {
		if (cur == nullptr) {
			cur = new Treap_Node(val);
			return;
		} else if (val == cur->val) {
			cur->cnt++;
			cur->siz++;
		} else if (val < cur->val) {
			Treap_Insert(cur->ch[0], val);
			if (cur->ch[0]->prio < cur->prio) {
				Treap_Rotate(cur, RIGHT);
			}
			cur->update_size();
		} else {
			Treap_Insert(cur->ch[1], val);
			if (cur->ch[1]->prio < cur->prio) {
				Treap_Rotate(cur, LEFT);
			}
			cur->update_size();
		}
	}

	void Treap_Delete(Treap_Node*& cur, int val) {
		if (cur == nullptr) return;
		if (val < cur->val) {
			Treap_Delete(cur->ch[0], val);
			cur->update_size();
			return;
		} else if (val > cur->val) {
			Treap_Delete(cur->ch[1], val);
			cur->update_size();
			return;
		} else {
			if (cur->cnt > 1) {
				cur->cnt--;
				cur->siz--;
				return;
			}
		}

		int state = 0;
		state |= (cur->ch[0] != nullptr);
		state |= ((cur->ch[1] != nullptr) << 1);
		Treap_Node* tmp = cur;
		switch (state) {
			case 0:
				delete cur;
				cur = nullptr;
				break;
			case 1:
				cur = tmp->ch[0];
				delete tmp;
				break;
			case 2:
				cur = tmp->ch[1];
				delete tmp;
				break;
			case 3:
				bool dir = cur->ch[0]->prio < cur->ch[1]->prio ? RIGHT : LEFT;
				Treap_Rotate(cur, dir);
				Treap_Delete(cur->ch[!dir], val);
				cur->update_size();
				break;
		}
	}

	int Treap_Query_Rank(Treap_Node* cur, int val) {
		if (cur == nullptr) return 1;
		int less_size = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
		if (val == cur->val) {
			return less_size + 1;
		} else if (val < cur->val) {
			return Treap_Query_Rank(cur->ch[0], val);
		} else {
			return less_size + cur->cnt + Treap_Query_Rank(cur->ch[1], val);
		}
	}

	int Treap_Query_Value(Treap_Node* cur, int rank) {
		int less_size = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
		if (rank <= less_size)
			return Treap_Query_Value(cur->ch[0], rank);
		else if (rank > less_size + cur->cnt)
			return Treap_Query_Value(cur->ch[1], rank - less_size - cur->cnt);
		else
			return cur->val;
	}

	int Treap_Query_Prev(Treap_Node* cur, int val) {
		int ans = -INF;
		while (cur != nullptr) {
			if (cur->val < val) {
				ans = cur->val;
				cur = cur->ch[1];
			} else {
				cur = cur->ch[0];
			}
		}
		return ans;
	}

	int Treap_Query_Next(Treap_Node* cur, int val) {
		int ans = INF;
		while (cur != nullptr) {
			if (cur->val > val) {
				ans = cur->val;
				cur = cur->ch[0];
			} else {
				cur = cur->ch[1];
			}
		}
		return ans;
	}

public:
	void insert(int val) { Treap_Insert(root, val); }
	void del(int val) { Treap_Delete(root, val); }
	int query_rank(int val) { return Treap_Query_Rank(root, val); }
	int query_val(int rank) { return Treap_Query_Value(root, rank); }
	int query_prev(int val) { return Treap_Query_Prev(root, val); }
	int query_next(int val) { return Treap_Query_Next(root, val); }
};

class Tree {
private:
	Treap tr[N << 2];

	void Tree_Insert(int u, int l, int r, int pos, int val) {
		tr[u].insert(val);
		if (l == r) return;
		int mid = l + r >> 1;
		if (pos <= mid)
			Tree_Insert(u << 1, l, mid, pos, val);
		else
			Tree_Insert(u << 1 | 1, mid + 1, r, pos, val);
	}

	void Tree_Delete(int u, int l, int r, int pos, int val) {
		tr[u].del(val);
		if (l == r) return;
		int mid = l + r >> 1;
		if (pos <= mid)
			Tree_Delete(u << 1, l, mid, pos, val);
		else
			Tree_Delete(u << 1 | 1, mid + 1, r, pos, val);
	}

	int Tree_Query_Rank(int u, int l, int r, int L, int R, int val) {
		if (l >= L && r <= R) return tr[u].query_rank(val) - 1;
		int mid = l + r >> 1, res = 0;
		if (L <= mid) res += Tree_Query_Rank(u << 1, l, mid, L, R, val);
		if (R > mid) res += Tree_Query_Rank(u << 1 | 1, mid + 1, r, L, R, val);
		return res;
	}

	int Tree_Query_Prev(int u, int l, int r, int L, int R, int val) {
		if (l >= L && r <= R) return tr[u].query_prev(val);
		int mid = l + r >> 1, res = -INF;
		if (L <= mid) res = max(res, Tree_Query_Prev(u << 1, l, mid, L, R, val));
		if (R > mid) res = max(res, Tree_Query_Prev(u << 1 | 1, mid + 1, r, L, R, val));
		return res;
	}

	int Tree_Query_Next(int u, int l, int r, int L, int R, int val) {
		if (l >= L && r <= R) return tr[u].query_next(val);
		int mid = l + r >> 1, res = INF;
		if (L <= mid) res = min(res, Tree_Query_Next(u << 1, l, mid, L, R, val));
		if (R > mid) res = min(res, Tree_Query_Next(u << 1 | 1, mid + 1, r, L, R, val));
		return res;
	}

public:
	int n;

	void insert(int pos, int val) { Tree_Insert(1, 1, n, pos, val); }
	void del(int pos, int val) { Tree_Delete(1, 1, n, pos, val); }
	int query_rank(int L, int R, int val) { return Tree_Query_Rank(1, 1, n, L, R, val) + 1; }
	int query_val(int L, int R, int rank) {
		int l = 0, r = 1e8;
		while (l < r) {
			int mid = (l + r >> 1) + 1;
			if (query_rank(L, R, mid) <= rank)
				l = mid;
			else
				r = mid - 1;
		}
		return l;
	}
	int query_prev(int L, int R, int val) { return Tree_Query_Prev(1, 1, n, L, R, val); }
	int query_next(int L, int R, int val) { return Tree_Query_Next(1, 1, n, L, R, val); }
} tree;

int a[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	tree.n = n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		tree.insert(i, a[i]);
	}
	while (m--) {
		int op, l, r, k;
		cin >> op;
		switch (op) {
			case 1:
				cin >> l >> r >> k;
				cout << tree.query_rank(l, r, k) << '\n';
				break;
			case 2:
				cin >> l >> r >> k;
				cout << tree.query_val(l, r, k) << '\n';
				break;
			case 3:
				cin >> l >> k;
				tree.del(l, a[l]);
				tree.insert(l, k);
				a[l] = k;
				break;
			case 4:
				cin >> l >> r >> k;
				cout << tree.query_prev(l, r, k) << '\n';
				break;
			case 5:
				cin >> l >> r >> k;
				cout << tree.query_next(l, r, k) << '\n';
				break;
		}
	}
	return 0;
}