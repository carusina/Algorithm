// https://swexpertacademy.com/main/talk/solvingClub/problemView.do?contestProbId=AV2XbCBaDfUBBASl&solveclubId=AZwrPjFqFyDHBIT3&problemBoxTitle=2%EC%A3%BC%EC%B0%A8&problemBoxCnt=6&probBoxId=AZxWf_YKvf3HBIT3

#include <iostream>

// ====================
// 상수 선언
// ====================

#define MAX_N 12
#define MAX_CORE 12
#define INF 0x3f3f3f3f

constexpr int dy[] = { -1, 1, 0, 0 };
constexpr int dx[] = { 0, 0, -1, 1 };

// ====================
// 구조체 선언
// ====================

struct Core
{
	int y, x;
};

// ====================
// 전역 변수 선언
// ====================

int maxConnectedCore;
int minLineLength;

int gridSize;
int grid[MAX_N][MAX_N];

int coreCount;
Core cores[MAX_CORE];

bool occupiedGrid[MAX_N][MAX_N];

// ====================
// 유틸 함수 구현부
// ====================

inline void Init()
{
	maxConnectedCore = 0;
	minLineLength = INF;
	coreCount = 0;

	for (int i = 0; i < gridSize; ++i)
	{
		for (int j = 0; j < gridSize; ++j)
		{
			occupiedGrid[i][j] = false;
		}
	}
}

inline bool IsBoundary(int y, int x)
{
	return y == 0 || y == gridSize - 1 ||
		   x == 0 || x == gridSize - 1;
}

inline bool IsValid(int y, int x)
{
	return 0 <= y && y < gridSize &&
		   0 <= x && x < gridSize;
}

int TryConnect(const Core& core, int dir)
{
	int length = 0;

	int currY = core.y + dy[dir];
	int currX = core.x + dx[dir];

	while (IsValid(currY, currX))
	{
		if (occupiedGrid[currY][currX]) return 0;

		currY += dy[dir];
		currX += dx[dir];
	}

	currY = core.y + dy[dir];
	currX = core.x + dx[dir];

	while (IsValid(currY, currX))
	{
		occupiedGrid[currY][currX] = true;

		currY += dy[dir];
		currX += dx[dir];

		length++;
	}

	return length;
}

void RemoveLines(const Core& core, int dir)
{
	int currY = core.y + dy[dir];
	int currX = core.x + dx[dir];

	while (IsValid(currY, currX))
	{
		occupiedGrid[currY][currX] = false;

		currY += dy[dir];
		currX += dx[dir];
	}
}

// ====================
// 로직 구현부
// ====================

void DfsLineConnection(int currentCore, int connectedCore, int currentLineLength)
{
	if (currentCore == coreCount)
	{
		if (connectedCore == maxConnectedCore) minLineLength = minLineLength > currentLineLength ? currentLineLength : minLineLength;
		else if (connectedCore > maxConnectedCore)
		{
			maxConnectedCore = connectedCore;
			minLineLength = currentLineLength;
		}

		return;
	}

	if (connectedCore + (coreCount - currentCore) < maxConnectedCore) return;

	for (int d = 0; d < 4; ++d)
	{
		int lineLength = TryConnect(cores[currentCore], d);
		
		if (lineLength > 0)
		{
			DfsLineConnection(currentCore + 1, connectedCore + 1, currentLineLength + lineLength);
			RemoveLines(cores[currentCore], d);
		}
	}

	DfsLineConnection(currentCore + 1, connectedCore, currentLineLength);
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
		Init();

		std::cin >> gridSize;

		for (int i = 0; i < gridSize; ++i)
		{
			for (int j = 0; j < gridSize; ++j)
			{
				std::cin >> grid[i][j];

				if (grid[i][j] == 1)
				{
					occupiedGrid[i][j] = true;

					if (!IsBoundary(i, j))
					{
						Core& core = cores[coreCount++];
						core.y = i;
						core.x = j;
					}
				}
			}
		}

		DfsLineConnection(0, 0, 0);
		std::cout << "#" << tc << " " << minLineLength << "\n";
	}

	return 0;
}