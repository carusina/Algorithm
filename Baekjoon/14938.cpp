#include <iostream>

const int INF = 1000000000;

int cntItems[101];
int dist[101][101];

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	
	int n = 0, m = 0, r = 0;
	std::cin >> n >> m >> r;

	for (int i = 1; i <= n; ++i)
	{
		std::fill(dist[i], dist[i] + n + 1, INF);
		dist[i][i] = 0;
	}

	for(int i = 1; i <= n; ++i)
	{
		std::cin >> cntItems[i];
	}

	for (int i = 1; i <= r; ++i)
	{
		int a, b, l;
		std::cin >> a >> b >> l;

		dist[a][b] = l;
		dist[b][a] = l;
	}

	for (int k = 1; k <= n; ++k)
	{
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				int d = dist[i][k] + dist[k][j];

				if (d < dist[i][j])
				{
					dist[i][j] = d;
				}
			}
		}
	}
	
	int maxCntItem = 0;
	for (int i = 1; i <= n; ++i)
	{
		int currCntItem = 0;

		for (int j = 1; j <= n; ++j)
		{
			if (dist[i][j] <= m)
			{
				currCntItem += cntItems[j];
			}
		}

		if (currCntItem > maxCntItem)
		{
			maxCntItem = currCntItem;
		}
	}

	std::cout << maxCntItem;

	return 0;
}