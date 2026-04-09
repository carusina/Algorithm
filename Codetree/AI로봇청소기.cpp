// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/ai-robot/description

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>

// ====================
// 구조체 선언
// ====================

struct Pos
{
	int y, x;

	bool operator<(const Pos& other) const
	{
		if (y != other.y)
		{
			return y < other.y;
		}
		return x < other.x;
	}
};

// ====================
// 상수 선언
// ====================

#define MAX_N     30
#define MAX_ROBOT 50
#define MAX_CLEAN_AMOUNT 20
#define ACC_DUST_AMOUNT 5
#define DIVISOR 10

#define UP    3
#define DOWN  1
#define LEFT  2
#define RIGHT 0

constexpr int dy[] = { 0, 1, 0, -1 }; // 우 하 좌 상
constexpr int dx[] = { 1, 0, -1, 0 };
constexpr int cleanDir[][3] = {
	{RIGHT, UP, DOWN},
	{DOWN, LEFT, RIGHT},
	{LEFT, UP, DOWN},
	{UP, LEFT, RIGHT},
};

// ====================
// 전역 변수
// ====================

int N, robotCount, maxTurn;

int grid[MAX_N + 1][MAX_N + 1];
int tempGrid[MAX_N + 1][MAX_N + 1];
bool visited[MAX_N + 1][MAX_N + 1];

Pos robots[MAX_ROBOT + 1];
bool isLocatedRobot[MAX_N + 1][MAX_N + 1];

// ====================
// 유틸 함수
// ====================

inline bool IsValid(int y, int x)
{
	return 1 <= y && y <= N &&
		   1 <= x && x <= N;
}

// ====================
// 청소기 이동
// ====================

void Move(Pos& robot)
{
	std::memset(visited, false, sizeof(visited));

	std::queue<Pos> q;
	std::vector<Pos> movePoses;

	q.push(robot);
	visited[robot.y][robot.x] = true;

	while (!q.empty())
	{
		int qSize = q.size();

		while (qSize--)
		{
			Pos curr = q.front();
			q.pop();

			if (grid[curr.y][curr.x] > 0)
			{
				movePoses.push_back(curr);
			}

			if (!movePoses.empty())
			{
				continue;
			}

			for (int d = 0; d < 4; ++d)
			{
				int ny = curr.y + dy[d];
				int nx = curr.x + dx[d];

				if (IsValid(ny, nx) && !visited[ny][nx] && grid[ny][nx] != -1)
				{
					if (!isLocatedRobot[ny][nx])
					{
						q.push({ ny, nx });
						visited[ny][nx] = true;
					}
				}
			}
		}

		if (!movePoses.empty())
		{
			break;
		}
	}

	if (movePoses.empty()) return;

	std::sort(movePoses.begin(), movePoses.end());

	isLocatedRobot[robot.y][robot.x] = false;
	robot.y = movePoses[0].y;
	robot.x = movePoses[0].x;
	isLocatedRobot[robot.y][robot.x] = true;
}

void MoveRobots()
{
	for (int i = 0; i < robotCount; ++i)
	{
		Move(robots[i]);
	}
}

// ====================
// 청소
// ====================

int FindCleanDir(Pos& robot)
{
	int maxDustDir = 0;
	int maxDustSum = 0;
	for (int d = 0; d < 4; ++d)
	{
		int currDustSum = 0;
		for (int i = 0; i < 3; ++i)
		{
			int cleanY = robot.y + dy[cleanDir[d][i]];
			int cleanX = robot.x + dx[cleanDir[d][i]];

			if (IsValid(cleanY, cleanX) && grid[cleanY][cleanX] > 0)
			{
				currDustSum += std::min(grid[cleanY][cleanX], MAX_CLEAN_AMOUNT);
			}
		}

		if (currDustSum > maxDustSum)
		{
			maxDustDir = d;
			maxDustSum = currDustSum;
		}
	}

	return maxDustDir;
}

void Clean(Pos& robot)
{
	int dir = FindCleanDir(robot);

	grid[robot.y][robot.x] = std::max(grid[robot.y][robot.x] - MAX_CLEAN_AMOUNT, 0);
	for (int i = 0; i < 3; ++i)
	{
		int cleanY = robot.y + dy[cleanDir[dir][i]];
		int cleanX = robot.x + dx[cleanDir[dir][i]];

		if (IsValid(cleanY, cleanX) && grid[cleanY][cleanX] > 0)
		{
			grid[cleanY][cleanX] = std::max(grid[cleanY][cleanX] - MAX_CLEAN_AMOUNT, 0);
		}
	}
}

void CleanRobots()
{
	for (int i = 0; i < robotCount; ++i)
	{
		Clean(robots[i]);
	}
}

// ====================
// 먼지 축적
// ====================

void AccumulatedDust()
{
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			if (grid[i][j] > 0)
			{
				grid[i][j] += ACC_DUST_AMOUNT;
			}
		}
	}
}

// ====================
// 먼지 확산
// ====================

int SumAroundDust(Pos p)
{
	int dustAmount = 0;

	for (int d = 0; d < 4; ++d)
	{
		int ny = p.y + dy[d];
		int nx = p.x + dx[d];

		if (IsValid(ny, nx) && grid[ny][nx] > 0)
		{
			dustAmount += grid[ny][nx];
		}
	}

	return dustAmount;
}

void SpreadDust(int& totalDust)
{
	std::memset(tempGrid, 0, sizeof(tempGrid));

	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			if (grid[i][j] == -1)
			{
				tempGrid[i][j] = -1;
			}
			else if (grid[i][j] == 0)
			{
				tempGrid[i][j] = (SumAroundDust({ i, j }) / DIVISOR);
				totalDust += tempGrid[i][j];
			}
			else
			{
				tempGrid[i][j] = grid[i][j];

				if (grid[i][j] > 0)
				{
					totalDust += grid[i][j];
				}
			}
		}
	}

	std::memcpy(grid, tempGrid, sizeof(tempGrid));
}

// ====================
// main 함수
// ====================

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N >> robotCount >> maxTurn;

	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			std::cin >> grid[i][j];
		}
	}

	for (int i = 0; i < robotCount; ++i)
	{
		std::cin >> robots[i].y >> robots[i].x;
		isLocatedRobot[robots[i].y][robots[i].x] = true;
	}

	int turn = 0;
	while (turn++ < maxTurn)
	{
		int totalDust = 0;

		MoveRobots();
		CleanRobots();
		AccumulatedDust();
		SpreadDust(totalDust);

		std::cout << totalDust << std::endl;
	}

	return 0;
}
