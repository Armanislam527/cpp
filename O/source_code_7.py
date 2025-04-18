def backward_interpolation(x, y, X):
    n = len(y)
    diff = [y.copy()] + [[0]*n for _ in range(n-1)]
    for i in range(1, n):
        for j in range(n-1, i-1, -1):
            diff[i][j] = diff[i-1][j] - diff[i-1][j-1]
    h = x[1] - x[0]
    u = (X - x[-1]) / h
    result = y[-1]
    u_term = 1
    for i in range(1, n):
        u_term *= (u + i - 1)
        result += (u_term * diff[i][n-1]) / math.factorial(i)
    return result

x = [1,2,3,4,5,6,7,8]
y = [1,8,27,64,125,216,343,512]
print("f(7.5) =", backward_interpolation(x, y, 7.5))
