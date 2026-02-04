#include <iostream>
#include <algorithm>

const int INF = 0x3f3f3f3f;

int V, E;
int dist[401][401];

int minDist = INF;

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> V >> E;
	for (int i = 1; i <= V; ++i)
	{
		for (int j = 1; j <= V; ++j)
		{
			dist[i][j] = INF;
		}
	}

	for (int i = 0; i < E; ++i)
	{
		int src, dest, d;
		std::cin >> src >> dest >> d;

		dist[src][dest] = d;
	}

	for (int k = 1; k <= V; ++k)
	{
		for (int i = 1; i <= V; ++i)
		{
			for (int j = 1; j <= V; ++j)
			{
				if (dist[i][k] != INF && dist[k][j] != INF)
				{
					dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
	}

	minDist = dist[1][1];
	for (int i = 2; i <= V; ++i)
	{
		minDist = std::min(minDist, dist[i][i]);
	}

	std::cout << (minDist == INF ? -1 : minDist);

	return 0;
}
