#include <iostream>
#include <queue>

int N, M, P;
int S[10];
int area[10];
char map[1000][1000];
std::queue<std::pair<int, int>> q[10];

const int dy[] = { -1, 1, 0, 0 };
const int dx[] = { 0, 0, -1, 1 };

inline bool IsValid(int y, int x)
{
	return 0 <= y && y < N &&
		   0 <= x && x < M;
}

bool Expand(int p)
{
	bool moved = false;

	for (int dist = 0; dist < S[p]; ++dist)
	{
		if (q[p].empty())
		{
			break;
		}

		int qSize = q[p].size();
		while (qSize--)
		{
			std::pair<int, int> curr = q[p].front();
			q[p].pop();

			for (int d = 0; d < 4; ++d)
			{
				int ny = curr.first + dy[d];
				int nx = curr.second + dx[d];

				if (!IsValid(ny, nx) || map[ny][nx] != '.')
				{
					continue;
				}

				map[ny][nx] = '#';
				area[p]++;
				q[p].push({ ny,nx });
				moved = true;
			}
		}
	}

	return moved;
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> N >> M >> P;

	for (int i = 1; i <= P; ++i)
	{
		std::cin >> S[i];
	}

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			std::cin >> map[i][j];

			if ('1' <= map[i][j] && map[i][j] <= '9')
			{
				int owner = map[i][j] - '0';
				q[owner].push({ i, j });
				area[owner]++;
			}
		}
	}

	while (true)
	{
		bool isAnyMoved = false;

		for (int i = 1; i <= P; ++i)
		{
			if (Expand(i))
			{
				isAnyMoved = true;
			}
		}

		if (!isAnyMoved)
		{
			break;
		}
	}

	for (int i = 1; i <= P; ++i)
	{
		std::cout << area[i] << " ";
	}

	return 0;
}
