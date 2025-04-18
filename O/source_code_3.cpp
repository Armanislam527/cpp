#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    vector<int> degree(n, 0), color(n, 0), vertex(n);

    cout << "Enter adjacency matrix:\n";
    for (int i = 0; i < n; i++)
    {
        vertex[i] = i;
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
            if (graph[i][j])
                degree[i]++;
        }
    }

    sort(vertex.begin(), vertex.end(), [&](int a, int b)
         { return degree[a] > degree[b]; });

    int currentColor = 1;
    for (int i = 0; i < n; i++)
    {
        if (color[vertex[i]] == 0)
        {
            color[vertex[i]] = currentColor;
            for (int j = i + 1; j < n; j++)
            {
                bool canColor = true;
                for (int k = 0; k < n; k++)
                {
                    if (graph[vertex[j]][k] && color[k] == currentColor)
                    {
                        canColor = false;
                        break;
                    }
                }
                if (canColor && color[vertex[j]] == 0)
                    color[vertex[j]] = currentColor;
            }
            currentColor++;
        }
    }

    cout << "\nVertex\tColor\n";
    for (int i = 0; i < n; i++)
    {
        cout << i << "\t" << color[i] << endl;
    }
    return 0;
}