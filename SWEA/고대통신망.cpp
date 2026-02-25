#define MAX_N 5005
#define MAX_EDGES 30005
#define HASH_SIZE 40009
#define MAX_HEAP 500000
#define INF 0x3f3f3f3f

struct Edge
{
	int from, to, dist;
	int prev, next;
};

Edge edgePool[MAX_EDGES];
int edgeCnt;
int head[MAX_N];

struct HashNode
{
	int id, edge_idx, next;
};

HashNode hashPool[MAX_EDGES];
int hashCnt;
int hashTable[HASH_SIZE];

int getEdgeIdx(int id)
{
	int h = id % HASH_SIZE;
	for (int i = hashTable[h]; i != -1; i = hashPool[i].next)
	{
		if (hashPool[i].id == id) return hashPool[i].edge_idx;
	}
	return -1;
}

void addHash(int id, int e_idx)
{
	int h = id % HASH_SIZE;
	hashPool[hashCnt] = { id, e_idx, hashTable[h] };
	hashTable[h] = hashCnt++;
}

struct PQNode
{
	int dist, max_edge, u;
	bool is_less(const PQNode& o) const
	{
		if (dist != o.dist) return dist < o.dist;
		return max_edge < o.max_edge;
	}
};

PQNode heap[MAX_HEAP];
int heapSz;

void pushPQ(int d, int m, int u)
{
	heap[++heapSz] = { d, m, u };
	int c = heapSz;
	while (c > 1)
	{
		int p = c / 2;
		if (heap[c].is_less(heap[p]))
		{
			PQNode t = heap[p];
			heap[p] = heap[c];
			heap[c] = t;
			c = p;
		}
		else
		{
			break;
		}
	}
}

PQNode popPQ()
{
	PQNode ret = heap[1];
	heap[1] = heap[heapSz--];
	int p = 1;
	while (p * 2 <= heapSz)
	{
		int c = p * 2;
		if (c + 1 <= heapSz && heap[c + 1].is_less(heap[c]))
		{
			c++;
		}

		if (heap[c].is_less(heap[p]))
		{
			PQNode t = heap[p];
			heap[p] = heap[c];
			heap[c] = t;
			p = c;
		}
		else
		{
			break;
		}
	}
	return ret;
}

int minDist[MAX_N];
int minMaxEdge[MAX_N];
bool needsFullDijkstra;
int capitalCity, numCities;

void addEdge(int id, int from, int to, int dist)
{
	int e = edgeCnt++;
	edgePool[e] = { from, to, dist, -1, head[from] };

	if (head[from] != -1)
	{
		edgePool[head[from]].prev = e;
	}

	head[from] = e;
	addHash(id, e);
}

void resumeDijkstra()
{
	while (heapSz > 0)
	{
		PQNode curr = popPQ();
		int u = curr.u;

		if (curr.dist > minDist[u])
		{
			continue;
		}
		if (curr.dist == minDist[u] && curr.max_edge > minMaxEdge[u])
		{
			continue;
		}

		for (int e = head[u]; e != -1; e = edgePool[e].next)
		{
			int v = edgePool[e].to;
			int d = edgePool[e].dist;

			int next_dist = curr.dist + d;
			int next_max = (curr.max_edge > d) ? curr.max_edge : d;

			if (next_dist < minDist[v] || (next_dist == minDist[v] && next_max < minMaxEdge[v]))
			{
				minDist[v] = next_dist;
				minMaxEdge[v] = next_max;
				pushPQ(next_dist, next_max, v);
			}
		}
	}
}

void runFullDijkstra()
{
	for (int i = 0; i < numCities; ++i)
	{
		minDist[i] = INF;
		minMaxEdge[i] = INF;
	}

	heapSz = 0;
	minDist[capitalCity] = 0;
	minMaxEdge[capitalCity] = 0;
	pushPQ(0, 0, capitalCity);

	resumeDijkstra();
	needsFullDijkstra = false;
}

void init(int N, int mCapital, int K, int mId[], int sCity[], int eCity[], int mDistance[]) {
	numCities = N;
	capitalCity = mCapital;
	edgeCnt = 0;
	hashCnt = 0;

	for (int i = 0; i < N; ++i)
	{
		head[i] = -1;
	}

	for (int i = 0; i < HASH_SIZE; ++i)
	{
		hashTable[i] = -1;
	}

	for (int i = 0; i < K; ++i)
	{
		addEdge(mId[i], sCity[i], eCity[i], mDistance[i]);
	}

	needsFullDijkstra = true;
}

void add(int mId, int sCity, int eCity, int mDistance) {
	addEdge(mId, sCity, eCity, mDistance);

	if (!needsFullDijkstra && minDist[sCity] != INF)
	{
		int next_dist = minDist[sCity] + mDistance;
		int next_max = (minMaxEdge[sCity] > mDistance) ? minMaxEdge[sCity] : mDistance;

		if (next_dist < minDist[eCity] || (next_dist == minDist[eCity] && next_max < minMaxEdge[eCity]))
		{
			minDist[eCity] = next_dist;
			minMaxEdge[eCity] = next_max;
			pushPQ(next_dist, next_max, eCity);
			resumeDijkstra();
		}
	}
}

void remove(int mId) {
	int e = getEdgeIdx(mId);
	if (e == -1)
	{
		return;
	}

	int u = edgePool[e].from;
	int v = edgePool[e].to;
	int d = edgePool[e].dist;

	if (!needsFullDijkstra && minDist[u] != INF)
	{
		int next_max = (minMaxEdge[u] > d) ? minMaxEdge[u] : d;
		if (minDist[u] + d == minDist[v] && next_max == minMaxEdge[v])
		{
			needsFullDijkstra = true;
		}
	}

	int p = edgePool[e].prev;
	int n = edgePool[e].next;
	if (p != -1)
	{
		edgePool[p].next = n;
	}
	else
	{
		head[u] = n;
	}

	if (n != -1)
	{
		edgePool[n].prev = p;
	}
}

int calculate(int mCity) {
	if (needsFullDijkstra)
	{
		runFullDijkstra();
	}

	return (minMaxEdge[mCity] == INF) ? -1 : minMaxEdge[mCity];
}
