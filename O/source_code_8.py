def divided_difference(x, y, X):
    n = len(x)
    table = [y.copy()] + [[0]*n for _ in range(n-1)]
    for i in range(1, n):
        for j in range(n-i):
            table[i][j] = (table[i-1][j+1] - table[i-1][j]) / (x[j+i] - x[j])
    result = y[0]
    term = 1
    for i in range(1, n):
        term *= (X - x[i-1])
        result += term * table[i][0]
    return result

x = [4,5,7,10,11,13]
y = [48,100,294,900,1210,2028]
print("f(15) =", divided_difference(x, y, 15))
