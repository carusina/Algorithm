#define MAP_SIZE_MAX 350
#define INF 0x3f3f3f3f
#define MAX_GATES 200
#define GATE_OFFSET 1

#include <queue>
#include <cstring>

// ====================
// 구조체 선언
// ====================

struct Pos {
	int row, col;
	int dist;
};

struct Gate {
	int row, col;
	bool activate;
};

struct Edge {
	int to;
	int dist;

	const bool operator<(const Edge& other) const {
		return dist > other.dist;
	}
};

// ====================
// 전역 변수
// ====================

constexpr int dy[] = { -1, 1, 0, 0 };
constexpr int dx[] = { 0, 0, -1 , 1 };

int mapSize;
int map[MAP_SIZE_MAX][MAP_SIZE_MAX];

int maxStamina;

int currentStamp;
int visitedStamp[MAP_SIZE_MAX][MAP_SIZE_MAX];

int gateCount;
Gate gates[MAX_GATES + 1];
int gateDist[MAX_GATES + 1][MAX_GATES + 1];

Pos q[MAP_SIZE_MAX * MAP_SIZE_MAX + 1];

// ====================
// API Helper
// ====================

inline bool IsValid(int row, int col) {
	return 0 <= row && row < mapSize &&
		0 <= col && col < mapSize;
}

inline bool IsGate(int row, int col) {
	return 2 <= map[row][col] && map[row][col] <= MAX_GATES;
}

void GetGateDist(int mGateID) {
	currentStamp++;

	for (int i = 1; i <= mGateID; ++i)
	{
		gateDist[mGateID][i] = INF;
		gateDist[i][mGateID] = INF;
	}

	Gate& gate = gates[mGateID];

	int head = 0;
	int tail = 0;

	q[tail++] = { gate.row, gate.col, 0 };
	gateDist[mGateID][mGateID] = 0;
	visitedStamp[gate.row][gate.col] = currentStamp;

	while (head < tail)
	{
		Pos curr = q[head++];

		if (IsGate(curr.row, curr.col))
		{
			int currGateID = map[curr.row][curr.col] - GATE_OFFSET;

			if (gates[currGateID].activate)
			{
				gateDist[mGateID][currGateID] = curr.dist;
				gateDist[currGateID][mGateID] = curr.dist;
			}
		}

		for (int d = 0; d < 4; ++d)
		{
			int nRow = curr.row + dy[d];
			int nCol = curr.col + dx[d];
			int nDist = curr.dist + 1;

			if (IsValid(nRow, nCol) && visitedStamp[nRow][nCol] != currentStamp && map[nRow][nCol] != 1)
			{
				if (nDist <= maxStamina)
				{
					q[tail++] = { nRow, nCol, nDist };
					visitedStamp[nRow][nCol] = currentStamp;
				}
			}
		}
	}
}

// ====================
// API 구현부
// ====================

void init(int N, int mMaxStamina, int mMap[MAP_SIZE_MAX][MAP_SIZE_MAX])
{
	mapSize = N;

	for (int r = 0; r < mapSize; ++r)
	{
		for (int c = 0; c < mapSize; ++c)
		{
			map[r][c] = mMap[r][c];
		}
	}

	maxStamina = mMaxStamina;

	currentStamp = 0;
	std::memset(visitedStamp, currentStamp, sizeof(visitedStamp));

	gateCount = 1;

	return;
}

void addGate(int mGateID, int mRow, int mCol)
{
	map[mRow][mCol] = mGateID + GATE_OFFSET;
	gates[gateCount++] = { mRow, mCol, true };

	GetGateDist(mGateID);

	return;
}

void removeGate(int mGateID)
{
	Gate& gate = gates[mGateID];

	map[gate.row][gate.col] = 0;
	gate.activate = false;

	return;
}

int getMinTime(int mStartGateID, int mEndGateID)
{
	int dist[MAX_GATES + 1];
	for (int i = 1; i < gateCount; ++i)
	{
		dist[i] = INF;
	}

	std::priority_queue<Edge> pq;
	pq.push({ mStartGateID, 0 });
	dist[mStartGateID] = 0;

	while (!pq.empty())
	{
		Edge curr = pq.top();
		pq.pop();

		if (curr.dist > dist[curr.to])
		{
			continue;
		}

		if (curr.to == mEndGateID)
		{
			return curr.dist;
		}

		for (int gateID = 1; gateID < gateCount; ++gateID)
		{
			Gate& gate = gates[gateID];

			if (gate.activate && gateDist[curr.to][gateID] != INF)
			{
				int nextDist = curr.dist + gateDist[curr.to][gateID];

				if (nextDist < dist[gateID])
				{
					pq.push({ gateID, nextDist });
					dist[gateID] = nextDist;
				}
			}
		}
	}

	return -1;
}