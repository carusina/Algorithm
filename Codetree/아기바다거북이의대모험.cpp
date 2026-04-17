// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/a-little-sea-turtles-big-adventure/description

#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

void SpreadFever(int id);
void EruptVolcano(int id);

// ====================
// 구조체 선언
// ====================

struct Pos
{
	int y, x;

	bool operator==(const Pos& other) const
	{
		return y == other.y && x == other.x;
	}
};

struct Turtle
{
	int id;
	Pos pos;
	bool isDead;
	int escapedTime;
};

struct Volcano
{
	Pos pos;
	int maxThreshold;
	int currentPressure;
};

struct BfsItem
{
	Pos pos;
	int startDir;
};

// ====================
// 상수 선언
// ====================

#define MAX_TURN 100
#define MAX_N 20
#define MAX_TURTLE 10
#define MAX_VOLCANO 10
#define INCREASE_AMOUNT 10
#define DANGER_FEVER_AMOUNT 20
#define TURTLE 2
#define CORAL 1

constexpr int dy[] = { 0, 1, 0, -1 }; // 우 하 좌 상
constexpr int dx[] = { 1, 0, -1, 0 };

// ====================
// 전역 변수
// ====================

int N;
Pos escapedPos;
int currentTurn;

int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

int volcanoGrid[MAX_N][MAX_N];
int feverGrid[MAX_N][MAX_N];

int turtleCount;
Turtle turtles[MAX_TURTLE + 1];

int volcanoCount;
Volcano volcanos[MAX_VOLCANO + 1];
bool isErupted[MAX_VOLCANO + 1];

// ====================
// 유틸 함수
// ====================

inline bool IsValid(int y, int x)
{
	return 0 <= y && y < N &&
		   0 <= x && x < N;
}

// ====================
// 바다거북 이동
// ====================

int CanEscapedTurtleDir(const Turtle& turtle)
{
	std::memset(visited, false, sizeof(visited));

	std::queue<BfsItem> q;
	visited[turtle.pos.y][turtle.pos.x] = true;

	for (int d = 0; d < 4; ++d)
	{
		int ny = turtle.pos.y + dy[d];
		int nx = turtle.pos.x + dx[d];

		if (IsValid(ny, nx) && !visited[ny][nx] && grid[ny][nx] == 0)
		{
			q.push({ ny, nx, d });
			visited[ny][nx] = true;
		}
	}

	while (!q.empty())
	{
		BfsItem curr = q.front();
		q.pop();

		if (curr.pos == escapedPos)
		{
			return curr.startDir;
		}

		for (int d = 0; d < 4; ++d)
		{
			int ny = curr.pos.y + dy[d];
			int nx = curr.pos.x + dx[d];

			if (IsValid(ny, nx) && !visited[ny][nx] && grid[ny][nx] == 0)
			{
				q.push({ ny, nx, curr.startDir });
				visited[ny][nx] = true;
			}
		}
	}

	return -1;
}

bool MoveTurtle(int id)
{
	Turtle& turtle = turtles[id];
	if (turtle.isDead || turtle.escapedTime != -1) return false;

	int dir = CanEscapedTurtleDir(turtle);
	if (dir == -1) return false;

	grid[turtle.pos.y][turtle.pos.x] = 0;

	turtle.pos.y += dy[dir];
	turtle.pos.x += dx[dir];

	if (turtle.pos == escapedPos)
	{
		turtle.escapedTime = currentTurn;
	}
	else
	{
		grid[turtle.pos.y][turtle.pos.x] = TURTLE;
	}
	
	return true;
}

int MoveTurtles()
{
	int movedCount = 0;

	for (int i = 1; i <= turtleCount; ++i)
	{
		if (MoveTurtle(i))
		{
			movedCount++;
		}
	}

	return movedCount;
}

// ====================
// 화산 압력 증가
// ====================

void IncreaseVolcanoFever()
{
	for (int i = 1; i <= volcanoCount; ++i)
	{
		volcanos[i].currentPressure += INCREASE_AMOUNT;
	}
}

// ====================
// 화산 분출 및 연쇄 반응
// ====================

void SpreadFever(int id)
{
	Volcano& volcano = volcanos[id];
	feverGrid[volcano.pos.y][volcano.pos.x] += volcano.maxThreshold;
	
	std::vector<int> volcanoIds;
	for (int d = 0; d < 4; ++d)
	{
		int cnt = 1;
		while (cnt)
		{
			int ny = volcano.pos.y + dy[d] * cnt;
			int nx = volcano.pos.x + dx[d] * cnt;
			int nFever = volcano.maxThreshold >> cnt;

			if (!IsValid(ny, nx) || grid[ny][nx] == CORAL || nFever == 0) break;
			if (volcanoGrid[ny][nx] != 0) volcanoIds.push_back(volcanoGrid[ny][nx]);

			feverGrid[ny][nx] += nFever;

			cnt++;
		}
	}

	for (int id : volcanoIds)
	{
		EruptVolcano(id);
	}
}

void EruptVolcano(int id)
{
	Volcano& volcano = volcanos[id];
	int feverValue = volcano.currentPressure + feverGrid[volcano.pos.y][volcano.pos.x];

	if (!isErupted[id] && feverValue >= volcano.maxThreshold)
	{
		isErupted[id] = true;
		volcano.currentPressure = 0;

		SpreadFever(id);
	}
}

void EruptVolcanos()
{
	for (int i = 1; i <= volcanoCount; ++i)
	{
		EruptVolcano(i);
	}

	for (int i = 1; i <= turtleCount; ++i)
	{
		Turtle& turtle = turtles[i];

		if (!turtle.isDead && turtle.escapedTime == -1)
		{
			if (feverGrid[turtle.pos.y][turtle.pos.x] >= DANGER_FEVER_AMOUNT)
			{
				turtle.isDead = true;
			}
		}
	}

	for (int i = 1; i <= volcanoCount; ++i)
	{
		if (isErupted[i])
		{
			isErupted[i] = false;
		}
	}

	std::memset(feverGrid, 0, sizeof(feverGrid));
}

// ====================
// main 함수
// ====================

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N >> turtleCount >> volcanoCount;
	escapedPos = { N - 1, N - 1 };

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cin >> grid[i][j];
		}
	}

	for (int i = 1; i <= turtleCount; ++i)
	{
		Turtle& turtle = turtles[i];

		turtle.id = i;
		std::cin >> turtle.pos.y >> turtle.pos.x;
		turtle.isDead = false;
		turtle.escapedTime = -1;

		grid[turtle.pos.y][turtle.pos.x] = TURTLE;
	}

	for (int i = 1; i <= volcanoCount; ++i)
	{
		Volcano& volcano = volcanos[i];

		std::cin >> volcano.pos.y >> volcano.pos.x >> volcano.maxThreshold;
		volcano.currentPressure = 0;

		volcanoGrid[volcano.pos.y][volcano.pos.x] = i;
	}

	currentTurn = 1;
	while (currentTurn <= 100)
	{
		int movedCount = MoveTurtles();
		if (movedCount == 0) break;

		IncreaseVolcanoFever();
		EruptVolcanos();

		currentTurn++;
	}

	for (int i = 1; i <= turtleCount; ++i)
	{
		std::cout << turtles[i].escapedTime << "\n";
	}

	return 0;
}