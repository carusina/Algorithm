// https://swexpertacademy.com/main/talk/solvingClub/problemView.do?contestProbId=AV5LwsHaD1MDFAXc&solveclubId=AZwrPjFqFyDHBIT3&problemBoxTitle=2%EC%A3%BC%EC%B0%A8&problemBoxCnt=6&probBoxId=AZxWf_YKvf3HBIT3

#include <iostream>

// ====================
// 상수 선언
// ====================

#define MAX_N 300
#define MAX_DIR 8

constexpr int dy[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
constexpr int dx[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

// ====================
// 구조체 선언
// ====================

struct Pos
{
	int y, x;
};

// ====================
// 전역 변수 선언
// ====================

int gridSize;
char grid[MAX_N][MAX_N];

int countMine;
int mineGrid[MAX_N][MAX_N];

int countVisited, zeroClick;
int visited[MAX_N][MAX_N];

int front, rear;
Pos q[MAX_N * MAX_N + 1];

// ====================
// 유틸 함수 구현부
// ====================

inline void Init()
{
	countMine = countVisited = zeroClick = 0;
}

inline bool IsValid(int y, int x)
{
	return 0 <= y && y < gridSize &&
		   0 <= x && x < gridSize;
}

// ====================
// 로직 구현부
// ====================

int GetAroundMines(int y, int x)
{
	int mines = 0;
	if (grid[y][x] == '*') return -1;

	for (int d = 0; d < MAX_DIR; ++d)
	{
		int ny = y + dy[d];
		int nx = x + dx[d];

		if (IsValid(ny, nx) && grid[ny][nx] == '*') ++mines;
	}

	return mines;
}

void BuildMineGrid()
{
	for (int i = 0; i < gridSize; ++i)
	{
		for (int j = 0; j < gridSize; ++j)
		{
			mineGrid[i][j] = GetAroundMines(i, j);
		}
	}
}

void ClickZeroCells(int stamp)
{
	for (int i = 0; i < gridSize; ++i)
	{
		for (int j = 0; j < gridSize; ++j)
		{
			if (mineGrid[i][j] == 0 && visited[i][j] != stamp)
			{
				++zeroClick;
				++countVisited;

				front = rear = 0;

				q[rear++] = { i, j };
				visited[i][j] = stamp;

				while (front < rear)
				{
					Pos curr = q[front++];

					for (int d = 0; d < MAX_DIR; ++d)
					{
						int ny = curr.y + dy[d];
						int nx = curr.x + dx[d];

						if (IsValid(ny, nx) && visited[ny][nx] != stamp && mineGrid[ny][nx] != -1)
						{
							++countVisited;
							visited[ny][nx] = stamp;
							
							if (mineGrid[ny][nx] == 0) q[rear++] = { ny, nx };
						}
					}
				}
			}
		}
	}
}

// ====================
// main 함수 구현부
// ====================

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	int T;
	std::cin >> T;
	for (int tc = 1; tc <= T; ++tc)
	{
		std::cin >> gridSize;
		Init();

		for (int i = 0; i < gridSize; ++i)
		{
			for (int j = 0; j < gridSize; ++j)
			{
				std::cin >> grid[i][j];
				if (grid[i][j] == '*') ++countMine;
			}
		}

		BuildMineGrid();
		ClickZeroCells(tc);
		std::cout << "#" << tc << " " << (gridSize * gridSize - countMine - countVisited + zeroClick) << "\n";
	}

	return 0;
}