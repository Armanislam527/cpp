def f(x): return x**2 - 4*x - 10

a, b = -2, -1.5
tolerance = 0.0001

while (b - a) >= tolerance:
    c = (a + b) / 2
    if f(c) == 0:
        break
    elif f(c) * f(a) < 0:
        b = c
    else:
        a = c

print("Root using Bisection:", c)
