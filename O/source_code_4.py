def warshall(matrix):
    n = len(matrix)
    for k in range(n):
        for i in range(n):
            for j in range(n):
                matrix[i][j] = matrix[i][j] or (matrix[i][k] and matrix[k][j])
    return matrix

adj = [
    [0,1,0,0],
    [0,0,1,0],
    [1,0,0,1],
    [0,0,0,1]
]

closure = warshall(adj)
for row in closure:
    print(row)
