A = [1, 2, 3]
B = [1, 2]

R = [(a, b) for a in A for b in B if a > b]
matrix = [[1 if (a, b) in R else 0 for b in B] for a in A]

print("Relation R (a > b):", R)
print("Matrix Representation:")
for row in matrix:
    print(row)
