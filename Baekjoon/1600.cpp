#include <iostream>
#include <queue>

int board[201][201];
int dist[201][201][31];

const int dHorseY[] = { -1, -2, -2, -1, 1, 2, 2, 1 };
const int dHorseX[] = { -2, -1, 1, 2, 2, 1, -1, -2 };

const int dMonkeyY[] = { 0, 0, -1 ,1 };
const int dMonkeyX[] = { -1, 1, 0, 0 };

inline bool IsValid(int H, int W, int y, int x);
int BFS(int K, int H, int W);

struct Point
{
	int y, x;
	int k;
};

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	int K = 0;
	std::cin >> K;

	int W = 0, H = 0;
	std::cin >> W >> H;

	for (int i = 0; i < H; ++i)
	{
		for (int j = 0; j < W; ++j)
		{
			std::cin >> board[i][j];
		}
	}

	std::cout << BFS(K, H, W);

	return 0;
}

inline bool IsValid(int H, int W, int y, int x)
{
	return 0 <= y && y < H &&
		   0 <= x && x < W;
}

int BFS(int K, int H, int W)
{
	std::queue<Point> q;
	q.push({ 0, 0, 0 });
	dist[0][0][0] = 1;

	while (!q.empty())
	{
		Point curr = q.front();
		q.pop();

		if (curr.y == H - 1 && curr.x == W - 1)
		{
			return dist[curr.y][curr.x][curr.k] - 1;
		}

		if (curr.k < K)
		{
			for (int d = 0; d < 8; ++d)
			{
				int ny = curr.y + dHorseY[d];
				int nx = curr.x + dHorseX[d];
				int nk = curr.k + 1;

				if (!IsValid(H, W, ny, nx) || board[ny][nx] == 1)
				{
					continue;
				}

				if (dist[ny][nx][nk] != 0)
				{
					continue;
				}

				dist[ny][nx][nk] = dist[curr.y][curr.x][curr.k] + 1;
				q.push({ ny, nx, nk });
			}
		}

		for (int d = 0; d < 4; ++d)
		{
			int ny = curr.y + dMonkeyY[d];
			int nx = curr.x + dMonkeyX[d];
			int nk = curr.k;

			if (!IsValid(H, W, ny, nx) || board[ny][nx] == 1)
			{
				continue;
			}

			if (dist[ny][nx][nk] != 0)
			{
				continue;
			}

			dist[ny][nx][nk] = dist[curr.y][curr.x][curr.k] + 1;
			q.push({ ny, nx, nk });
		}
	}

	return -1;
}
