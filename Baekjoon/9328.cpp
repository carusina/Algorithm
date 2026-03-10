#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

constexpr int MAX_H = 101;
constexpr int MAX_W = 101;

constexpr int dy[] = { -1, 1, 0, 0 };
constexpr int dx[] = { 0, 0, -1, 1 };

int h, w;
std::string board[MAX_H];
bool visited[MAX_H][MAX_W];
bool hasKey['z' - 'a' + 1];

std::queue<std::pair<int, int>> q;
std::queue<std::pair<int, int>> waitingDoors['z' - 'a' + 1];

bool inline IsValid(int y, int x)
{
	return 0 <= y && y < h &&
		   0 <= x && x < w;
}

bool inline IsBoundary(int y, int x)
{
	return 0 == y || y == h - 1 ||
		   0 == x || x == w - 1;
}

int BFS()
{
	int getDocuments = 0;

	while (!q.empty())
	{
		std::pair<int, int> curr = q.front();
		q.pop();

		int currCell = board[curr.first][curr.second];

		if ('a' <= currCell && currCell <= 'z')
		{
			if (!hasKey[currCell - 'a'])
			{
				hasKey[currCell - 'a'] = true;

				while (!waitingDoors[currCell - 'a'].empty())
				{
					q.push(waitingDoors[currCell - 'a'].front());
					waitingDoors[currCell - 'a'].pop();
				}
			}
		}
		else if ('A' <= currCell && currCell <= 'Z')
		{
			if (!hasKey[currCell - 'A'])
			{
				waitingDoors[currCell - 'A'].push({ curr.first, curr.second });
				continue;
			}
		}
		else if (currCell == '$')
		{
			getDocuments++;
		}

		for (int d = 0; d < 4; ++d)
		{
			int ny = curr.first + dy[d];
			int nx = curr.second + dx[d];

			if (IsValid(ny, nx) && !visited[ny][nx] && board[ny][nx] != '*')
			{
				q.push({ ny, nx });
				visited[ny][nx] = true;
			}
		}
	}
	
	return getDocuments;
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	int T;
	std::cin >> T;
	for (int tc = 1; tc <= T; ++tc)
	{
		std::fill(&visited[0][0], &visited[MAX_H][0], false);
		std::fill(&hasKey[0], &hasKey['z' - 'a' + 1], false);
		
		q = std::queue<std::pair<int, int>>();
		for (int i = 'a'; i <= 'z'; ++i)
		{
			waitingDoors[i - 'a'] = std::queue<std::pair<int, int>>();
		}

		std::cin >> h >> w;

		for (int i = 0; i < h; ++i)
		{
			std::cin >> board[i];

			for (int j = 0; j < w; ++j)
			{
				if (IsBoundary(i, j) && board[i][j] != '*')
				{
					q.push({ i, j });
					visited[i][j] = true;
				}
			}
		}

		std::string keys;
		std::cin >> keys;
		if (keys != "0")
		{
			for (int i = 0; i < keys.length(); ++i)
			{
				hasKey[keys[i] - 'a'] = true;
			}
		}

		std::cout << BFS() << "\n";
	}

	return 0;
}
