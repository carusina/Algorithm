// https://swexpertacademy.com/main/talk/solvingClub/problemView.do?contestProbId=AYH1wsXKpYUDFATO&solveclubId=AZwrPjFqFyDHBIT3&problemBoxTitle=2%EC%A3%BC%EC%B0%A8&problemBoxCnt=6&probBoxId=AZxWf_YKvf3HBIT3

#include <vector>

// ====================
// 상수 선언
// ====================

#define MAX_N 20
#define MAX_HEIGHT 5
#define MAX_STRUCTURE_LEN 5
#define MAX_HASH 9999
#define OFFSET 5

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

inline bool IsValid(int y, int x)
{
	return 1 <= y && y <= mapSize &&
		   1 <= x && x <= mapSize;
}

int GetUnsubmergedArea(int mMap[MAX_N + 2][MAX_N + 2], int mSeaLevel)
{
	int submergedArea = 0;
	
	int head = 0, rear = 0;
	for (int i = 0; i <= mapSize + 1; ++i)
	{
		for (int j = 0; j <= mapSize + 1; ++j)
		{
			if (i == 0 || i == mapSize + 1 || j == 0 || j == mapSize + 1)
			{
				visited[i][j] = true;
				q[rear++] = { i, j };
			}
			else visited[i][j] = false;
		}
	}

	while (head < rear)
	{
		Pos curr = q[head++];

		for (int d = 0; d < 4; ++d)
		{
			int ny = curr.y + dy[d];
			int nx = curr.x + dx[d];

			if (IsValid(ny, nx) && !visited[ny][nx] && mMap[ny][nx] < mSeaLevel)
			{
				++submergedArea;
				visited[ny][nx] = true;
				q[rear++] = { ny, nx };
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
			tempMap[i + 1][j + 1] = map[i + 1][j + 1] = mMap[i][j];
		}
	}

	for (int i = 0; i <= MAX_HASH; ++i)
	{
		candidates[i].clear();
	}

	for (int len = 2; len <= MAX_STRUCTURE_LEN; ++len)
	{
		// 가로
		for (int sy = 1; sy <= N; ++sy)
		{
			for (int sx = 1; sx <= N - len + 1; ++sx)
			{
				int hash = 0;
				for (int d = 1; d < len; ++d)
				{
					hash = hash * 10 + (map[sy][sx + d] - map[sy][sx + d - 1] + OFFSET);
				}

				candidates[hash].push_back({ sy, sx, true, false });

				int reverseHash = 0;
				for (int d = len - 1; d >= 1; --d)
				{
					reverseHash = reverseHash * 10 + (map[sy][sx + d - 1] - map[sy][sx + d] + OFFSET);
				}

				if (reverseHash != hash) candidates[reverseHash].push_back({ sy, sx, true, true });
			}
		}

		// 세로
		for (int sx = 1; sx <= N; ++sx)
		{
			for (int sy = 1; sy <= N - len + 1; ++sy)
			{
				int hash = 0;
				for (int d = 1; d < len; ++d)
				{
					hash = hash * 10 + (map[sy + d][sx] - map[sy + d - 1][sx] + OFFSET);
				}

				candidates[hash].push_back({ sy, sx, false, false });

				int reverseHash = 0;
				for (int d = len - 1; d >= 1; --d)
				{
					reverseHash = reverseHash * 10 + (map[sy + d - 1][sx] - map[sy + d][sx] + OFFSET);
				}

				if (reverseHash != hash) candidates[reverseHash].push_back({ sy, sx, false, true });
			}
		}
	}
}

int numberOfCandidate(int M, int mStructure[5])
{
	if (M == 1) return mapSize * mapSize;

	int hash = 0;
	for (int d = 1; d < M; ++d)
	{
		hash = hash * 10 + (mStructure[d - 1] - mStructure[d] + OFFSET);
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
			for (int j = 1; j <= mapSize; ++j)
			{
				tempMap[i][j] = map[i][j] + mStructure[0];

				int unsubmergedArea = GetUnsubmergedArea(tempMap, mSeaLevel);
				area = area > unsubmergedArea ? area : unsubmergedArea;

				tempMap[i][j] = map[i][j];
			}
		}

		return area;
	}

	int hash = 0;
	for (int d = 1; d < M; ++d)
	{
		hash = hash * 10 + (mStructure[d - 1] - mStructure[d] + OFFSET);
	}

	for (const Candidate& candidate : candidates[hash])
	{
		if (candidate.isHorizontal)
		{
			int height = mStructure[0] + (candidate.isReverse ? map[candidate.y][candidate.x + M - 1] : map[candidate.y][candidate.x]);

			for (int d = 0; d < M; ++d)
			{
				tempMap[candidate.y][candidate.x + d] = height;
			}

			int unsubmergedArea = GetUnsubmergedArea(tempMap, mSeaLevel);
			area = area > unsubmergedArea ? area : unsubmergedArea;

			for (int d = 0; d < M; ++d)
			{
				tempMap[candidate.y][candidate.x + d] = map[candidate.y][candidate.x + d];
			}
		}
		else
		{
			int height = mStructure[0] + (candidate.isReverse ? map[candidate.y + M - 1][candidate.x] : map[candidate.y][candidate.x]);

			for (int d = 0; d < M; ++d)
			{
				tempMap[candidate.y + d][candidate.x] = height;
			}

			int unsubmergedArea = GetUnsubmergedArea(tempMap, mSeaLevel);
			area = area > unsubmergedArea ? area : unsubmergedArea;

			for (int d = 0; d < M; ++d)
			{
				tempMap[candidate.y + d][candidate.x] = map[candidate.y + d][candidate.x];
			}
		}
	}

	return area;
}
