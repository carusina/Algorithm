#include <iostream>

int graph[101][101];
int visited[101][101];

void DFS(int N, int start, int curr, int visitedRow[]);

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	int N = 0;
	std::cin >> N;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cin >> graph[i][j];
		}
	}

	for (int i = 0; i < N; ++i)
	{
		DFS(N, i, i, visited[i]);
	}

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cout << visited[i][j] << " ";
		}
		std::cout << "\n";
	}

	return 0;
}

void DFS(int N, int start, int curr, int visitedRow[])
{
	for (int next = 0; next < N; ++next)
	{
		if (graph[curr][next] == 1 && visitedRow[next] == 0)
		{
			visitedRow[next] = 1;
			DFS(N, start, next, visitedRow);
		}
	}
}