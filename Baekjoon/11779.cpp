#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

constexpr int INF = 0x3f3f3f3f;
constexpr int MAX_N = 1001;

struct Edge
{
    int to;
    int weight;
};

struct PathInfo
{
    int node;
    int accumulatedDist;

    const bool operator<(const PathInfo other) const
    {
        return accumulatedDist > other.accumulatedDist;
    }
};

int n, m;
int src, dest;

std::vector<Edge> edges[MAX_N];
int dist[MAX_N];
int preNode[MAX_N];

void Dijkstra()
{
    std::memset(dist, INF, sizeof(dist));

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
            int nextNode = edge.to;
            int nextDist = curr.accumulatedDist + edge.weight;

            if(nextDist < dist[nextNode])
            {
                preNode[nextNode] = curr.node;
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

    std::cin >> n >> m;
    for(int i = 0; i < m; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        edges[u].push_back({v, w});
    }

    std::cin >> src >> dest;

    Dijkstra();

    std::vector<int> path;
    int traceNode = dest;
    while(traceNode != 0)
    {
        path.push_back(traceNode);
        if(traceNode == src)
        {
            break;
        }

        traceNode = preNode[traceNode];
    }
    std::reverse(path.begin(), path.end());

    std::cout << dist[dest] << "\n";
    std::cout << path.size() << "\n";
    for(int node : path)
    {
        std::cout << node << " ";
    }

    return 0;
}