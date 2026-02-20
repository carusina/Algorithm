#include <iostream>
#include <cstring>
#include <algorithm>

constexpr int INF = 0x3f3f3f3f;
constexpr int MAX_N = 201;

int dist[MAX_N][MAX_N];
int firstPath[MAX_N][MAX_N];

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
		
	std::memset(dist, INF, sizeof(dist));
	std::memset(firstPath, INF, sizeof(firstPath));

	int N, M;
	std::cin >> N >> M;
	for (int i = 0; i < M; ++i)
	{
		int a, b, d;
		std::cin >> a >> b >> d;
		if(d < dist[a][b])
		{
			dist[a][b] = d;
			dist[b][a] = d;

			firstPath[a][b] = b;
			firstPath[b][a] = a;
		}
	}

	for (int k = 1; k <= N; ++k)
	{
		for (int i = 1; i <= N; ++i)
		{
			for (int j = 1; j <= N; ++j)
			{
				if (i == j)
				{
					continue;
				}

				if (dist[i][j] > dist[i][k] + dist[k][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					firstPath[i][j] = firstPath[i][k];
				}
			}
		}
	}

	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			if (firstPath[i][j] == INF)
			{
				std::cout << "- ";
			}
			else
			{
				std::cout << firstPath[i][j] << " ";
			}
		}

		std::cout << "\n";
	}

	return 0;
}
