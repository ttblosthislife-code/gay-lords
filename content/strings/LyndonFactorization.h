/**
 * Author: std-abs
 * Source: github
 * Description: Computes the unique Lyndon factorization
 * s = w[0] + w[1] + ... + w[k-1], where
 * w[0] >= w[1] >= ... >= w[k-1] lexicographically,
 * and each w[i] is strictly lexicographically smaller
 * than all its non-empty proper suffixes.
 * Time: O(|s|), Space: O(|s|) for output.
 * Status: Stress-tested
 */
vector<string> duval(const string &s) {
  vector<string> ans;
  for (int n = sz(s), i = 0, j, k; i < n; ) {
    for (j = i + 1, k = i; j < n && s[k] <= s[j]; j++)
      k = (s[k] < s[j] ? i : k + 1);
    for (; i <= k; i += j - k)
      ans.pb(s.substr(i, j - k)); // s.substr(l, len)
  }
  return ans;
}