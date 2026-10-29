/**
 * Author: Bao Tran The
 * Date: 2026-10-29
 * License: CC0
 * Description: Polynomial basic operations, 
 * inv, ln and exp modulo $x^n$ using Hensel Lift (result size can be larger than n).
 * $F(Q) = Q^{-1} - A$; $Q_{k+1} = Q_{k} - F(Q_{k}) / F'(Q_{k})$.
 * For div(A, B) make sure that A[n] != 0 and B[m] != 0.
 * Time: O(N) or O(N \log N)
 * Status: tested on QOJ, yosupo library checker
 */
#pragma once

#include "../numerical/NumberTheoreticTransform.h"

vl operator +(vl A, vl B) {
	vl C(max(sz(A), sz(B)));
	rep(i, 0, sz(A)) C[i] = (C[i] + A[i]) % mod;
	rep(i, 0, sz(B)) C[i] = (C[i] + B[i]) % mod;
	return C;
}
vl operator -(vl A, vl B) {
	vl C(max(sz(A), sz(B)));
	rep(i, 0, sz(A)) C[i] = A[i];
	rep(i, 0, sz(B)) C[i] = (C[i] - B[i] + mod) % mod;
	return C;
}
vl deriv(vl A) {
	int n = sz(A) - 1;
	if (!n) return {0};
	vl B(n);
	rep(i, 0, n) B[i] = (i + 1) * A[i + 1] % mod;
	return B;
}
vl integr(vl A) {
	int n = sz(A) - 1;
	vl iv(n + 2);
	iv[1] = 1;
	rep(i, 2, n + 2)
		iv[i] = (-mod / i + mod) * iv[mod % i] % mod;
	vl B(n + 2);
	rep(i, 1, n + 2) B[i] = A[i - 1] * iv[i] % mod;
	return B;
}
vl inv(vl A, int n) {
	int m = 1; vl Q = {modpow(A[0], mod - 2)};
	while (m < n) {
		m <<= 1; vl A1 = A; A1.resize(m);
		Q = conv(Q, vl{2} - conv(A1, Q)); Q.resize(m);
	}
	return Q;
}
pair<vl, vl> div(vl A, vl B) {
	int n = sz(A) - 1, m = sz(B) - 1;
	assert(A[n] && B[m]);
	if (n < m) return {{0}, A};
	vl Ar = A, Br = B;
	reverse(all(Ar)); reverse(all(Br));
	int k = n - m + 1;
	vl D = conv(Ar, inv(Br, k)); D.resize(k);
	reverse(all(D));
	vl R = A - conv(B, D);
	return {D, R};
}
vl ln(vl P, int n) {
  return integr(conv(deriv(P), inv(P, n)));
}
vl exp(vl P, int n) {
	int m = 1; vl Q = {1};
	while (m < n) {
		m <<= 1; vl P1 = P; P1.resize(m);
		Q = conv(Q, vl{1} + P1 - ln(Q, m)); Q.resize(m);
	}
	return Q;
}