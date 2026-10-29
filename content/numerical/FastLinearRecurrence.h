/**
 * Author: Bao Tran The
 * Date: 2026-10-29
 * License: CC0
 * Description: Calculate $A_k$ modulo 998244353 of an linear recurrence with Bostan-Mori:
 * $A_i = \sum_{j=0}^{n-1} C_j A_{i-j-1}$ for $i \ge n$.
 * A and C must have equal sizes when calling the function.
 * Time: O(nlognlogk).
 * Status: tested on yosupo library checker.
 */
#pragma once

#include "../numerical/NumberTheoreticTransform.h"

ll fastLinearRecurrence(vl A, vl C, ll k) {
	assert(sz(A) == sz(C));
	int n = sz(A);
	vl G(n + 1), Q(n + 1);
	rep(i, 0, n) {
		G[i] = A[i];
		G[n] = (G[n] + A[i] * C[n - 1 - i]) % mod;
	}
	Q[0] = 1;
	rep(i, 0, n) Q[i + 1] = (mod - C[i]) % mod;
	auto P = conv(G, Q); P.resize(n + 1);
  // calculate [x^k]P(x)/Q(x) (Bostan-Mori)
	while (k) {
		auto Q1 = Q;
		for (int i = 1; i < sz(Q1); i += 2)
			Q1[i] = (mod - Q1[i]) % mod;
		auto P1 = conv(P, Q1);
		Q1 = conv(Q, Q1); Q = vl(n + 1);
		for (int i = 0; i < sz(Q1); i += 2)
			Q[i / 2] = Q1[i];
		P = vl(n + 1);
		for (int i = (k & 1); i < sz(P1); i += 2)
			P[i / 2] = P1[i];
		k >>= 1;
	}
	return P[0] * modpow(Q[0], mod - 2) % mod;
}