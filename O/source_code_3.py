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
