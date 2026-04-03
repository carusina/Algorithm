#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

constexpr int MAX_N = 500;

int N;
int buildTime[MAX_N + 1];
int totalBuildTime[MAX_N + 1];
int indegrees[MAX_N + 1];
std::vector<int> nextBuildings[MAX_N + 1];

void Solve()
{
	std::queue<int> q;

	for (int i = 1; i <= N; ++i)
	{
		if (indegrees[i] == 0)
		{
			q.push(i);
			totalBuildTime[i] = buildTime[i];
		}
	}

	while (!q.empty())
	{
		int curr = q.front();
		q.pop();

		for (int next : nextBuildings[curr])
		{
			totalBuildTime[next] = std::max(totalBuildTime[next], totalBuildTime[curr] + buildTime[next]);

			indegrees[next]--;
			if (indegrees[next] == 0)
			{
				q.push(next);
			}
		}
	}

	for (int i = 1; i <= N; ++i)
	{
		std::cout << totalBuildTime[i] << "\n";
	}
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		std::cin >> buildTime[i];

		while (true)
		{
			int prev;
			std::cin >> prev;
			if (prev == -1)
			{
				break;
			}

			nextBuildings[prev].push_back(i);
			indegrees[i]++;
		}
	}

	Solve();

	return 0;
}