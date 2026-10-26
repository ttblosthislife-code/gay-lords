/**
 * Author: Bao Tran
 * License: CC0
 * Description: Python template for inputs, big integers.
 * Status: Approved.
 */

import sys
import math

sys.set_int_max_str_digits(0)

# input
n = int(input())
n, m = map(int, input().split())
a = list(map(int, input().split()))
s = input()
# fast input
it = iter(sys.stdin.read().strip().split())
a = int(next(it))
b = int(next(it))
s = str(next(it))
# / float, // floor, % mod, ** power, ^ xor; abs(), divmod(), pow(a,b,m)
# x.bit_length(), x.bit_count()
# math.gcd(a, b), math.isqrt(x), math.comb(n, k)
# output
# print(*objects, sep=' ', end='\n')
# keywords
# for i in range(n); for x in arr
# def f(x, y): ...