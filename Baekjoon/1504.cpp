#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

constexpr int INF = 0x3f3f3f3f;
constexpr int MAX_N = 801;

struct Edge
{
    int dest;
    int weight;
};

struct PathInfo
{
    int node;
    int accumulatedDist;

    const bool operator<(const PathInfo& other) const
    {
        return accumulatedDist > other.accumulatedDist;
    }
};

std::vector<Edge> edges[MAX_N];

int N, E;
int v1, v2;

void Dijkstra(std::vector<int>& dist, int src)
{
    dist.assign(N + 1, INF);

    std::priority_queue<PathInfo> pq;
    dist[src] = 0;
    pq.push({src, 0});

    while(!pq.empty())
    {
        PathInfo curr = pq.top();
        pq.pop();

        if(curr.accumulatedDist > dist[curr.node])
        {
            continue;
        }

        for(const Edge& edge : edges[curr.node])
        {
            int nextNode = edge.dest;
            int nextDist = curr.accumulatedDist + edge.weight;

            if(nextDist < dist[nextNode])
            {
                dist[nextNode] = nextDist;
                pq.push({nextNode, nextDist});
            }
        }
    }
}

long long GetTotalDist(int dist1, int dist2, int dist3)
{
    if(dist1 == INF || dist2 == INF || dist3 == INF)
    {
        return INF;
    }

    return dist1 + dist2 + dist3;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N >> E;
    for(int i = 0; i < E; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        edges[u].push_back({v, w});
        edges[v].push_back({u, w});
    }
    std::cin >> v1 >> v2;

    std::vector<int> distFromStart;
    std::vector<int> distFromConnect1;
    std::vector<int> distFromConnect2;

    Dijkstra(distFromStart, 1);
    Dijkstra(distFromConnect1, v1);
    Dijkstra(distFromConnect2, v2);

    long long path1 = GetTotalDist(distFromStart[v1], distFromConnect1[v2], distFromConnect2[N]);
    long long path2 = GetTotalDist(distFromStart[v2], distFromConnect2[v1], distFromConnect1[N]);
    
    long long minDist = std::min(path1, path2);
    if(minDist >= INF)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << minDist;
    }

    return 0;
}