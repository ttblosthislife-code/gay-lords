/**
 * Author: Bao Tran
 * Date: 2026-10-03
 * License: CC0
 * Source: CP-Algorithms
 * Description: Line adding and minimum query when knowing
 * all x-coordinates of queries in advance. Can be used for convex hull trick.
 * Time: $O(\log N)$ for add and query. Can be used for line range updates
 * in $O(\log^2 N)$.
 * Status: Stress-tested
 */
#pragma once

typedef vector<ll> vl;
const ll oo = (ll)2e18 + 5;
struct Line {
  ll a, b;
  Line(ll a = 0, ll b = oo) : a(a), b(b) {}
  ll get(ll x) const { return a * x + b; }
};
struct LiChao {
  int n;
  vl xs;
  vector<Line> st;
  LiChao() {}
  LiChao(vl _xs) {
  	assert(!_xs.empty());
  	xs = _xs;
  	sort(all(xs));
    xs.erase(unique(all(xs)), xs.end());
    n = sz(xs);
    st.resize(4 * n + 1, Line());
  }
  void add(int i, int l, int r, Line nw) {
    int m = (l + r) / 2;
    bool lef = nw.get(xs[l]) < st[i].get(xs[l]);
    bool mid = nw.get(xs[m]) < st[i].get(xs[m]);
    if (mid) swap(st[i], nw);
    if (l == r) return;
    if (lef != mid) add(i * 2, l, m, nw);
    else add(i * 2 + 1, m + 1, r, nw);
  }
  void add(Line nw) { add(1, 0, n - 1, nw); }
  ll query(int i, int l, int r, int id) {
    ll ans = st[i].get(xs[id]);
    if (l == r) return ans;
    int m = (l + r) / 2;
    if (id <= m) return min(ans, query(i * 2, l, m, id));
    else return min(ans, query(i * 2 + 1, m + 1, r, id));
  }
  ll query(ll x) {
    int id = lower_bound(all(xs), x) - xs.begin();
    assert(id < n && xs[id] == x);
    return query(1, 0, n - 1, id);
  }
};