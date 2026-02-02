#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 1000000000;

int dist[201][201];
int friends[201];

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N = 0, M = 0;
    std::cin >> N >> M;

    for(int i = 1; i <= N; ++i)
    {
        for(int j = 1; j <= N; ++j)
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

    for(int i = 0; i < M; ++i)
    {
        int src, dest, d;
        std::cin >> src >> dest >> d;

        dist[src][dest] = std::min(dist[src][dest], d);
    }

    int K = 0;
    std::cin >> K;
    
    for(int i = 0; i < K; ++i)
    {
        std::cin >> friends[i];
    }

    for(int k = 1; k <= N; ++k)
    {
        for(int i = 1; i <= N; ++i)
        {
            for(int j = 1; j <= N; ++j)
            {
                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    
    int minTime = INF;
    std::vector<int> candidates;
    for(int i = 1; i <= N; ++i)
    {
        int time = 0;
        
        for(int j = 0; j < K; ++j)
        {
            time = std::max(time, dist[friends[j]][i] + dist[i][friends[j]]);
        }

        if(time <= minTime)
        {
            if(time < minTime)
            {
                minTime = time;
                candidates.clear();
            }

            candidates.push_back(i);
        }
    }

    for(int city : candidates)
    {
        std::cout << city << " ";
    }

    return 0;
}