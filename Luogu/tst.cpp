#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

ull mask(int len) {
	if (len <= 0) return 0;
	if (len >= 64) return ~0ULL;
	return (1ULL << len) - 1;
}

ull rev64(ull x) {
	x = ((x & 0x5555555555555555ULL) << 1) | ((x >> 1) & 0x5555555555555555ULL);
	x = ((x & 0x3333333333333333ULL) << 2) | ((x >> 2) & 0x3333333333333333ULL);
	x = ((x & 0x0f0f0f0f0f0f0f0fULL) << 4) | ((x >> 4) & 0x0f0f0f0f0f0f0f0fULL);
	x = ((x & 0x00ff00ff00ff00ffULL) << 8) | ((x >> 8) & 0x00ff00ff00ff00ffULL);
	x = ((x & 0x0000ffff0000ffffULL) << 16) | ((x >> 16) & 0x0000ffff0000ffffULL);
	return (x << 32) | (x >> 32);
}

ull rev(ull x, int len) { return rev64(x) >> (64 - len); }

struct DS {
	int n, B;
	vector<ull> full, a;
	vector<unsigned char> has0, has1;
	vector<signed char> tag;

	DS(string s) {
		n = s.size();
		B = (n + 63) / 64;
		full.resize(B);
		a.assign(B, 0);
		for (int b = 0; b < B; b++) {
			int len = min(64, n - b * 64);
			full[b] = mask(len);
		}
		for (int i = 0; i < n; i++)
			if (s[i] == 'H') a[i / 64] |= 1ULL << (i % 64);

		has0.resize(4 * B + 5);
		has1.resize(4 * B + 5);
		tag.assign(4 * B + 5, -1);
		build(1, 0, B - 1);
	}

	void pull(int p) {
		has0[p] = has0[p * 2] | has0[p * 2 + 1];
		has1[p] = has1[p * 2] | has1[p * 2 + 1];
	}

	void build(int p, int l, int r) {
		if (l == r) {
			has0[p] = (a[l] != full[l]);
			has1[p] = (a[l] != 0);
			return;
		}
		int m = (l + r) / 2;
		build(p * 2, l, m);
		build(p * 2 + 1, m + 1, r);
		pull(p);
	}

	void apply(int p, int l, int r, int v) {
		has0[p] = !v;
		has1[p] = v;
		tag[p] = v;
		if (l == r) a[l] = v ? full[l] : 0;
	}

	void push(int p, int l, int r) {
		if (tag[p] == -1 || l == r) return;
		int m = (l + r) / 2;
		apply(p * 2, l, m, tag[p]);
		apply(p * 2 + 1, m + 1, r, tag[p]);
		tag[p] = -1;
	}

	void assignBlock(int p, int l, int r, int ql, int qr, int v) {
		if (ql <= l && r <= qr) {
			apply(p, l, r, v);
			return;
		}
		push(p, l, r);
		int m = (l + r) / 2;
		if (ql <= m) assignBlock(p * 2, l, m, ql, qr, v);
		if (qr > m) assignBlock(p * 2 + 1, m + 1, r, ql, qr, v);
		pull(p);
	}

	void assignBlock(int l, int r, int v) {
		if (l <= r) assignBlock(1, 0, B - 1, l, r, v);
	}

	ull getBlock(int p, int l, int r, int x) {
		if (l == r) return a[l];
		push(p, l, r);
		int m = (l + r) / 2;
		if (x <= m) return getBlock(p * 2, l, m, x);
		return getBlock(p * 2 + 1, m + 1, r, x);
	}

	ull getBlock(int x) { return getBlock(1, 0, B - 1, x); }

	void setBlock(int p, int l, int r, int x, ull v) {
		if (l == r) {
			a[l] = v & full[l];
			has0[p] = (a[l] != full[l]);
			has1[p] = (a[l] != 0);
			tag[p] = -1;
			return;
		}
		push(p, l, r);
		int m = (l + r) / 2;
		if (x <= m)
			setBlock(p * 2, l, m, x, v);
		else
			setBlock(p * 2 + 1, m + 1, r, x, v);
		pull(p);
	}

	void setBlock(int x, ull v) { setBlock(1, 0, B - 1, x, v); }

	int findFirstBlock(int p, int l, int r, int ql, int qr, int v) {
		if (r < ql || qr < l) return -1;
		if (v && !has1[p]) return -1;
		if (!v && !has0[p]) return -1;
		if (l == r) return l;
		push(p, l, r);
		int m = (l + r) / 2;
		int x = findFirstBlock(p * 2, l, m, ql, qr, v);
		if (x != -1) return x;
		return findFirstBlock(p * 2 + 1, m + 1, r, ql, qr, v);
	}

	int findLastBlock(int p, int l, int r, int ql, int qr, int v) {
		if (r < ql || qr < l) return -1;
		if (v && !has1[p]) return -1;
		if (!v && !has0[p]) return -1;
		if (l == r) return l;
		push(p, l, r);
		int m = (l + r) / 2;
		int x = findLastBlock(p * 2 + 1, m + 1, r, ql, qr, v);
		if (x != -1) return x;
		return findLastBlock(p * 2, l, m, ql, qr, v);
	}

	int findFirstBlock(int l, int r, int v) {
		if (l > r) return -1;
		return findFirstBlock(1, 0, B - 1, l, r, v);
	}

	int findLastBlock(int l, int r, int v) {
		if (l > r) return -1;
		return findLastBlock(1, 0, B - 1, l, r, v);
	}

	void assignPos(int l, int r, int v) {
		if (l > r) return;

		int bl = l / 64, br = r / 64;
		if (bl == br) {
			ull x = getBlock(bl);
			ull m = mask(r % 64 + 1) & (~0ULL << (l % 64));
			if (v)
				x |= m;
			else
				x &= ~m;
			setBlock(bl, x);
			return;
		}

		ull x = getBlock(bl);
		ull m = (~0ULL << (l % 64)) & full[bl];
		if (v)
			x |= m;
		else
			x &= ~m;
		setBlock(bl, x);

		x = getBlock(br);
		m = mask(r % 64 + 1) & full[br];
		if (v)
			x |= m;
		else
			x &= ~m;
		setBlock(br, x);

		assignBlock(bl + 1, br - 1, v);
	}

	ull getBits(int l, int len) {
		int b = l / 64, o = l % 64;
		if (o + len <= 64) return (getBlock(b) >> o) & mask(len);

		int x = 64 - o;
		return (getBlock(b) >> o) | ((getBlock(b + 1) & mask(len - x)) << x);
	}

	void setBits(int l, int len, ull x) {
		int b = l / 64, o = l % 64;

		if (o + len <= 64) {
			ull v = getBlock(b);
			ull m = mask(len) << o;
			v = (v & ~m) | ((x & mask(len)) << o);
			setBlock(b, v);
			return;
		}

		int t = 64 - o;

		ull v = getBlock(b);
		ull m = mask(t) << o;
		v = (v & ~m) | ((x & mask(t)) << o);
		setBlock(b, v);

		v = getBlock(b + 1);
		m = mask(len - t);
		v = (v & ~m) | ((x >> t) & m);
		setBlock(b + 1, v);
	}

	int findFirst(int l, int r, int v) {
		int bl = l / 64, br = r / 64;

		auto calc = [&](int b, ull m) {
			ull x = getBlock(b);
			x = v ? (x & m) : ((~x) & m);
			if (!x) return -1;
			return b * 64 + __builtin_ctzll(x);
		};

		if (bl == br) return calc(bl, mask(r % 64 + 1) & (~0ULL << (l % 64)));

		int x = calc(bl, (~0ULL << (l % 64)) & full[bl]);
		if (x != -1) return x;

		int b = findFirstBlock(bl + 1, br - 1, v);
		if (b != -1) return calc(b, full[b]);

		return calc(br, mask(r % 64 + 1) & full[br]);
	}

	int findLast(int l, int r, int v) {
		int bl = l / 64, br = r / 64;

		auto calc = [&](int b, ull m) {
			ull x = getBlock(b);
			x = v ? (x & m) : ((~x) & m);
			if (!x) return -1;
			return b * 64 + 63 - __builtin_clzll(x);
		};

		if (bl == br) return calc(bl, mask(r % 64 + 1) & (~0ULL << (l % 64)));

		int x = calc(br, mask(r % 64 + 1) & full[br]);
		if (x != -1) return x;

		int b = findLastBlock(bl + 1, br - 1, v);
		if (b != -1) return calc(b, full[b]);

		return calc(bl, (~0ULL << (l % 64)) & full[bl]);
	}

	string getString() {
		string s(n, 'N');
		for (int b = 0; b < B; b++) {
			ull x = getBlock(b);
			for (int j = 0; j < 64 && b * 64 + j < n; j++)
				if (x >> j & 1) s[b * 64 + j] = 'H';
		}
		return s;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, T;
	cin >> n >> T;

	string s;
	cin >> s;

	DS ds(s);

	const ull MOD = 1ULL << 60;
	const ull MASK = MOD - 1;

	while (T--) {
		int op, p;
		ull k;
		cin >> op >> p >> k;
		--p;

		if (k == 0) continue;

		bool right = op <= 2;
		bool add = (op == 1 || op == 3);

		int L = right ? n - p : p + 1;
		int len = min(L, 60);
		int l = right ? p : p - len + 1;

		ull x = ds.getBits(l, len);
		if (!right) x = rev(x, len);

		ull y;
		bool carry = false;

		if (L <= 60) {
			ull m = mask(L);
			k &= m;
			if (add)
				y = (x + k) & m;
			else
				y = (x - k) & m;
		} else if (add) {
			ull z = x + k;
			carry = z >= MOD;
			y = z & MASK;
		} else {
			if (x >= k)
				y = x - k;
			else {
				y = x + MOD - k;
				carry = true;
			}
		}

		ds.setBits(l, len, right ? y : rev(y, len));

		if (!carry) continue;

		if (right) {
			int l = p + 60, r = n - 1;

			if (add) {
				int q = ds.findFirst(l, r, 0);
				if (q == -1)
					ds.assignPos(l, r, 0);
				else {
					ds.assignPos(l, q - 1, 0);
					ds.assignPos(q, q, 1);
				}
			} else {
				int q = ds.findFirst(l, r, 1);
				if (q == -1)
					ds.assignPos(l, r, 1);
				else {
					ds.assignPos(l, q - 1, 1);
					ds.assignPos(q, q, 0);
				}
			}
		} else {
			int l = 0, r = p - 60;

			if (add) {
				int q = ds.findLast(l, r, 0);
				if (q == -1)
					ds.assignPos(l, r, 0);
				else {
					ds.assignPos(q + 1, r, 0);
					ds.assignPos(q, q, 1);
				}
			} else {
				int q = ds.findLast(l, r, 1);
				if (q == -1)
					ds.assignPos(l, r, 1);
				else {
					ds.assignPos(q + 1, r, 1);
					ds.assignPos(q, q, 0);
				}
			}
		}
	}

	cout << ds.getString() << '\n';
}