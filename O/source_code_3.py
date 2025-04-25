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
                        print(graph[vertex[j]][k], color[k])
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
