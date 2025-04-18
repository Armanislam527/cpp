def lagrange_interpolation(x, y, X):
    n = len(x)
    result = 0
    for i in range(n):
        term = y[i]
        for j in range(n):
            if i != j:
                term *= (X - x[j]) / (x[i] - x[j])
        result += term
    return result

x = [5,6,9,11]
y = [12,13,14,16]
print("y at x = 10:", lagrange_interpolation(x, y, 10))
