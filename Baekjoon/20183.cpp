#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

constexpr int MAX_N = 100001;
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;

struct Edge
{
    int dest;
    int weight;
};

struct PathInfo
{
    int node;
    long long accumlatedCost;

    const bool operator<(const PathInfo& other) const
    {
        return accumlatedCost > other.accumlatedCost;
    }
};

int N, M, A, B;
long long C;

std::vector<Edge> edges[MAX_N];
long long dist[MAX_N];

bool Dijkstra(long long limit)
{
    std::fill(dist, dist + N + 1, INF);

    std::priority_queue<PathInfo> pq;
    pq.push({A, 0});
    dist[A] = 0;

    while(!pq.empty())
    {
        PathInfo curr = pq.top();
        pq.pop();

        if(curr.node == B)
        {
            return curr.accumlatedCost <= C;
        }

        if(curr.accumlatedCost > dist[curr.node])
        {
            continue;
        }

        for(const Edge& edge : edges[curr.node])
        {
            if(edge.weight > limit)
            {
                continue;
            }

            int nextNode = edge.dest;
            long long nextCost = curr.accumlatedCost + edge.weight;

            if(nextCost < dist[nextNode])
            {
                pq.push({nextNode, nextCost});
                dist[nextNode] = nextCost;
            }
        }
    }

    return false;
}

int ParametricSearch()
{
    long long left = 1;
    long long right = 1e9;
    long long answer = -1;

    while(left <= right)
    {
        long long mid = left + (right - left) / 2;

        if(Dijkstra(mid))
        {
            answer = mid;
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return answer;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N >> M >> A >> B >> C;
    for(int i = 0; i < M; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        edges[u].push_back({v, w});
        edges[v].push_back({u, w});
    }

    std::cout << ParametricSearch();

    return 0;
}