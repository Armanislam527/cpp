#include <iostream>
using namespace std;

int main()
{
    int MR1[3][3] = {
        {1, 0, 1},
        {1, 0, 0},
        {0, 1, 0}};

    int MR2[3][3] = {
        {1, 0, 1},
        {0, 1, 1},
        {1, 0, 0}};

    int unionMatrix[3][3], intersectMatrix[3][3];

    // Calculate Union and Intersection
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            unionMatrix[i][j] = MR1[i][j] | MR2[i][j];
            intersectMatrix[i][j] = MR1[i][j] & MR2[i][j];
        }
    }

    cout << "Union (MR1 ∪ MR2):\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << unionMatrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nIntersection (MR1 ∩ MR2):\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << intersectMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}