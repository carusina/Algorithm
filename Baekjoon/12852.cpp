#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

const int MAX_N = 1000001;

int N;
int visited[MAX_N];

void BFS()
{
	std::queue<int> q;
	q.push(N);
	visited[N] = true;

	while (!q.empty())
	{
		int curr = q.front();
		q.pop();

		if (curr == 1)
		{
			return;
		}

		int nx[3];
		nx[0] = curr - 1;
		nx[1] = curr % 2 == 0 ? curr / 2 : 0;
		nx[2] = curr % 3 == 0 ? curr / 3 : 0;

		for (int n : nx)
		{
			if (n > 0 && visited[n] == 0)
			{
				q.push(n);
				visited[n] = curr;
			}
		}
	}
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> N;
	BFS();

	std::vector<int> path;
	int curr = 1;
	while (curr != N)
	{
		path.push_back(curr);
		curr = visited[curr];
	}
	path.push_back(N);
	std::reverse(path.begin(), path.end());

	std::cout << path.size() - 1 << "\n";
	for (int p : path)
	{
		std::cout << p << " ";
	}

	return 0;
}
