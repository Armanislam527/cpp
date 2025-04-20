
# 1. Ordered Pairs from Relations
A = {1, 2, 3, 4}
R1 = [(a, b) for a in A for b in A if b % a == 0]
R2 = [(a, b) for a in A for b in A if a <= b]
print("R1 (a divides b):", R1)
print("R2 (a <= b):", R2)

# 2. Relation and Matrix Representation
A = [1, 2, 3]
B = [1, 2]
R = [(a, b) for a in A for b in B if a > b]
matrix = [[1 if (a, b) in R else 0 for b in B] for a in A]
print("Relation R (a > b):", R)
print("Matrix Representation:")
for row in matrix:
    print(row)

# 3. Welch–Powell Graph Coloring
def welch_powell(adj):
    n = len(adj)
    degree = [(i, sum(adj[i])) for i in range(n)]
    degree.sort(key=lambda x: -x[1])
    color = [0] * n
    current_color = 1
    for i, _ in degree:
        if color[i] == 0:
            color[i] = current_color
            for j, _ in degree:
                if color[j] == 0 and all(adj[j][k] == 0 or color[k] != current_color for k in range(n)):
                    color[j] = current_color
            current_color += 1
    return color

graph = [
    [0,1,1,0,1],
    [1,0,1,1,0],
    [1,1,0,1,1],
    [0,1,1,0,1],
    [1,0,1,1,0]
]
colors = welch_powell(graph)
print("Vertex Colors:", colors)

"""
    Assigns colors to the vertices of a graph such that no two adjacent vertices
    have the same color. The algorithm works by sorting the vertices by degree
    in descending order, then assigning colors to each vertex in order by
    trying to assign the lowest possible color to each vertex. If a vertex can't
    be assigned the lowest color, the algorithm increments the current color.

    Parameters:
        graph (list of lists of int): adjacency matrix of the graph

    Returns:
        list of int: list of colors assigned to each vertex
    """
def welch_powell_coloring(graph):
    
    n = len(graph)
    degree = [sum(row) for row in graph]
    vertex = list(range(n))

    # Sort vertices by degree descending
    vertex.sort(key=lambda x: -degree[x])

    color = [0] * n
    current_color = 1

    for i in range(n):
        if color[vertex[i]] == 0:
            color[vertex[i]] = current_color
            for j in range(i + 1, n):
                can_color = True
                for k in range(n):
                    if graph[vertex[j]][k] and color[k] == current_color:
                        can_color = False
                        break
                if can_color and color[vertex[j]] == 0:
                    color[vertex[j]] = current_color
            current_color += 1

    return color


# Input
n = int(input("Enter the number of vertices: "))
graph = []
print("Enter adjacency matrix:")
for i in range(n):
    row = list(map(int, input().split()))
    graph.append(row)

# Run coloring algorithm
colors = welch_powell_coloring(graph)

# Output
print("\nVertex\tColor")
for i in range(n):
    print(f"{i}\t{colors[i]}")



# 4. Warshall’s Algorithm
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
print("Transitive Closure:")
for row in closure:
    print(row)

# 5. Matrix Union and Intersection
MR1 = [
    [1, 0, 1],
    [1, 0, 0],
    [0, 1, 0]
]
MR2 = [
    [1, 0, 1],
    [0, 1, 1],
    [1, 0, 0]
]
union = [[MR1[i][j] | MR2[i][j] for j in range(3)] for i in range(3)]
intersection = [[MR1[i][j] & MR2[i][j] for j in range(3)] for i in range(3)]
print("Union:")
for row in union:
    print(row)
print("Intersection:")
for row in intersection:
    print(row)

# 6. Newton-Gregory Forward Interpolation
import math
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

x = [1911, 1921, 1931, 1941, 1951, 1961]
y = [12, 15, 20, 27, 39, 52]
print("Estimated population in 1946:", forward_interpolation(x, y, 1946))

# 7. Newton-Gregory Backward Interpolation
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

# 8. Newton’s Divided Difference
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

# 9. Lagrange Interpolation
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

# 10. Bisection Method
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

# 11. False Position Method
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
