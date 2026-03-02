#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

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
    long long accumulatedDist;

    const bool operator<(const PathInfo& other) const
    {
        return accumulatedDist > other.accumulatedDist;
    }
};

int N, M, K;
std::vector<Edge> edges[MAX_N];

void Dijkstra(const std::vector<int>& interviewCities)
{
    long long dist[MAX_N];
    std::fill(dist, dist + N + 1, INF);

    std::priority_queue<PathInfo> pq;
    for(int interviewCity : interviewCities)
    {
        dist[interviewCity] = 0;
        pq.push({interviewCity, 0});
    }

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
            long long nextDist = curr.accumulatedDist + edge.weight;

            if( nextDist < dist[nextNode])
            {
                pq.push({nextNode, nextDist});
                dist[nextNode] = nextDist;
            }
        }
    }

    int maxDistCity = -1;
    long long maxDist = -1;
    for(int i = 1; i <= N; ++i)
    {
        if(dist[i] != INF && dist[i] > maxDist)
        {
            maxDistCity = i;
            maxDist = dist[i];
        }
    }

    std::cout << maxDistCity << "\n" << maxDist;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N >> M >> K;
    for(int i = 0; i < M; ++i)
    {
        int u, v, c;
        std::cin >> u >> v >> c;
        edges[v].push_back({u, c});
    }

    std::vector<int> interviewCities(K);
    for(int i = 0; i < K; ++i)
    {
        std::cin >> interviewCities[i];
    }

    Dijkstra(interviewCities);

    return 0;
}