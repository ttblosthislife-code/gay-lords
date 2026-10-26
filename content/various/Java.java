/**
 * Author: Bao Tran
 * License: CC0
 * Description: Java template for inputs, big integers.
 * Status: Approved.
 */
import java.util.*;
import java.io.*;
import java.math.*;
public class Main {
  static InputStream inputStream = System.in;
  static OutputStream outputStream = System.out;
  public static void main(String[] args) {
    InputReader in = new InputReader(inputStream);
    PrintWriter out = new PrintWriter(outputStream);
    Task solver = new Task(in, out);
    solver.solve();
    out.close();
  }
  static class Task {
    Random random = new Random(751454315315L + System.currentTimeMillis());
    InputReader in;
    PrintWriter out;
    Task(InputReader _in, PrintWriter _out) { in = _in; out = _out; }
    final int N = 5000;
    int[] arr = new int[N];
    ArrayList<Integer> list = new ArrayList<>();
    // ArrayList: add(x), get(i), set(i, x), size(), remove(i),
    // clear(), isEmpty(), Collections.sort(list)
    public void solve() {
      // shuffle before sort
      Arrays.sort(arr, 0, 10, (a, b) -> {
        return Integer.compare(-a, -b);
      });
      BigInteger a = in.nextBigInteger();
      BigInteger b = new BigInteger("6");
      // BigInteger:
      // intValue(), valueOf(x), toString(base)
      // add/subtract/multiply/divide(b)    // + - * /
      // pow(p), remainder(m), mod(m)       // ^, %, %
      // modInverse(m), modPow(p,m), gcd(b) // inv, powmod, gcd
      // negate(), min(b), max(b)           // -, min, max
      // not(), and(b), andNot(b), or(b), xor(b)
      // shiftLeft(n), shiftRight(n)        // <<, >>
    }
    void sortArray(int[] s) {
      shuffle(s);
      Arrays.sort(s);
    }
    void shuffle(int[] s) {
      for (int i = 0; i < s.length; ++i) {
        int j = random.nextInt(i + 1);
        int t = s[i]; s[i] = s[j]; s[j] = t;
      }
    }
  }
  static class InputReader {
    public BufferedReader reader;
    public StringTokenizer tokenizer;
    public InputReader(InputStream stream) {
      reader = new BufferedReader(new InputStreamReader(stream), 32768);
      tokenizer = null;
    }
    public String next() {
      while (tokenizer == null || !tokenizer.hasMoreTokens()) {
        try { tokenizer = new StringTokenizer(reader.readLine()); }
        catch (IOException e) { throw new RuntimeException(e); }
      }
      return tokenizer.nextToken();
    }
    public int nextInt() { return Integer.parseInt(next()); }
    public double nextDouble() { return Double.parseDouble(next()); }
    public BigInteger nextBigInteger() { return new BigInteger(next()); }
  }
}