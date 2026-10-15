#include <bits/stdc++.h>

// C++17 多项式库：固定模数 998244353，原根 3。
// Poly 按低次到高次存储：{1,2,3} 表示 1+2x+3x^2；空数组表示零多项式。
// 输入系数、求值点、标量都必须在 [0,MOD) 内，读入时可用 poly::norm(v)。
// n 表示保留的项数，即模 x^n，而不是最高次数；缺失项按零处理。
// FPS 接口要求 0<=n<MOD，n=0 时返回空数组。
// 除 trim 和 ntt 外，公共运算不会修改传入的多项式。
// 参数不合法或运算无解时抛出标准异常，具体条件见各函数注释。
namespace poly {
	using i64 = long long;
	using u64 = unsigned long long;
	using Poly = std::vector<int>;
	constexpr int MOD = 998244353, ROOT = 3, MAX_NTT = 1 << 23;
	// 有符号整数取模，返回 [0,MOD) 内的值；O(1)。
	// 用法：int x = poly::norm(-1); // MOD-1
	// 建议保留 poly:: 前缀，避免与 std::norm 重名。
	inline int norm(i64 x) {
		x %= MOD;
		return int(x < 0 ? x + MOD : x);
	}
	// 标量快速幂：返回 a^e mod MOD，a 已归一化，e 为非负 64 位整数。
	// 用法：int x = poly::power(2, 10); // 1024；O(log(e+1))，0^0 返回 1。
	inline int power(int a, u64 e) {
		int r = 1;
		for (; e; e >>= 1, a = int(i64(a) * a % MOD))
			if (e & 1) r = int(i64(r) * a % MOD);
		return r;
	}
	// 标量乘法逆元：返回 x^{-1} mod MOD，要求 1<=x<MOD；O(log MOD)。
	// 用法：int half = poly::inverse(2); // (MOD+1)/2；x=0 抛 domain_error。
	inline int inverse(int x) {
		if (!x) throw std::domain_error("inverse of zero");
		return power(x, MOD - 2);
	}
	// 原地去掉最高次的零系数；零多项式变为空数组，无返回值。
	// 用法：poly::trim(a); // {1,2,0,0} -> {1,2}；O(删除项数)。
	inline void trim(Poly& a) {
		while (!a.empty() && !a.back()) a.pop_back();
	}
	// 返回恰好 n 项的副本：超长截断、不足补零；n>=0，原 a 不变。
	// 用法：auto b = poly::cut({1,2}, 4); // {1,2,0,0}；复制/调整为线性时间。
	inline Poly cut(Poly a, int n) {
		if (n < 0) throw std::invalid_argument("negative precision");
		a.resize(n);
		return a;
	}
	// 多项式加法，返回 max(a.size(),b.size()) 项，不自动去高位零；O(n)。
	// 用法：auto c = poly::add({1,2}, {3}); // {4,2}
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
	// 多项式减法，返回 max(a.size(),b.size()) 项，不自动去高位零；O(n)。
	// 用法：auto c = poly::sub({1,2}, {3}); // {MOD-2,2}
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
	// 多项式乘标量 c，返回与 a 等长的新数组，要求 0<=c<MOD；O(n)。
	// 用法：auto b = poly::scale({1,2}, 3); // {3,6}
	// 取负：auto b = poly::scale(a, poly::MOD-1);
	inline Poly scale(Poly a, int c) {
		for (int& x : a) x = int(i64(x) * c % MOD);
		return a;
	}
	// 原地数论变换；invert=false 为正变换，true 为逆变换（含除以长度）。
	// 要求 a.size() 是非零的 2 的幂且 <=2^23，否则抛 invalid_argument。
	// 用法：a.resize(8); poly::ntt(a); poly::ntt(a,true); // 恢复 a
	// O(n log n)。一般直接调用 mul，只有手动做频域运算时才需要调用 ntt。
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
	// 多项式乘法/卷积，系数 c[k]=sum(a[i]*b[k-i]) mod MOD；O(N log N)。
	// 用法：auto c = poly::mul({1,2}, {3,4}); // {3,10,8}
	// limit=-1（默认）：返回完整乘积；任一输入为空时返回空数组。
	// limit>=0：返回恰好 limit 项，不足补零，即乘积模 x^limit。
	// 用法：auto c = poly::mul(a,b,100); // 只取前 100 项
	// NTT 分支要求截断后输入的完整乘积长度 <=2^23，否则抛 length_error。
	// 返回长度 limit 并不意味着 NTT 只需要 limit 长；短数组走朴素乘法。
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
	// 求导：b[i]=(i+1)*a[i+1]，非空输入返回 a.size()-1 项；O(n)。
	// 用法：auto b = poly::derivative({1,2,3}); // {2,6}
	inline Poly derivative(const Poly& a) {
		if (a.empty()) return {};
		Poly b(a.size() - 1);
		for (int i = 1; i < int(a.size()); ++i) b[i - 1] = int(i64(a[i]) * i % MOD);
		return b;
	}
	// 积分，积分常数设为 0：b[i+1]=a[i]/(i+1)，返回 a.size()+1 项；O(n)。
	// 要求 a.size()<MOD；空输入返回 {0}。
	// 用法：auto b = poly::integral({2,6}); // {0,2,3}
	inline Poly integral(const Poly& a) {
		int n = int(a.size());
		if (n >= MOD) throw std::length_error("integral degree >= MOD");
		Poly b(n + 1), iv(n + 1);
		if (n) iv[1] = 1;
		for (int i = 2; i <= n; ++i) iv[i] = MOD - int(i64(MOD / i) * iv[MOD % i] % MOD);
		for (int i = 0; i < n; ++i) b[i + 1] = int(i64(a[i]) * iv[i + 1] % MOD);
		return b;
	}
	// 内部精度检查：无返回值；n 不满足 0<=n<MOD 时抛 invalid_argument。
	// 用法：poly::precision(n); // 通常无需手动调用，FPS 接口会调用它。
	// 此检查不保证中间卷积满足 NTT 长度上限，长度由 mul 单独检查。
	inline void precision(int n) {
		if (n < 0 || n >= MOD) throw std::invalid_argument("precision must be in [0, MOD)");
	}
	// 形式幂级数求逆，返回 n 项 b，使 a*b == 1 (mod x^n)；O(n log n)。
	// n>0 时要求 a 非空且 a[0]!=0，否则抛 domain_error。
	// 用法：auto b = poly::inv({1,1}, 4); // {1,MOD-1,1,MOD-1}
	// 与 inverse 区别：inverse 求单个数的逆元，inv 求整个幂级数的逆元。
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
	// 形式幂级数 ln，返回 n 项，常数项为 0；O(n log n)。
	// n>0 时要求 a[0]==1，否则抛 domain_error。
	// 用法：auto b = poly::log({1,1}, 4); // {0,1,-1/2,1/3}（均按模数存储）
	inline Poly log(const Poly& a, int n) {
		precision(n);
		if (!n) return {};
		if (a.empty() || a[0] != 1) throw std::domain_error("log requires a[0] == 1");
		return cut(integral(mul(derivative(cut(a, n)), inv(a, n), n - 1)), n);
	}
	// 形式幂级数 exp，返回 n 项，n>0 时常数项为 1；O(n log n)。
	// 要求 a[0]==0（空输入视作 0），否则抛 domain_error。
	// 用法：auto b = poly::exp({0,1}, 4); // {1,1,1/2,1/6}（模意义）
	// 在相应常数项条件下，exp(log(a,n),n)==cut(a,n)。
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
	// 非负整数幂，返回 a^k mod x^n 的 n 项；支持 a[0]=0 和前导零。
	// k 是真实的 unsigned long long 指数，不要在调用前对 MOD 取模。
	// 用法：auto b = poly::pow({1,1}, 3ULL, 5); // {1,3,3,1,0}
	// k=0 返回常数 1（包括 0^0）；不支持负指数，负幂可先 inv 再 pow。
	// 时间 O(n log n + log(k+1))，前导零导致乘积消失时可提前返回。
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
	// 标量模平方根：求 r*r==a (mod MOD)，使用 Tonelli-Shanks。
	// 要求 0<=a<MOD；有解返回两个根中较小的根，无解返回 -1；a=0 返回 0。
	// 用法：int r = poly::mod_sqrt(4); // 2；可先判断 r==-1。
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
	// 形式幂级数开根，返回 n 项 b，使 b*b==a (mod x^n)；O(n log n)。
	// 前 n 项全零时返回 n 个零；否则首个非零项次数须为偶数，且系数须有模根。
	// 无解抛 domain_error；选用较小的首项模根，不确定的最高项设为零。
	// 用法：auto b = poly::sqrt({1,2,1}, 5); // {1,1,0,0,0}
	// 支持前导零：sqrt({0,0,1},4) 返回 {0,1,0,0}。
	// 另一支根可用 poly::scale(b,poly::MOD-1)；无解题应捕获 domain_error。
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
	// 多项式带余除法：返回 {q,r}，满足 a=q*b+r 且 deg(r)<deg(b)。
	// 要求 b 不是零多项式，否则抛 domain_error；q、r 均去高位零。
	// 用法：auto [q,r] = poly::divmod({1,2,1}, {1,1}); // q={1,1}, r={}
	// 这是有限多项式除法，区别于 inv 的形式幂级数除法；O(N log N)。
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
	// 返回多项式 a 除以 b 的余数，并去高位零；b 非零，O(N log N)。
	// 用法：auto r = poly::mod({1,2,1}, {1,1}); // 空数组，即余数为 0。
	inline Poly mod(const Poly& a, const Poly& b) { return divmod(a, b).second; }
	// 单点求值：返回 a(x) mod MOD，要求 0<=x<MOD；Horner 法，O(a.size())。
	// 用法：int y = poly::eval({1,2,3}, 2); // 17
	inline int eval(const Poly& a, int x) {
		int r = 0;
		for (int i = int(a.size()) - 1; i >= 0; --i) r = int((i64(r) * x + a[i]) % MOD);
		return r;
	}
	// 多项式平移：返回 a(x+c) 的系数，与 a 等长，要求 0<=c<MOD。
	// 用法：auto b = poly::shift({1,2,3}, 1); // {6,8,3}
	// c 为负整数时先 norm；这里不是乘 x^c 或移动数组下标。
	// 要求 a.size()<MOD；时间 O(n log n)。
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
	// 乘积树：t[v]=区间内所有 (X-x[i]) 的乘积，区间统一采用 [l,r)。
	// 用于多点求值和插值；树的空间 O(m log m)，m 为点数。
	// 一般调用下面的 evaluate/interpolate 即可；相同点集重复求值可复用此树。
	struct ProductTree {
		int n;
		std::vector<Poly> t;
		// 构造并建树，x 是求值点数组，要求所有点已归一化；允许空数组和重复点。
		// 用法：poly::ProductTree tree({0,1,2}); // O(m log^2 m)。
		explicit ProductTree(const Poly& x) : n(int(x.size())), t(4 * std::max(1, n)) {
			if (n) build(1, 0, n, x);
		}
		// 内部建树：建立节点 v 对应的点下标区间 [l,r)，要求 l<r。
		// 构造函数自动调用 build(1,0,n,x)，一般无需手动调用。
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
		// 内部余数下传：a 已经是原多项式模 t[v] 的余数，区间为 [l,r)。
		// 把该区间的求值结果写入预先分配的 ans（长度至少 n）。
		// 由成员 evaluate 自动调用，一般无需手动调用。
		void descend(int v, int l, int r, const Poly& a, Poly& ans) const {
			if (r - l == 1) {
				ans[l] = a.empty() ? 0 : a[0];
				return;
			}
			int m = (l + r) / 2;
			descend(v * 2, l, m, mod(a, t[v * 2]), ans);
			descend(v * 2 + 1, m, r, mod(a, t[v * 2 + 1]), ans);
		}
		// 使用已建好的点集求 a 的值，返回 n 项，顺序与构造时的 x 相同。
		// 用法：auto ys = tree.evaluate(a); // 可以对多个 a 复用同一棵树。
		// 单次 O(L log L + n log^2 n)，L 为 a 的长度。
		Poly evaluate(const Poly& a) const {
			Poly ans(n);
			if (n) descend(1, 0, n, mod(a, t[1]), ans);
			return ans;
		}
		// 内部插值合并：返回 sum(w[i]*区间内除第 i 项外的 (X-x[j]) 乘积)。
		// 插值时 w[i]=y[i]/P'(x[i])，P 为根节点乘积；区间为 [l,r)。
		// interpolate 自动调用 combine(1,0,n,w)，一般无需手动调用。
		Poly combine(int v, int l, int r, const Poly& w) const {
			if (r - l == 1) return {w[l]};
			int m = (l + r) / 2;
			return add(mul(combine(v * 2, l, m, w), t[v * 2 + 1]), mul(combine(v * 2 + 1, m, r, w), t[v * 2]));
		}
	};
	// 多点求值：返回 {a(x[0]),a(x[1]),...}，按输入顺序；允许重复点。
	// 用法：auto y = poly::evaluate({1,2,3}, {0,1,2}); // {1,6,17}
	// O(L log L + m log^2 m)，L=a.size()，m=x.size()；空点集返回空数组。
	inline Poly evaluate(const Poly& a, const Poly& x) { return ProductTree(x).evaluate(a); }
	// 多项式插值：求次数 <m 且 a(x[i])=y[i] 的唯一多项式，返回恰好 m 项。
	// 要求 x、y 等长，x 中的点模意义下两两不同；重复点抛 domain_error。
	// 用法：auto a = poly::interpolate({0,1,2}, {1,6,17}); // {1,2,3}
	// m=0 返回空数组；时间 O(m log^2 m + m log MOD)，空间 O(m log m)。
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
	// Bostan-Mori：返回形式幂级数 p(x)/q(x) 的第 k 项，即 [x^k]p/q。
	// 要求 q[0]!=0；k 是从 0 开始的非负 64 位下标，分子次数可大于分母。
	// 用法：int v = poly::bostan_mori({1}, {1,poly::MOD-1}, 100ULL); // 1
	// 常规 deg(p)<deg(q)=d 时 O(d log d log(k+1))；分子更长时额外处理其长度。
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
	// 求 d 阶线性递推的第 n 项，返回模 MOD 的结果，n 从 0 开始。
	// 递推约定：f[t]=c[0]*f[t-1]+...+c[d-1]*f[t-d]（t>=d）。
	// init={f[0],...,f[d-1]}，要求 init.size()==c.size()==d>0。
	// 用法：int fib = poly::linear_recurrence({0,1}, {1,1}, 10ULL); // 55
	// n 可达 unsigned long long 上限；时间 O(d log d log(n+1))。
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

using namespace std;
using namespace poly;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	Poly g(n);
	for (int i = 1; i <= n - 1; i++) cin >> g[i];
	Poly f = inv(sub({1}, g), n);
	for (int i = 0; i < n; i++) cout << f[i] << " ";
	return 0;
}