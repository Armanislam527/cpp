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
