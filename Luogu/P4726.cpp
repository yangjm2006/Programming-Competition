#include <bits/stdc++.h>
using namespace std;

namespace poly {
	using i64 = long long;
	using u64 = unsigned long long;
	using Poly = std::vector<int>;
	constexpr int MOD = 998244353, ROOT = 3, MAX_NTT = 1 << 23;
	inline int norm(i64 x) {
		x %= MOD;
		return int(x < 0 ? x + MOD : x);
	}
	inline int power(int a, u64 e) {
		int r = 1;
		for (; e; e >>= 1, a = int(i64(a) * a % MOD))
			if (e & 1) r = int(i64(r) * a % MOD);
		return r;
	}
	inline int inverse(int x) {
		if (!x) throw std::domain_error("inverse of zero");
		return power(x, MOD - 2);
	}
	inline void trim(Poly& a) {
		while (!a.empty() && !a.back()) a.pop_back();
	}
	inline Poly cut(Poly a, int n) {
		if (n < 0) throw std::invalid_argument("negative precision");
		a.resize(n);
		return a;
	}
	inline Poly add(const Poly& a, const Poly& b) {
		Poly c(std::max(a.size(), b.size()));
		for (int i = 0; i < int(c.size()); ++i) {
			int x = i < int(a.size()) ? a[i] : 0;
			int y = i < int(b.size()) ? b[i] : 0;
			c[i] = x + y;
			if (c[i] >= MOD) c[i] -= MOD;
		}
		return c;
	}
	inline Poly sub(const Poly& a, const Poly& b) {
		Poly c(std::max(a.size(), b.size()));
		for (int i = 0; i < int(c.size()); ++i) {
			int x = i < int(a.size()) ? a[i] : 0;
			int y = i < int(b.size()) ? b[i] : 0;
			c[i] = x - y;
			if (c[i] < 0) c[i] += MOD;
		}
		return c;
	}
	inline Poly scale(Poly a, int c) {
		for (int& x : a) x = int(i64(x) * c % MOD);
		return a;
	}
	inline void ntt(Poly& a, bool invert = false) {
		int n = int(a.size());
		if (!n || (n & (n - 1)) || n > MAX_NTT) throw std::invalid_argument("NTT length must be a power of 2 <= 2^23");
		for (int i = 1, j = 0; i < n; ++i) {
			int bit = n >> 1;
			for (; j & bit; bit >>= 1) j ^= bit;
			j ^= bit;
			if (i < j) std::swap(a[i], a[j]);
		}
		for (int len = 2; len <= n; len <<= 1) {
			int wlen = power(ROOT, (MOD - 1) / len);
			if (invert) wlen = inverse(wlen);
			for (int i = 0; i < n; i += len) {
				int w = 1;
				for (int j = 0; j < len / 2; ++j) {
					int u = a[i + j], v = int(i64(a[i + j + len / 2]) * w % MOD);
					int x = u + v;
					if (x >= MOD) x -= MOD;
					int y = u - v;
					if (y < 0) y += MOD;
					a[i + j] = x;
					a[i + j + len / 2] = y;
					w = int(i64(w) * wlen % MOD);
				}
			}
		}
		if (invert) {
			int z = inverse(n);
			for (int& x : a) x = int(i64(x) * z % MOD);
		}
	}
	// limit >= 0: return exactly limit coefficients, zero padded.
	inline Poly mul(const Poly& a, const Poly& b, int limit = -1) {
		if (limit < -1) throw std::invalid_argument("invalid limit");
		if (!limit) return {};
		int na = int(a.size()), nb = int(b.size());
		if (limit >= 0) {
			na = std::min(na, limit);
			nb = std::min(nb, limit);
		}
		if (!na || !nb) return limit < 0 ? Poly{} : Poly(limit);
		int full = na + nb - 1, take = limit < 0 ? full : std::min(full, limit);
		Poly c;
		if (std::min(na, nb) <= 32) {
			c.assign(take, 0);
			for (int i = 0; i < na && i < take; ++i)
				for (int j = 0; j < nb && i + j < take; ++j) c[i + j] = int((c[i + j] + i64(a[i]) * b[j]) % MOD);
		} else {
			if (full > MAX_NTT) throw std::length_error("convolution exceeds NTT capacity");
			int n = 1;
			while (n < full) n <<= 1;
			Poly x(a.begin(), a.begin() + na), y(b.begin(), b.begin() + nb);
			x.resize(n);
			y.resize(n);
			ntt(x);
			ntt(y);
			for (int i = 0; i < n; ++i) x[i] = int(i64(x[i]) * y[i] % MOD);
			ntt(x, true);
			x.resize(take);
			c = std::move(x);
		}
		if (limit >= 0) c.resize(limit);
		return c;
	}
	inline Poly derivative(const Poly& a) {
		if (a.empty()) return {};
		Poly b(a.size() - 1);
		for (int i = 1; i < int(a.size()); ++i) b[i - 1] = int(i64(a[i]) * i % MOD);
		return b;
	}
	inline Poly integral(const Poly& a) {
		int n = int(a.size());
		if (n >= MOD) throw std::length_error("integral degree >= MOD");
		Poly b(n + 1), iv(n + 1);
		if (n) iv[1] = 1;
		for (int i = 2; i <= n; ++i) iv[i] = MOD - int(i64(MOD / i) * iv[MOD % i] % MOD);
		for (int i = 0; i < n; ++i) b[i + 1] = int(i64(a[i]) * iv[i + 1] % MOD);
		return b;
	}
	inline void precision(int n) {
		if (n < 0 || n >= MOD) throw std::invalid_argument("precision must be in [0, MOD)");
	}
	inline Poly inv(const Poly& a, int n) {
		precision(n);
		if (!n) return {};
		if (a.empty() || !a[0]) throw std::domain_error("inv requires a[0] != 0");
		Poly b{inverse(a[0])};
		while (int(b.size()) < n) {
			int m = std::min(n, int(b.size()) * 2);
			Poly t = mul(cut(a, m), b, m);
			for (int& x : t)
				if (x) x = MOD - x;
			t[0] += 2;
			if (t[0] >= MOD) t[0] -= MOD;
			b = mul(b, t, m);
		}
		return b;
	}
	inline Poly log(const Poly& a, int n) {
		precision(n);
		if (!n) return {};
		if (a.empty() || a[0] != 1) throw std::domain_error("log requires a[0] == 1");
		return cut(integral(mul(derivative(cut(a, n)), inv(a, n), n - 1)), n);
	}
	inline Poly exp(const Poly& a, int n) {
		precision(n);
		if (!n) return {};
		if (!a.empty() && a[0]) throw std::domain_error("exp requires a[0] == 0");
		Poly b{1};
		while (int(b.size()) < n) {
			int m = std::min(n, int(b.size()) * 2);
			Poly t = sub(cut(a, m), log(b, m));
			if (++t[0] == MOD) t[0] = 0;
			b = mul(b, t, m);
		}
		return b;
	}
	// Nonnegative integer exponent, including 0^0 = 1 as a formal power series.
	inline Poly pow(const Poly& a, u64 k, int n) {
		precision(n);
		if (!n) return {};
		if (!k) {
			Poly b(n);
			b[0] = 1;
			return b;
		}
		int s = 0;
		while (s < int(a.size()) && !a[s]) ++s;
		if (s == int(a.size()) || s >= n || (s && k > u64((n - 1) / s))) return Poly(n);
		int shift = s ? int(u64(s) * k) : 0, m = n - shift;
		Poly b(m);
		int z = inverse(a[s]);
		for (int i = 0; i < m && i + s < int(a.size()); ++i) b[i] = int(i64(a[i + s]) * z % MOD);
		b = exp(scale(log(b, m), int(k % MOD)), m);
		b = scale(std::move(b), power(a[s], k));
		Poly c(n);
		std::copy(b.begin(), b.end(), c.begin() + shift);
		return c;
	}
	// Tonelli-Shanks. Returns the smaller of the two roots; -1 if no root.
	inline int mod_sqrt(int a) {
		if (!a) return 0;
		if (power(a, (MOD - 1) / 2) != 1) return -1;
		int q = MOD - 1, s = 0;
		while (!(q & 1)) {
			q >>= 1;
			++s;
		}
		int z = 2;
		while (power(z, (MOD - 1) / 2) != MOD - 1) ++z;
		int c = power(z, q), x = power(a, (q + 1) / 2), t = power(a, q), m = s;
		while (t != 1) {
			int i = 0, u = t;
			while (u != 1) {
				u = int(i64(u) * u % MOD);
				++i;
			}
			int b = power(c, u64(1) << (m - i - 1));
			x = int(i64(x) * b % MOD);
			c = int(i64(b) * b % MOD);
			t = int(i64(t) * c % MOD);
			m = i;
		}
		return std::min(x, MOD - x);
	}
	// One root modulo x^n. Undetermined highest coefficients are set to zero.
	inline Poly sqrt(const Poly& a, int n) {
		precision(n);
		if (!n) return {};
		int s = 0;
		while (s < n && (s >= int(a.size()) || !a[s])) ++s;
		if (s == n) return Poly(n);
		if (s & 1) throw std::domain_error("sqrt: odd leading degree");
		int r = mod_sqrt(a[s]);
		if (r < 0) throw std::domain_error("sqrt: leading coefficient is a nonresidue");
		int m = n - s;
		Poly t(m);
		for (int i = 0; i < m && i + s < int(a.size()); ++i) t[i] = a[i + s];
		Poly b{r};
		while (int(b.size()) < m) {
			int len = std::min(m, int(b.size()) * 2);
			b = scale(add(cut(b, len), mul(cut(t, len), inv(b, len), len)), (MOD + 1) / 2);
		}
		Poly c(n);
		std::copy(b.begin(), b.end(), c.begin() + s / 2);
		return c;
	}
	// a = quotient * b + remainder; both returned in trimmed form.
	inline std::pair<Poly, Poly> divmod(Poly a, Poly b) {
		trim(a);
		trim(b);
		if (b.empty()) throw std::domain_error("division by zero polynomial");
		if (a.size() < b.size()) return {{}, a};
		int k = int(a.size() - b.size() + 1);
		Poly ra(a.rbegin(), a.rend()), rb(b.rbegin(), b.rend());
		Poly q = mul(cut(ra, k), inv(rb, k), k);
		std::reverse(q.begin(), q.end());
		Poly r = sub(a, mul(q, b));
		r.resize(b.size() - 1);
		trim(q);
		trim(r);
		return {q, r};
	}
	inline Poly mod(const Poly& a, const Poly& b) { return divmod(a, b).second; }
	inline int eval(const Poly& a, int x) {
		int r = 0;
		for (int i = int(a.size()) - 1; i >= 0; --i) r = int((i64(r) * x + a[i]) % MOD);
		return r;
	}
	// a(x+c), O(n log n).
	inline Poly shift(const Poly& a, int c) {
		int n = int(a.size());
		if (!n) return {};
		precision(n);
		Poly fac(n, 1), ifac(n, 1), x(n), y(n);
		for (int i = 1; i < n; ++i) fac[i] = int(i64(fac[i - 1]) * i % MOD);
		ifac[n - 1] = inverse(fac[n - 1]);
		for (int i = n - 1; i; --i) ifac[i - 1] = int(i64(ifac[i]) * i % MOD);
		int p = 1;
		for (int i = 0; i < n; ++i) {
			x[n - 1 - i] = int(i64(a[i]) * fac[i] % MOD);
			y[i] = int(i64(p) * ifac[i] % MOD);
			p = int(i64(p) * c % MOD);
		}
		Poly z = mul(x, y, n), b(n);
		for (int i = 0; i < n; ++i) b[i] = int(i64(z[n - 1 - i]) * ifac[i] % MOD);
		return b;
	}
	struct ProductTree {
		int n;
		std::vector<Poly> t;
		explicit ProductTree(const Poly& x) : n(int(x.size())), t(4 * std::max(1, n)) {
			if (n) build(1, 0, n, x);
		}
		void build(int v, int l, int r, const Poly& x) {
			if (r - l == 1) {
				t[v] = {x[l] ? MOD - x[l] : 0, 1};
				return;
			}
			int m = (l + r) / 2;
			build(v * 2, l, m, x);
			build(v * 2 + 1, m, r, x);
			t[v] = mul(t[v * 2], t[v * 2 + 1]);
		}
		void descend(int v, int l, int r, const Poly& a, Poly& ans) const {
			if (r - l == 1) {
				ans[l] = a.empty() ? 0 : a[0];
				return;
			}
			int m = (l + r) / 2;
			descend(v * 2, l, m, mod(a, t[v * 2]), ans);
			descend(v * 2 + 1, m, r, mod(a, t[v * 2 + 1]), ans);
		}
		Poly evaluate(const Poly& a) const {
			Poly ans(n);
			if (n) descend(1, 0, n, mod(a, t[1]), ans);
			return ans;
		}
		Poly combine(int v, int l, int r, const Poly& w) const {
			if (r - l == 1) return {w[l]};
			int m = (l + r) / 2;
			return add(mul(combine(v * 2, l, m, w), t[v * 2 + 1]), mul(combine(v * 2 + 1, m, r, w), t[v * 2]));
		}
	};
	inline Poly evaluate(const Poly& a, const Poly& x) { return ProductTree(x).evaluate(a); }
	// All x[i] must be distinct modulo MOD. Result has exactly x.size() entries.
	inline Poly interpolate(const Poly& x, const Poly& y) {
		if (x.size() != y.size()) throw std::invalid_argument("interpolation size mismatch");
		if (x.empty()) return {};
		ProductTree tree(x);
		Poly d = tree.evaluate(derivative(tree.t[1])), w(x.size());
		for (int i = 0; i < int(x.size()); ++i) {
			if (!d[i]) throw std::domain_error("interpolation requires distinct points");
			w[i] = int(i64(y[i]) * inverse(d[i]) % MOD);
		}
		return cut(tree.combine(1, 0, int(x.size()), w), int(x.size()));
	}
	// [x^k] P(x)/Q(x). Supports improper fractions; Q[0] must be nonzero.
	inline int bostan_mori(Poly p, Poly q, u64 k) {
		trim(p);
		trim(q);
		if (q.empty() || !q[0]) throw std::domain_error("Bostan-Mori requires Q[0] != 0");
		while (k && !p.empty()) {
			Poly qm = q;
			for (int i = 1; i < int(qm.size()); i += 2)
				if (qm[i]) qm[i] = MOD - qm[i];
			Poly a = mul(p, qm), b = mul(q, qm), np, nq;
			for (int i = int(k & 1); i < int(a.size()); i += 2) np.push_back(a[i]);
			for (int i = 0; i < int(b.size()); i += 2) nq.push_back(b[i]);
			p = std::move(np);
			q = std::move(nq);
			trim(p);
			trim(q);
			k >>= 1;
		}
		return p.empty() ? 0 : int(i64(p[0]) * inverse(q[0]) % MOD);
	}
	// f[n] = c[0]*f[n-1] + ... + c[d-1]*f[n-d], init = f[0..d-1].
	inline int linear_recurrence(const Poly& init, const Poly& c, u64 n) {
		int d = int(c.size());
		if (!d || int(init.size()) != d) throw std::invalid_argument("invalid recurrence size");
		if (n < u64(d)) return init[size_t(n)];
		Poly q(d + 1);
		q[0] = 1;
		for (int i = 0; i < d; ++i) q[i + 1] = c[i] ? MOD - c[i] : 0;
		return bostan_mori(mul(init, q, d), q, n);
	}
}  // namespace poly

using namespace poly;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	Poly a;
	a.resize(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	a = exp(a, n);
	for (int i = 0; i < n; i++) cout << a[i] << " ";
	return 0;
}