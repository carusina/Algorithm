#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

constexpr int INF = 0x3f3f3f3f;
constexpr int MAX_V = 20001;
constexpr int MAX_E = 300001;

struct Edge
{
	int to;
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

int V, E, K;
std::vector<Edge> graph[MAX_V];
int dist[MAX_V]; // about start

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> V >> E;
	std::cin >> K;
	for (int i = 0; i < E; ++i)
	{
		int u, v, w;
		std::cin >> u >> v >> w;
		
		graph[u].push_back({ v, w });
	}

	std::priority_queue<PathInfo> pq;

	std::memset(dist, INF, sizeof(dist));
	
	dist[K] = 0;
	pq.push({ K, 0 });

	while (!pq.empty())
	{
		PathInfo curr = pq.top();
		pq.pop();

		if (curr.accumulatedDist > dist[curr.node])
		{
			continue;
		}

		for (const Edge& edge : graph[curr.node])
		{
			int nextNode = edge.to;
			int nextDist = curr.accumulatedDist + edge.weight;

			if (nextDist < dist[nextNode])
			{
				dist[nextNode] = nextDist;
				pq.push({ nextNode, nextDist });
			}
		}
	}

	for (int i = 1; i <= V; ++i)
	{
		if (dist[i] == INF)
		{
			std::cout << "INF" << "\n";
		}
		else
		{
			std::cout << dist[i] << "\n";
		}
	}

	return 0;
}
