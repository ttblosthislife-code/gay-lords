/**
 * Author: std-abs
 * Date: 2026-10-29
 * License: CC0
 * Source: std-abs
 * Description: Blossom for general matching.
 * Match[i] = n if i isn't included or match[i] < n if i matched with match[i].
 * Time: O(N^3)
 * Status: Tested on yosupo library checker.
 */
#pragma once

struct Blossom {
  int n, tk;
  vector<vi> g;
  vi fa, pre, match, s, t;
  queue<int> q;
  Blossom(int _n) : n(_n), tk(0), g(n), fa(n + 1),
    pre(n + 1, n), match(n + 1, n), s(n + 1), t(n) {}
  int find(int u) {
		return u == fa[u]? u : fa[u] = find(fa[u]); }
  int lca(int x, int y) {
    tk++, x = find(x), y = find(y);
    for (; ; swap(x, y)) if (x != n) {
      if (t[x] == tk) return x;
      t[x] = tk;
      x = find(pre[match[x]]);
    }
  }
  void blossom(int x, int y, int l) {
    for (; find(x) != l; x = pre[y]) {
      pre[x] = y, y = match[x];
      if (s[y] == 1) q.push(y), s[y] = 0;
    	for (int z : {x, y}) if (fa[z] == z) fa[z] = l;
    }
  }
  bool bfs(int r) {
    iota(all(fa), 0), fill(all(s), -1);
    while (!q.empty()) q.pop();
    q.push(r), s[r] = 0;
    while (!q.empty()) {
      int x = q.front(); q.pop();
      for (int u : g[x]) {
        if (s[u] == -1) {
          pre[u] = x, s[u] = 1;
          if (match[u] == n) {
            for (int a = u, b = x, last; b != n; a = last, b = pre[a])
              last = match[b], match[b] = a, match[a] = b;
            return true;
          }
          q.push(match[u]);
          s[match[u]] = 0;
        } else if (!s[u] && find(u) != find(x)) {
          int l = lca(u, x);
          blossom(x, u, l), blossom(u, x, l);
        }
      }
    }
    return false;
  }
  int solve() {
    int res = 0;
    for (int x = 0; x < n; ++x) if (match[x] == n)
      res += bfs(x);
    return res;
  }
  void add_edge(int u, int v) {
    g[u].push_back(v), g[v].push_back(u); }
};