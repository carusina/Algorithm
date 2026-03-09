#include <iostream>
#include <queue>
#include <vector>

constexpr int MAX_N = 32001;

int N, M;
std::vector<int> adj[MAX_N];
int indegree[MAX_N];

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> N >> M; 
	for (int i = 0; i < M; ++i)
	{
		int u, v;
		std::cin >> u >> v;

		adj[u].push_back(v);
		indegree[v]++;
	}

	std::queue<int> q;
	for (int i = 1; i <= N; ++i)
	{
		if (indegree[i] == 0)
		{
			q.push(i);
		}
	}

	while (!q.empty())
	{
		int curr = q.front();
		q.pop();

		std::cout << curr << " ";

		for (const int next : adj[curr])
		{
			indegree[next]--;

			if (indegree[next] == 0)
			{
				q.push(next);
			}
		}
	}

	return 0;
}
