// https://swexpertacademy.com/main/talk/solvingClub/problemView.do?contestProbId=AYH1wsXKpYUDFATO&solveclubId=AZwrPjFqFyDHBIT3&problemBoxTitle=2%EC%A3%BC%EC%B0%A8&problemBoxCnt=6&probBoxId=AZxWf_YKvf3HBIT3

#include <vector>

// ====================
// 상수 선언
// ====================

#define MAX_N 20
#define MAX_STRUCTURE_LEN 5
#define MAX_HASH 9999
#define OFFSET 5
#define MAX_DIR 4

constexpr int dy[] = { -1, 1, 0, 0 };
constexpr int dx[] = { 0, 0, -1, 1 };

// ====================
// 구조체 선언
// ====================

struct Pos
{
	int y, x;
};

struct Candidate
{
	int y, x;
	bool isHorizontal;
	bool isReverse;
};

// ====================
// 전역 변수 선언
// ====================

int mapSize;
int map[MAX_N + 2][MAX_N + 2];
int tempMap[MAX_N + 2][MAX_N + 2];

std::vector<Candidate> candidates[MAX_HASH + 1];

Pos q[(MAX_N + 2) * (MAX_N + 2)];
bool visited[MAX_N + 2][MAX_N + 2];

// ====================
// API Helper
// ====================

inline bool IsSea(int y, int x)
{
	return y == 0 || y == mapSize + 1 ||
		   x == 0 || x == mapSize + 1;
}

inline bool IsValid(int y, int x)
{
	return 1 <= y && y <= mapSize &&
		   1 <= x && x <= mapSize;
}

int GetUnsubmergedArea(int seaLevel)
{
	int submergedArea = 0;

	int head = 0, rear = 0;
	for (int i = 0; i < mapSize + 2; ++i)
	{
		for (int j = 0; j < mapSize + 2; ++j)
		{
			if (IsSea(i, j))
			{
				q[rear++] = { i, j };
				visited[i][j] = true;
			}
			else visited[i][j] = false;
		}
	}

	while (head < rear)
	{
		Pos curr = q[head++];

		for (int dir = 0; dir < MAX_DIR; ++dir)
		{
			int ny = curr.y + dy[dir];
			int nx = curr.x + dx[dir];

			if (IsValid(ny, nx) && !visited[ny][nx] && tempMap[ny][nx] < seaLevel)
			{
				q[rear++] = { ny, nx };
				visited[ny][nx] = true;
				submergedArea++;
			}
		}
	}

	return mapSize * mapSize - submergedArea;
}

// ====================
// API 구현부
// ====================

void init(int N, int mMap[20][20])
{
	mapSize = N;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			map[i + 1][j + 1] = tempMap[i + 1][j + 1] = mMap[i][j];
		}
	}

	for (int hash = 0; hash <= MAX_HASH; ++hash)
	{
		candidates[hash].clear();
	}

	// 가로
	for (int i = 1; i <= N; ++i)
	{
		for (int len = 2; len <= MAX_STRUCTURE_LEN; ++len)
		{
			for (int j = 1; j <= N - len + 1; ++j)
			{
				int hash = 0;
				for (int d = 0; d < len - 1; ++d)
				{
					hash = hash * 10 + (map[i][j + d] - map[i][j + d + 1] + OFFSET);
				}

				candidates[hash].push_back({ i, j, true, false });

				int reverseHash = 0;
				for (int d = len - 2; d >= 0; --d)
				{
					reverseHash = reverseHash * 10 + (map[i][j + d + 1] - map[i][j + d] + OFFSET);
				}

				if(hash != reverseHash) candidates[reverseHash].push_back({ i, j, true, true });
			}
		}
	}

	// 세로
	for (int j = 1; j <= N; ++j)
	{
		for (int len = 2; len <= MAX_STRUCTURE_LEN; ++len)
		{
			for (int i = 1; i <= N - len + 1; ++i)
			{
				int hash = 0;
				for (int d = 0; d < len - 1; ++d)
				{
					hash = hash * 10 + (map[i + d][j] - map[i + d + 1][j] + OFFSET);
				}

				candidates[hash].push_back({ i, j, false, false });

				int reverseHash = 0;
				for (int d = len - 2; d >= 0; --d)
				{
					reverseHash = reverseHash * 10 + (map[i + d + 1][j] - map[i + d][j] + OFFSET);
				}

				if (hash != reverseHash) candidates[reverseHash].push_back({ i, j, false, true });
			}
		}
	}
}

int numberOfCandidate(int M, int mStructure[5])
{
	if (M == 1) return mapSize * mapSize;

	int hash = 0;
	for (int d = 0; d < M - 1; ++d)
	{
		hash = hash * 10 + (mStructure[d + 1] - mStructure[d] + OFFSET);
	}
	
	return (int)candidates[hash].size();
}

int maxArea(int M, int mStructure[5], int mSeaLevel)
{
	int area = -1;

	if (M == 1)
	{
		for (int i = 1; i <= mapSize; ++i)
		{
			for(int j = 1; j <= mapSize; ++j)
			{ 
				tempMap[i][j] = map[i][j] + mStructure[0];
				
				int unSubmergedArea = GetUnsubmergedArea(mSeaLevel);
				area = area > unSubmergedArea ? area : unSubmergedArea;

				tempMap[i][j] = map[i][j];
			}
		}
		
		return area;
	}

	int hash = 0;
	for (int d = 0; d < M - 1; ++d)
	{
		hash = hash * 10 + (mStructure[d + 1] - mStructure[d] + OFFSET);
	}

	for (const Candidate& candidate : candidates[hash])
	{
		if (candidate.isHorizontal)
		{
			int height = candidate.isReverse ?
				map[candidate.y][candidate.x + M - 1] + mStructure[0] :
				map[candidate.y][candidate.x] + mStructure[0];

			for (int d = 0; d < M; ++d)
			{
				tempMap[candidate.y][candidate.x + d] = height;
			}

			int unSubmergedArea = GetUnsubmergedArea(mSeaLevel);
			area = area > unSubmergedArea ? area : unSubmergedArea;

			for (int d = 0; d < M; ++d)
			{
				tempMap[candidate.y][candidate.x + d] = map[candidate.y][candidate.x + d];
			}
		}
		else
		{
			int height = candidate.isReverse ?
				map[candidate.y + M - 1][candidate.x] + mStructure[0] :
				map[candidate.y][candidate.x] + mStructure[0];

			for (int d = 0; d < M; ++d)
			{
				tempMap[candidate.y + d][candidate.x] = height;
			}

			int unSubmergedArea = GetUnsubmergedArea(mSeaLevel);
			area = area > unSubmergedArea ? area : unSubmergedArea;

			for (int d = 0; d < M; ++d)
			{
				tempMap[candidate.y + d][candidate.x] = map[candidate.y + d][candidate.x];
			}
		}
	}
	
	return area;
}
