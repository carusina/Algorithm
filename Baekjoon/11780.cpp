#include <iostream>
#include <vector>

const int INF = 1000000000;
int dist[101][101];
int next[101][101];

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	for (int i = 1; i < 101; ++i)
	{
		for (int j = 1; j < 101; ++j)
		{
			if (i == j)
			{
				dist[i][j] = 0;
			}
			else
			{
				dist[i][j] = INF;
			}
		}
	}

	int N = 0, M = 0;
	std::cin >> N >> M;

	for (int i = 0; i < M; ++i)
	{
		int src = 0, dest = 0, d = 0;
		std::cin >> src >> dest >> d;

		if (d < dist[src][dest])
		{
			dist[src][dest] = d;
			next[src][dest] = dest;
		}
	}

	for (int k = 1; k <= N; ++k)
	{
		for (int src = 1; src <= N; ++src)
		{
			for (int dest = 1; dest <= N; ++dest)
			{
				int d = dist[src][k] + dist[k][dest];
				
				if (d < dist[src][dest])
				{
					dist[src][dest] = d;
					next[src][dest] = next[src][k];
				}
			}
		}
	}
	
	for (int src = 1; src <= N; ++src)
	{
		for (int dest = 1; dest <= N; ++dest)
		{
			if (dist[src][dest] == INF)
			{
				std::cout << 0 << " ";
			}
			else
			{
				std::cout << dist[src][dest] << " ";
			}
		}
		std::cout << "\n";
	}

	for (int src = 1; src <= N; ++src)
	{
		for (int dest = 1; dest <= N; ++dest)
		{
			if (src == dest || dist[src][dest] == INF)
			{
				std::cout << 0 << "\n";
				continue;
			}

			std::vector<int> path;
			int curr = src;

			while(curr != dest)
			{
				path.push_back(curr);
				curr = next[curr][dest];
			}
			path.push_back(dest);

			std::cout << path.size() << " ";
			for (int p : path)
			{
				std::cout << p << " ";
			}
			std::cout << "\n";
		}
	}

	return 0;
}
