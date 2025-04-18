#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;
    int path[10][10];

    cout << "Enter the adjacency matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> path[i][j];
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                path[i][j] = path[i][j] || (path[i][k] && path[k][j]);
            }
        }
    }

    cout << "\nTransitive Closure Matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << path[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}