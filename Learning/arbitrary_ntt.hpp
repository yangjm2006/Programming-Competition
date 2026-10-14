#pragma once
#include <bits/stdc++.h>

// C++17 任意模数卷积：三模 NTT + CRT，全部为整数运算，无浮点误差。
// 支持任意 32 位正整数模数：1 <= mod <= 2147483647，合数也支持。
// 系数按低次到高次排列；允许负系数，公共卷积接口会自动归一化。
// 输入项数 n 表示次数最多为 n-1；limit 表示返回项数，不是最高次数。
// 空数组表示零多项式，所有公共卷积接口均不修改输入。
// NTT 分支中，截断后输入的完整乘积长度必须 <=2^24。
// 该限制同时保证整数卷积系数小于三个 NTT 模数的乘积，CRT 重建唯一。
namespace arbitrary_ntt {
	using i64 = long long;
	using Poly = std::vector<int>;
	using Input = std::vector<i64>;
	constexpr int P1 = 167772161, P2 = 469762049, P3 = 1224736769;
	constexpr int MAX_NTT = 1 << 24;

	// 检查目标模数是否为正数；非法时抛 invalid_argument，无返回值。
	// 用法：arbitrary_ntt::check_mod(mod); // 卷积接口自动调用，一般不必手动调用。
	inline void check_mod(int mod) {
		if (mod <= 0) throw std::invalid_argument("mod must be a positive 32-bit integer");
	}

	// 将有符号 64 位整数归一化到 [0,mod)，要求 mod>0；O(1)。
	// 用法：int x = arbitrary_ntt::norm(-1, 1000000007); // 1000000006
	// 支持 LLONG_MIN、LLONG_MAX；建议保留命名空间前缀以避免 std::norm 重名。
	inline int norm(i64 x, int mod) {
		check_mod(mod);
		x %= mod;
		return int(x < 0 ? x + mod : x);
	}

	// 批量归一化 long long 系数，返回 vector<int>，不改变输入；O(a.size())。
	// 用法：auto a = arbitrary_ntt::normalize({-1, 2, 3}, 1000000007);
	inline Poly normalize(const Input& a, int mod) {
		check_mod(mod);
		Poly b(a.size());
		for (size_t i = 0; i < a.size(); ++i) b[i] = norm(a[i], mod);
		return b;
	}

	// 单个固定模数的 NTT 引擎；通常只调用下面的 mul/convolution 即可。
	// P 必须是 NTT 质数，G 为原根，CAP 为该模数支持的最大 2 的幂长度。
	template <int P, int G, int CAP>
	struct Engine {
		// 标量快速幂：返回 a^e mod P；要求 0<=a<P、e>=0；O(log(e+1))。
		// 内部用法：Engine<P1,3,MAX_NTT>::power(3, (P1-1)/len)。
		static int power(int a, int e) {
			int r = 1;
			for (; e; e >>= 1, a = int(i64(a) * a % P))
				if (e & 1) r = int(i64(r) * a % P);
			return r;
		}

		// 原地 NTT，false 为正变换，true 为逆变换（已乘长度逆元）。
		// 要求长度为非零 2 的幂，且 <=CAP；所有系数在 [0,P) 内。
		// 用法：NTT1::transform(a); NTT1::transform(a,true); // 恢复 a
		// O(n log n)。P3 大于 2^30，蝶形加法特意避免 int 溢出。
		static void transform(Poly& a, bool invert = false) {
			size_t sz = a.size();
			if (!sz || sz > size_t(CAP) || (sz & (sz - 1))) throw std::invalid_argument("invalid NTT length");
			int n = int(sz);
			for (int i = 1, j = 0; i < n; ++i) {
				int bit = n >> 1;
				for (; j & bit; bit >>= 1) j ^= bit;
				j ^= bit;
				if (i < j) std::swap(a[i], a[j]);
			}
			for (int len = 2; len <= n; len <<= 1) {
				int step = power(G, (P - 1) / len);
				if (invert) step = power(step, P - 2);
				for (int i = 0; i < n; i += len) {
					int w = 1;
					for (int j = 0; j < len / 2; ++j) {
						int u = a[i + j], v = int(i64(a[i + j + len / 2]) * w % P);
						a[i + j] = u >= P - v ? u - (P - v) : u + v;
						a[i + j + len / 2] = u >= v ? u - v : u + (P - v);
						w = int(i64(w) * step % P);
					}
				}
			}
			if (invert) {
				int z = power(n, P - 2);
				for (int& x : a) x = int(i64(x) * z % P);
			}
		}

		// 内部单模卷积：只使用 a 的前 na 项、b 的前 nb 项，返回前 take 项。
		// 输入须非负，但可以大于 P，函数会对 P 取模；na、nb 必须为正。
		// 要求 na<=a.size()、nb<=b.size()、0<=take<=na+nb-1<=CAP。
		// 自动补到合适的 2 的幂长度，O(N log N)；由 mul 自动调用。
		static Poly multiply(const Poly& a, const Poly& b, int na, int nb, int take) {
			if (na <= 0 || nb <= 0 || size_t(na) > a.size() || size_t(nb) > b.size() || i64(na) + nb - 1 > CAP ||
				take < 0 || i64(take) > i64(na) + nb - 1)
				throw std::invalid_argument("invalid single-mod convolution size");
			int n = 1;
			while (n < na + nb - 1) n <<= 1;
			Poly x(n), y(n);
			for (int i = 0; i < na; ++i) x[i] = a[i] % P;
			for (int i = 0; i < nb; ++i) y[i] = b[i] % P;
			transform(x);
			transform(y);
			for (int i = 0; i < n; ++i) x[i] = int(i64(x[i]) * y[i] % P);
			transform(x, true);
			x.resize(take);
			return x;
		}
	};
	using NTT1 = Engine<P1, 3, MAX_NTT>;
	using NTT2 = Engine<P2, 3, MAX_NTT>;
	using NTT3 = Engine<P3, 3, MAX_NTT>;

	// 三模 CRT：重建 [0,P1*P2*P3) 中的整数，再返回该整数 mod mod。
	// 要求 0<=r1<P1、0<=r2<P2、0<=r3<P3、mod>0；O(1)，逆元仅首次计算。
	// 用法：int x = arbitrary_ntt::crt(42,42,42,1000000007); // 42
	// 只有真实非负整数系数小于 P1*P2*P3 时，重建值才是原整数。
	// mul 的模数/长度范围保证此条件；不要拿它无条件重建任意大整数。
	// 混合进位形式 x=r1+P1*t+P1*P2*u，最后一项先取目标模数以免溢出。
	inline int crt(int r1, int r2, int r3, int mod) {
		check_mod(mod);
		static const int inv12 = NTT2::power(P1, P2 - 2);
		static const i64 p12 = i64(P1) * P2;
		static const int inv123 = NTT3::power(int(p12 % P3), P3 - 2);
		i64 t = (i64(r2) - r1 + P2) % P2 * inv12 % P2;
		i64 r12 = r1 + i64(P1) * t;
		i64 u = (i64(r3) - r12 % P3 + P3) % P3 * inv123 % P3;
		return int((r12 % mod + (p12 % mod) * u % mod) % mod);
	}

	// 任意模数多项式乘法，要求 1<=mod<=INT_MAX，质数/合数/mod=1 都支持。
	// 输入为 vector<int>，允许负系数或系数>=mod，会自动归一化到 [0,mod)。
	// 用法：auto c = arbitrary_ntt::mul({1,2}, {3,4}, 1000000007); // {3,10,8}
	// limit=-1（默认）：完整卷积，非空输入返回 a.size()+b.size()-1 项。
	// limit>=0：恰好返回 limit 项，超出乘积长度的部分补零；limit=0 返回空数组。
	// 用法：auto c = arbitrary_ntt::mul(a,b,1000000007,100); // 模 x^100
	// 任一输入为空：完整卷积返回空数组；指定 limit 时返回 limit 个零。
	// 短数组走朴素乘法；其余走三模 NTT，要求截断后 na+nb-1<=2^24。
	// 时间 O(N log N)，空间 O(N)，N 为完整线性卷积长度上取整至 2 的幂。
	// 不满足参数/容量条件时抛 invalid_argument 或 length_error。
	inline Poly mul(const Poly& a, const Poly& b, int mod, int limit = -1) {
		check_mod(mod);
		if (limit < -1) throw std::invalid_argument("limit must be -1 or nonnegative");
		if (!limit) return {};
		size_t na = a.size(), nb = b.size();
		if (limit >= 0) {
			na = std::min(na, size_t(limit));
			nb = std::min(nb, size_t(limit));
		}
		if (!na || !nb) return limit < 0 ? Poly{} : Poly(limit);
		if (na > size_t(INT_MAX) || nb > size_t(INT_MAX) || na + nb - 1 > size_t(INT_MAX))
			throw std::length_error("too many coefficients");
		int full = int(na + nb - 1), take = limit < 0 ? full : std::min(full, limit);
		int out = limit < 0 ? full : limit;
		if (mod == 1) return Poly(out);
		Poly x(na), y(nb);
		for (size_t i = 0; i < na; ++i) x[i] = norm(a[i], mod);
		for (size_t i = 0; i < nb; ++i) y[i] = norm(b[i], mod);
		Poly ans;
		if (std::min(na, nb) <= 32) {
			ans.assign(take, 0);
			for (int i = 0; i < int(na) && i < take; ++i)
				for (int j = 0; j < int(nb) && i + j < take; ++j)
					ans[i + j] = int((ans[i + j] + i64(x[i]) * y[j]) % mod);
		} else {
			if (full > MAX_NTT) throw std::length_error("convolution exceeds 2^24");
			// 分别计算，避免同时保留三对 NTT 临时数组。
			Poly r1 = NTT1::multiply(x, y, int(na), int(nb), take);
			Poly r2 = NTT2::multiply(x, y, int(na), int(nb), take);
			Poly r3 = NTT3::multiply(x, y, int(na), int(nb), take);
			ans.resize(take);
			for (int i = 0; i < take; ++i) ans[i] = crt(r1[i], r2[i], r3[i], mod);
		}
		ans.resize(out);
		return ans;
	}

	// long long 输入版任意模数卷积，返回 vector<int>，每项属于 [0,mod)。
	// 适合直接读取题目中较大的整数；支持整个有符号 64 位范围及负数。
	// 用法：Input a={-1,2}, b={3,4}; auto c=arbitrary_ntt::convolution(a,b,1000000007);
	// limit、返回长度、异常与 mul 一致；额外 O(a.size()+b.size()) 归一化。
	// 目标 mod 仍须为 32 位正整数，这不是 64 位模数卷积。
	inline Poly convolution(const Input& a, const Input& b, int mod, int limit = -1) {
		return mul(normalize(a, mod), normalize(b, mod), mod, limit);
	}
}  // namespace arbitrary_ntt
