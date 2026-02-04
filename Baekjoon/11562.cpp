#include <iostream>
#include <algorithm>

const int INF = 0x3f3f3f3f;

int n, m;
int dist[251][251];

int k;

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

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
        int u, v, b;
        std::cin >> u >> v >> b;

        switch (b)
        {
            case 0:
                dist[u][v] = 0;
                dist[v][u] = 1;
                break;
            case 1:
                dist[u][v] = 0;
                dist[v][u] = 0;
                break;
        }
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

    std::cin >> k;
    for(int i = 0; i < k; ++i)
    {
        int s, e;
        std::cin >> s >> e;

        std::cout << dist[s][e] << "\n";
    }

    return 0;
}