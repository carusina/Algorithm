#include <iostream>
#include <algorithm>

constexpr int INF = 0x3f3f3f3f;
constexpr int MAX_N = 301;

int N, M, T;
int maxHeight[MAX_N][MAX_N];

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	
	std::fill(&maxHeight[0][0], &maxHeight[0][0] + (MAX_N * MAX_N), INF);

	std::cin >> N >> M >> T;
	for (int i = 1; i <= N; ++i)
	{
		maxHeight[i][i] = 0;
	}

	for (int i = 0; i < M; ++i)
	{
		int u, v, h;
		std::cin >> u >> v >> h;

		maxHeight[u][v] = h;
	}

	for (int k = 1; k <= N; ++k)
	{
		for (int i = 1; i <= N; ++i)
		{
			for (int j = 1; j <= N; ++j)
			{
				maxHeight[i][j] = std::min(maxHeight[i][j], std::max(maxHeight[i][k], maxHeight[k][j]));
			}
		}
	}
	
	for (int i = 0; i < T; ++i)
	{
		int s, e;
		std::cin >> s >> e;

		std::cout << (maxHeight[s][e] == INF ? -1 : maxHeight[s][e]) << "\n";
	}

	return 0;
}
