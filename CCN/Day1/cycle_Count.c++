/* 
 * C++ Program to Find Number of Cycles in a Graph
 */
#include<iostream>
#define SIZE 20
using namespace std;
 
bool map[SIZE][SIZE], F;
long long f[1 << SIZE][SIZE], res = 0;
/* 
 * Main: count the number of cycles in a graph
 */
int main()
{

    int n , m, i, j, k, l, x, y;
    cout<<"Enter number of vertices and number of edges: ";
    cin>>n>>m;
    for (i = 0; i < m; i++)
    {
        cout<<"Enter source vertex and destination vertex of an edge:: ";
        cin>>x>>y;
        x--;
        y--;
        if (x > y)
           swap(x, y);
        map[x][y] = map[y][x] = 1;
        f[(1 << x) + (1 << y)][y] = 1;
    }
 
    for (i = 7; i < (1 << n); i++)
    {
        F = 1;
        for (j = 0; j < n; j++)
        {
            if (i & (1 << j) && f[i][j] == 0)
            {
                if (F)
                {
                    F = 0;
                    k = j;
                    continue;
                }
                for (l = k + 1; l < n; l++)
                {
                    if (i & (1 << l) && map[j][l])
                        f[i][j] += f[i - (1 << j)][l];
                }
                if (map[k][j])
                    res += f[i][j];
            }    
        }
    }
    cout<<"Number of Cycles: "<<res/2<<endl;
    return 0;
}