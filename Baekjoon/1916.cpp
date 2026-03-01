#include <iostream>
#include <vector>
#include <queue>

constexpr int INF = 0x3f3f3f3f;
constexpr int MAX_N = 1001;

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

int N, M;
int src, dest;
std::vector<Edge> edges[MAX_N];
std::vector<int> dist;

int Dijkstra()
{
    dist.assign(N + 1, INF);

    std::priority_queue<PathInfo> pq;
    dist[src] = 0;
    pq.push({src, 0});

    while(!pq.empty())
    {
        PathInfo curr = pq.top();
        pq.pop();

        if(curr.node == dest)
        {
            return dist[dest];
        }

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

    return -1;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N >> M;
    for(int i = 0; i < M; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        edges[u].push_back({v, w});
    }
    std::cin >> src >> dest;

    std::cout << Dijkstra();

    return 0;
}