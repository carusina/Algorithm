// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/microbial-research/description

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cstring>

// ====================
// 구조체 선언
// ====================

struct Pos
{
	int y, x;
};

struct MicroGroup
{
	int id;
	int size;
	std::vector<Pos> cells;

	bool operator<(const MicroGroup& other) const
	{
		if (size != other.size)
		{
			return size < other.size;
		}

		return id > other.id;
	}
};

struct MicroGroupComparator
{
	bool operator()(const MicroGroup* a, const MicroGroup* b)
	{
		return *a < *b;
	}
};

// ====================
// 상수 선언
// ====================

#define MAX_N 15
#define MAX_Q 50
#define INF 0x3f3f3f3f

constexpr int dy[] = { -1, 1, 0, 0 };
constexpr int dx[] = { 0, 0, -1, 1 };

// ====================
// 전역 변수 선언
// ====================

int N, maxQ, currQ;
int grid[MAX_N + 1][MAX_N + 1];
int tempGrid[MAX_N + 1][MAX_N + 1];
bool visited[MAX_N + 1][MAX_N + 1];

MicroGroup microGroups[MAX_Q + 1];

// ====================
// 유틸 함수
// ====================

inline bool IsValid(int y, int x)
{
	return 0 <= y && y < N &&
		   0 <= x && x < N;
}

// ====================
// 미생물 투입
// ====================

bool IsSeparated(int microId)
{
	const std::vector<Pos>& oldCells = microGroups[microId].cells;
	
	int currentCellCount = 0;
	Pos start = { -1, -1 };

	for (const Pos& cell : oldCells)
	{
		if (grid[cell.y][cell.x] == microId)
		{
			currentCellCount++;

			if (start.y == -1)
			{
				start = cell;
			}
		}
	}

	if (currentCellCount == 0)
	{
		return false;
	}

	int bfsCount = 0;
	std::queue<Pos> q;
	std::memset(visited, false, sizeof(visited));

	q.push(start);
	visited[start.y][start.x] = true;
	bfsCount++;

	while (!q.empty())
	{
		Pos curr = q.front();
		q.pop();

		for (int d = 0; d < 4; ++d)
		{
			int ny = curr.y + dy[d];
			int nx = curr.x + dx[d];

			if (IsValid(ny, nx) && !visited[ny][nx] && grid[ny][nx] == microId)
			{
				q.push({ ny, nx });
				visited[ny][nx] = true;
				bfsCount++;
			}
		}
	}

	return bfsCount != currentCellCount;
}

void InsertMicro(int r1, int c1, int r2, int c2)
{
	MicroGroup& currMicroGroup = microGroups[currQ];
	currMicroGroup.id = currQ;
	currMicroGroup.size = (r2 - r1) * (c2 - c1);
	currMicroGroup.cells.clear();

	std::vector<int> deadMicros(currQ, 0);

	for (int r = r1; r < r2; ++r)
	{
		for (int c = c1; c < c2; ++c)
		{
			if (grid[r][c] != 0)
			{
				deadMicros[grid[r][c]]++;
			}

			grid[r][c] = currQ;
			currMicroGroup.cells.push_back({ r, c });
		}
	}

	for (int i = 1; i < currQ; ++i)
	{
		if (deadMicros[i] > 0)
		{
			if (IsSeparated(i))
			{
				microGroups[i].size = 0;
				microGroups[i].cells.clear();
			}
			else
			{
				microGroups[i].size -= deadMicros[i];

				microGroups[i].cells.clear();
				for (int r = 0; r < N; ++r)
				{
					for (int c = 0; c < N; ++c)
					{
						if (grid[r][c] == i)
						{
							microGroups[i].cells.push_back({ r, c });
						}
					}
				}
			}
		}
	}
}

// ====================
// 배양 용기 이동
// ====================

bool FindEmptySpaceAndRelocate(MicroGroup* curr)
{
	int minR = INF, minC = INF;
	int maxR = -1, maxC = -1;

	for (const Pos& cell : curr->cells)
	{
		minR = std::min(minR, cell.y);
		minC = std::min(minC, cell.x);
		maxR = std::max(maxR, cell.y);
		maxC = std::max(maxC, cell.x);
	}

	int h = maxR - minR + 1;
	int w = maxC - minC + 1;

	std::vector<Pos> relative;
	for (const Pos& cell : curr->cells)
	{
		relative.push_back({ cell.y - minR, cell.x - minC });
	}

	for (int c = 0; c <= N - w; ++c)
	{
		for (int r = 0; r <= N - h; ++r)
		{
			bool isEmptySpace = true;

			for (const Pos& rel : relative)
			{
				if (tempGrid[r + rel.y][c + rel.x] != 0)
				{
					isEmptySpace = false;
					break;
				}
			}

			if (isEmptySpace)
			{
				curr->cells.clear();

				for (const Pos& rel : relative)
				{
					tempGrid[r + rel.y][c + rel.x] = curr->id;
					curr->cells.push_back({ r + rel.y, c + rel.x });
				}

				return true;
			}
		}
	}

	return false;
}

void MoveGrid()
{
	std::memset(tempGrid, 0, sizeof(tempGrid));

	std::priority_queue<MicroGroup*, std::vector<MicroGroup*>, MicroGroupComparator> pq;

	for (int i = 1; i <= currQ; ++i)
	{
		if (microGroups[i].size > 0)
		{
			pq.push(&microGroups[i]);
		}
	}

	while (!pq.empty())
	{
		MicroGroup* curr = pq.top();
		pq.pop();

		if (!FindEmptySpaceAndRelocate(curr))
		{
			curr->size = 0;
		}
	}

	std::memcpy(grid, tempGrid, sizeof(tempGrid));
}

// ====================
// 실험 결과 기록
// ====================

void GetNeighbor(std::set<int>& neighborMicroNum, const MicroGroup* currGroup)
{
	for (const Pos& cell : currGroup->cells)
	{
		for (int d = 0; d < 4; ++d)
		{
			int ny = cell.y + dy[d];
			int nx = cell.x + dx[d];

			if (IsValid(ny, nx) && grid[ny][nx] != currGroup->id && grid[ny][nx] != 0)
			{
				neighborMicroNum.insert(grid[ny][nx]);
			}
		}
	}
}

void PrintResult()
{
	int result = 0;

	for (int i = 1; i <= currQ; ++i)
	{
		std::set<int> neighborMicroNum;

		if (microGroups[i].size > 0)
		{
			GetNeighbor(neighborMicroNum, &microGroups[i]);

			for (int neighbor : neighborMicroNum)
			{
				result += (microGroups[i].size * microGroups[neighbor].size);
			}
		}
	}

	std::cout << result / 2 << "\n";
}

// ====================
// main 함수
// ====================

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N >> maxQ;
	for (currQ = 1; currQ <= maxQ; ++currQ)
	{
		int r1, c1;
		int r2, c2;

		std::cin >> c1 >> r1 >> c2 >> r2;

		InsertMicro(r1, c1, r2, c2);
		MoveGrid();
		PrintResult();
	}

	return 0;
}
