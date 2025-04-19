def warshall_closure(matrix):
    n = len(matrix)
    for k in range(n):
        for i in range(n):
            for j in range(n):
                matrix[i][j] = matrix[i][j] or (matrix[i][k] and matrix[k][j])
    return matrix

# Input
n = int(input("Enter the number of vertices: "))
path = []

print("Enter the adjacency matrix:")
for _ in range(n):
    row = list(map(int, input().split()))
    path.append(row)

# Compute transitive closure
closure = warshall_closure(path)

# Output
print("\nTransitive Closure Matrix:")
for row in closure:
    print(" ".join(map(str, row)))
