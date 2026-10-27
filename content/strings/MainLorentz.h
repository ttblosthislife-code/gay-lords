/**
 * Author: std-abs
 * Source: github
 * Description: Finds all tandem repeats (squares) in s
 * in compressed form. Returns {L, R, len}, where
 * for every p in [L, R], s.substr(p, len) ==
 * s.substr(p + len, len).
 * Intervals with the same len may need merging.
 * Requires O(n) Z-function and a separator \# not in s.
 * Time: O(n log n), Space: O(n log n) including output.
 * Status: Stress-tested
 */
 auto main_lorentz(string _s) {
  vector<array<int, 3>> rep;
  auto dfs = [&](auto self, string s, int sft) -> void {
    int n = sz(s);
    if (n == 1) return;
    int nu = n / 2, nv = n - nu;
    string u = s.substr(0, nu), v = s.substr(nu),
          ru(u.rbegin(), u.rend()), rv(v.rbegin(), v.rend());
    self(self, u, sft), self(self, v, sft + nu);
    auto z1 = buildZ(ru), z2 = buildZ(v + '#' + u),
              z3 = buildZ(ru + '#' + rv), z4 = buildZ(v);
    auto get_z = [](vector<int> &z, int i) {
      return 0 <= i && i < sz(z) ? z[i] : 0; };
    auto add_rep = [&](bool left, int c, int l, int k1, int k2) {
      int L = max(1, l - k2), R = min(l - left, k1);
      if (L > R) return;
      if (left) rep.pb({sft + c - R, sft + c - L, l});
      else rep.pb({sft + c - R - l + 1, sft + c - L - l + 1, l});
    };
    for (int cntr = 0; cntr < n; cntr++) {
      int l, k1, k2;
      if (cntr < nu) {
        l = nu - cntr;
        k1 = get_z(z1, nu - cntr);
        k2 = get_z(z2, nv + 1 + cntr);
      } else {
        l = cntr - nu + 1;
        k1 = get_z(z3, nu + 1 + nv - 1 - (cntr - nu));
        k2 = get_z(z4, (cntr - nu) + 1);
      }
      if (k1 + k2 >= l)
        add_rep(cntr < nu, cntr, l, k1, k2);
    }
  };
  dfs(dfs, _s, 0);
  return rep;
}