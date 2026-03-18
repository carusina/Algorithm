#define MAP_SIZE_MAX 350

#include <queue>
#include <cstring>

struct Pos {
	int y, x;
	int dist;
};

struct Gate {
	int y, x;
	int activate;
};

struct Edge {
	int to;
	int dist;

	const bool operator<(const Edge& other) const {
		return dist > other.dist;
	}
};

constexpr int INF		      = 0x3f3f3f3f;
constexpr int MAX_GATE    = 201;
constexpr int GATE_OFFSET = 1;
constexpr int dy[]		    = { -1, 1, 0, 0 };
constexpr int dx[]        = { 0, 0, -1 ,1 };

int maxHealth;
int gateCount;
int mapSize;
int map[MAP_SIZE_MAX][MAP_SIZE_MAX];

int currentStamp = 0;
int visitedStamp[MAP_SIZE_MAX][MAP_SIZE_MAX];

Gate gates[MAX_GATE];
int gateDist[MAX_GATE][MAX_GATE];

Pos q[MAP_SIZE_MAX * MAP_SIZE_MAX];

// ====================
// API Helper
// ====================

inline bool IsValid(int y, int x) {
	return 0 <= y && y < mapSize &&
		   0 <= x && x < mapSize;
}

void GetGateDist(int mGateID) {
	currentStamp++;

	for (int i = 1; i <= mGateID; ++i)
	{
		gateDist[mGateID][i] = INF;
		gateDist[i][mGateID] = INF;
	}

	int head = 0;
	int tail = 0;
	q[tail++] = { gates[mGateID].y, gates[mGateID].x, 0 };
	gateDist[mGateID][mGateID] = 0;
	visitedStamp[gates[mGateID].y][gates[mGateID].x] = currentStamp;

	while (head < tail)
	{
		Pos curr = q[head++];

		if (2 <= map[curr.y][curr.x] && map[curr.y][curr.x] <= MAX_GATE)
		{
			int currGate = map[curr.y][curr.x] - GATE_OFFSET;

			if (gates[currGate].activate)
			{
				gateDist[mGateID][currGate] = curr.dist;
				gateDist[currGate][mGateID] = curr.dist;
			}
		}

		for (int d = 0; d < 4; ++d)
		{
			int ny = curr.y + dy[d];
			int nx = curr.x + dx[d];
			int nd = curr.dist + 1;

			if (IsValid(ny, nx) && visitedStamp[ny][nx] != currentStamp && map[ny][nx] != 1)
			{
				if (nd <= maxHealth)
				{
					q[tail++] = { ny, nx, curr.dist + 1 };
					visitedStamp[ny][nx] = currentStamp;
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
	maxHealth = mMaxStamina;
	gateCount = 1;

	currentStamp = 0;
	std::memset(visitedStamp, 0, sizeof(visitedStamp));

	for (int i = 0; i < mapSize; ++i)
	{
		for (int j = 0; j < mapSize; ++j)
		{
			map[i][j] = mMap[i][j];
		}
	}

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
	int gateY = gates[mGateID].y;
	int gateX = gates[mGateID].x;

	map[gateY][gateX] = 0;
	gates[mGateID].activate = false;

	return;
}

int getMinTime(int mStartGateID, int mEndGateID)
{
	int dist[MAX_GATE];
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
			break;
		}

		for (int gate = 1; gate < gateCount; ++gate)
		{
			if (gates[gate].activate && gateDist[curr.to][gate] != INF)
			{
				int nextDist = curr.dist + gateDist[curr.to][gate];

				if (nextDist < dist[gate])
				{
					pq.push({ gate, nextDist });
					dist[gate] = nextDist;
				}
			}
		}
	}

	return dist[mEndGateID] == INF ? -1 : dist[mEndGateID];
}
