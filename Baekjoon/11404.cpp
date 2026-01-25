#include <iostream>
#include <algorithm>

const int INF = 10000000;

int dist[101][101];

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n = 0, m = 0;
    std::cin >> n >> m;
    
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            if(i == j)
            {
                dist[i][j] = 0;
            }
            else
            {
                dist[i][j] = INF;
            }
        }
    }

    for(int i = 0; i < m; ++i)
    {
        int u = 0, v = 0, w = 0;
        std::cin >> u >> v >> w;
        dist[u][v] = std::min(dist[u][v], w);
    }

    for(int k = 1; k <= n; ++k)
    {
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= n; ++j)
            {
                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            if(dist[i][j] == INF)
            {
                std::cout << 0 << " ";
            }
            else
            {
                std::cout << dist[i][j] << " ";
            }
        }

        std::cout << "\n";
    }

    return 0;
}