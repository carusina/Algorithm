#include <iostream>
#include <vector>
#include <queue>

struct lightSwitch
{
	int switchY, switchX;
};

const int dy[] = { -1, 1, 0, 0 };
const int dx[] = { 0, 0, -1, 1 };

int N, M;

std::vector<lightSwitch> rooms[101][101];
bool onLights[101][101];
int turnOnLight;
bool visited[101][101];

inline bool IsValid(const int y, const int x)
{
	return 1 <= y && y <= N &&
		   1 <= x && x <= N;
}

bool CanEnter(int y, int x)
{
	for (int d = 0; d < 4; ++d)
	{
		int ny = y + dy[d];
		int nx = x + dx[d];

		if (IsValid(ny, nx) && visited[ny][nx])
		{
			return true;
		}
	}

	return false;
}

void BFS()
{
	std::queue<std::pair<int, int>> q;
	q.push({ 1, 1 });
	visited[1][1] = true;

	onLights[1][1] = true;
	turnOnLight++;

	while (!q.empty())
	{
		std::pair<int, int> curr = q.front();
		q.pop();

		for (const lightSwitch& s : rooms[curr.first][curr.second])
		{
			int sY = s.switchY;
			int sX = s.switchX;

			if (!onLights[sY][sX])
			{
				onLights[sY][sX] = true;
				turnOnLight++;

				if (CanEnter(sY, sX) && !visited[sY][sX])
				{
					visited[sY][sX] = true;
					q.push({ sY, sX });
				}
			}
		}

		for (int d = 0; d < 4; ++d)
		{
			int ny = curr.first + dy[d];
			int nx = curr.second + dx[d];

			if (!IsValid(ny, nx))
			{
				continue;
			}

			if (!onLights[ny][nx] || visited[ny][nx])
			{
				continue;
			}

			q.push({ ny, nx });
			visited[ny][nx] = true;
		}
	}
}
 
int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> N >> M;

	for (int i = 0; i < M; ++i)
	{
		int x, y;
		int switchX, switchY;
		std::cin >> x >> y >> switchX >> switchY;

		rooms[y][x].push_back({ switchY, switchX });
	}

	BFS();

	std::cout << turnOnLight;

	return 0;
}
