#include <iostream>

int N;
int dist[20][20];
int unused[20][20];

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> N;
	
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cin >> dist[i][j];
		}
	}

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (i == j)
			{
				continue;
			}

			for (int k = 0; k < N; ++k)
			{
				if (k == i || k == j)
				{
					continue;
				}

				if (dist[i][k] + dist[k][j] < dist[i][j])
				{
					std::cout << -1;
					return 0;
				}

				if (dist[i][k] + dist[k][j] == dist[i][j])\
				{
					unused[i][j] = true;
				}
			}
		}
	}

	int totalWeights = 0;
	for (int i = 0; i < N; ++i)
	{
		for (int j = i + 1; j < N; ++j)
		{
			if (!unused[i][j])
			{
				totalWeights += dist[i][j];
			}
		}
	}

	std::cout << totalWeights;

	return 0;
}
