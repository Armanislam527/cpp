def forward_interpolation(x, y, X):
    n = len(y)
    diff = [y.copy()] + [[0]*n for _ in range(n-1)]
    for i in range(1, n):
        for j in range(n-i):
            diff[i][j] = diff[i-1][j+1] - diff[i-1][j]
    h = x[1] - x[0]
    u = (X - x[0]) / h
    result = y[0]
    u_term = 1
    for i in range(1, n):
        u_term *= (u - (i - 1))
        result += (u_term * diff[i][0]) / math.factorial(i)
    return result

import math
x = [1911, 1921, 1931, 1941, 1951, 1961]
y = [12, 15, 20, 27, 39, 52]
print("Estimated population in 1946:", forward_interpolation(x, y, 1946))
