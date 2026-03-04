#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int MAX_N = 100001;

struct Edge
{
	int dest;
	int i;
};

struct PathInfo
{
	int node;
	long long accumulatedTime;

	const bool operator<(const PathInfo& other) const
	{
		return accumulatedTime > other.accumulatedTime;
	}
};

int N, M;
std::vector<Edge> edges[MAX_N];
long long dist[MAX_N];

long long Dijkstra()
{
	std::fill(dist, dist + N + 1, INF);

	std::priority_queue<PathInfo> pq;
	pq.push({ 1, 0 });
	dist[1] = 0;
	
	while (!pq.empty())
	{
		PathInfo curr = pq.top();
		pq.pop();

		if (curr.node == N)
		{
			return curr.accumulatedTime;
		}

		if (curr.accumulatedTime > dist[curr.node])
		{
			continue;
		}

		for (const Edge& edge : edges[curr.node])
		{
			int nextNode = edge.dest;
			int nextIndex = edge.i;

			long long waitingTime = (nextIndex - (curr.accumulatedTime % M) + M) % M;
			long long nextTime = curr.accumulatedTime + waitingTime + 1;

			if (nextTime < dist[nextNode])
			{
				dist[nextNode] = nextTime;
				pq.push({ nextNode, nextTime });
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
	for (int i = 0; i < M; ++i)
	{
		int u, v;
		std::cin >> u >> v;

		edges[u].push_back({ v, i });
		edges[v].push_back({ u, i });
	}

	std::cout << Dijkstra();

	return 0;
}
