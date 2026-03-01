#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

constexpr int INF = 0x3f3f3f3f;
constexpr int MAX_N = 1001;
constexpr int MAX_M = 10001;

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

int N, M, X;

std::vector<Edge> forwardEdges[MAX_N];
std::vector<Edge> backwardEdges[MAX_N];

void Dijkstra(std::vector<int>& dist, const std::vector<Edge> edges[MAX_N])
{
    dist.assign(N + 1, INF);

    std::priority_queue<PathInfo> pq;
    dist[X] = 0;
    pq.push({X, 0});

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

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N >> M >> X;
    for(int i = 0; i < M; ++i)
    {
        int src, dest, weight;
        std::cin >> src >> dest >> weight;

        forwardEdges[src].push_back({dest, weight});
        backwardEdges[dest].push_back({src, weight});
    }

    std::vector<int> distFromX;
    std::vector<int> distToX;

    Dijkstra(distFromX, forwardEdges);
    Dijkstra(distToX, backwardEdges);

    int maxDist = 0;
    for(int i = 1; i <= N; ++i)
    {
        maxDist = std::max(maxDist, distFromX[i] + distToX[i]);
    }

    std::cout << maxDist;

    return 0;
}