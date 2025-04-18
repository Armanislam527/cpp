def f(x): return x**2 - x - 2

a, b = 1, 3
tolerance = 0.0001

while True:
    c = a - (f(a) * (b - a)) / (f(b) - f(a))
    if abs(f(c)) < tolerance:
        break
    elif f(a) * f(c) < 0:
        b = c
    else:
        a = c

print("Root using False Position:", c)
