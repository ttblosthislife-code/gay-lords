/**
 * Author: Bao Tran
 * Date: 2026-10-02
 * License: CC0
 * Source: USACO
 * Description: Update min, max, add
 * Time: $O(\log N)$ amortized for updMin, updMax when not using updAdd
 * $O(\log^2 N)$ amortized when using updAdd.
 * Status: Stress-tested
 */
#pragma once

const ll oo = (ll)1e18 + 5;
const int N = 2e5 + 5;
struct Node { ll sum, mx1, cmx, mx2, mn1, cmn, mn2, laz; };
int n, q;
ll a[N];
Node t[4 * N];
void merge(int i) {
	auto &cc = t[i], lc = t[i * 2], rc = t[i * 2 + 1];
	// sum
	cc.sum = lc.sum + rc.sum;
	// min
	if (lc.mn1 > rc.mn1) swap(lc, rc);
	cc.mn1 = lc.mn1; cc.cmn = lc.cmn;
	cc.mn2 = min(lc.mn2, rc.mn2);
	if (rc.mn1 == lc.mn1) cc.cmn += rc.cmn;
	else cc.mn2 = min(cc.mn2, rc.mn1);
	// max
	if (lc.mx1 < rc.mx1) swap(lc, rc);
	cc.mx1 = lc.mx1; cc.cmx = lc.cmx;
	cc.mx2 = max(lc.mx2, rc.mx2);
	if (rc.mx1 == lc.mx1) cc.cmx += rc.cmx;
	else cc.mx2 = max(cc.mx2, rc.mx1);
}
void build(int i, int l, int r) {
	t[i].laz = 0;
	if (l == r) {
		t[i] = Node{a[l], a[l], 1, -oo, a[l], 1, oo, 0};
		return;
	}
	int mid = (l + r) / 2;
	build(i * 2, l, mid); build(i * 2 + 1, mid + 1, r);
	merge(i);
}
void pushAdd(int i, int l, int r, ll v) {
	if (!v) return;
	t[i].sum += (r - l + 1) * v;
	t[i].mx1 += v; if (t[i].mx2 != -oo) t[i].mx2 += v;
	t[i].mn1 += v; if (t[i].mn2 != oo) t[i].mn2 += v;
	t[i].laz += v;
}
void pushMin(int i, ll v) {
	if (v >= t[i].mx1) return;
	t[i].sum += (v - t[i].mx1) * t[i].cmx;
	t[i].mx1 = v;
	if (t[i].mn1 >= v) t[i].mn1 = v;
	else t[i].mn2 = min(t[i].mn2, v);
}
void pushMax(int i, ll v) {
	if (v <= t[i].mn1) return;
	t[i].sum += (v - t[i].mn1) * t[i].cmn;
	t[i].mn1 = v;
	if (t[i].mx1 <= v) t[i].mx1 = v;
	else t[i].mx2 = max(t[i].mx2, v);
}
void pushDown(int i, int l, int r) {
	int mid = l + (r - l) / 2;
	pushAdd(i * 2, l, mid, t[i].laz);
	pushAdd(i * 2 + 1, mid + 1, r, t[i].laz);
	t[i].laz = 0;
	pushMin(i * 2, t[i].mx1); pushMin(i * 2 + 1, t[i].mx1);
	pushMax(i * 2, t[i].mn1); pushMax(i * 2 + 1, t[i].mn1);
}
// 0: updAdd, 1: updMin, 2: updMax
void upd(int i, int l, int r, int ql, int qr, ll v, int type) {
	if (r < ql || l > qr) return;
	if (ql <= l && r <= qr && 
	(type == 0? 1 : type == 1? v > t[i].mx2 : v < t[i].mn2)) {
		if (type == 0) pushAdd(i, l, r, v);
		if (type == 1) pushMin(i, v);
		if (type == 2) pushMax(i, v);
		return;
	}
	int mid = (l + r) / 2; pushDown(i, l, r);
	upd(i * 2, l, mid, ql, qr, v, type);
	upd(i * 2 + 1, mid + 1, r, ql, qr, v, type);
	merge(i);
}
ll getSum(int i, int l, int r, int ql, int qr) {
	if (r < ql || l > qr) return 0;
	if (ql <= l && r <= qr) return t[i].sum;
	int mid = l + (r - l) / 2; pushDown(i, l, r);
	return getSum(i * 2, l, mid, ql, qr) + getSum(i * 2 + 1, mid + 1, r, ql, qr);
}