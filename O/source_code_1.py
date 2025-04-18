A = {1, 2, 3, 4}

R1 = [(a, b) for a in A for b in A if b % a == 0]
R2 = [(a, b) for a in A for b in A if a <= b]

print("R1 (a divides b):", R1)
print("R2 (a <= b):", R2)
