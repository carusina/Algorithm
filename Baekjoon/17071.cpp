#include <iostream>
#include <queue>

const int MAX = 500000;
int N, K;
int visited[2][MAX + 1];

int BFS()
{
	int t = 0;

	std::queue<int> q;
	q.push(N);
	visited[0][N] = true;

	while (true)
	{
		if (visited[t % 2][K])
		{
			return t;
		}

		int qSize = q.size();
		if (qSize == 0)
		{
			return -1;
		}

		while (qSize--)
		{
			int curr = q.front();
			q.pop();

			int nx[] = { curr - 1, curr + 1, curr * 2 };

			for (int d = 0; d < 3; ++d)
			{
				if (0 <= nx[d] && nx[d] <= MAX)
				{
					if (!visited[(t + 1) % 2][nx[d]])
					{
						q.push(nx[d]);
						visited[(t + 1) % 2][nx[d]] = true;
					}
				}
			}
		}

		t++;
		K += t;

		if (K > MAX)
		{
			return -1;
		}
	}
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> N >> K;
	std::cout << BFS();

	return 0;
}
