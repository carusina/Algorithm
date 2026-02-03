#include <iostream>

const int INF = 10000000;
int dist[10][10];
int visited[10];
int minDist = INF;

void DFS(int N, int curr, int cost, int cnt)
{
    if(cost >= minDist)
    {
        return;
    }

    if(cnt == N)
    {
        minDist = minDist > cost ? cost : minDist;
        return;
    }

    for(int i = 0; i < N; ++i)
    {
        if(!visited[i])
        {
            visited[i] = true;
            DFS(N, i, cost + dist[curr][i], cnt + 1);
            
            visited[i] = false;
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N = 0, K = 0;
    std::cin >> N >> K;

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            std::cin >> dist[i][j];
        }
    }

    for(int k = 0; k < N; ++k)
    {
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                int d = dist[i][k] + dist[k][j];

                if(d < dist[i][j])
                {
                    dist[i][j] = d;
                }
            }
        }
    }

    visited[K] = true;
    DFS(N, K, 0, 1);
    std::cout << minDist;

    return 0;
}