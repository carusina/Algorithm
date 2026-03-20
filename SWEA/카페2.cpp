#define MAX_ORDERS 20000
#define DUMMY_START 20000
#define MAX_BEBERAGES 10
#define HASH_SIZE 40009

#include <cstring>

struct RESULT
{
	int cnt;
	int IDs[5];
};

enum OrderStatus {
	ACTIVE,
	DONE,
	CANCELLED,
};

struct Order {
	int ID;
	OrderStatus status;
	int remainingCount;
	int assignedBeverages[MAX_BEBERAGES + 1];
	int neededBeverages[MAX_BEBERAGES + 1];
	int bucketPrev, bucketNext;
};

int beverageTypeCount;
int totalOrderCount;
int activeOrderCount;
int firstActiveOrder;

Order orders[MAX_ORDERS + 11];

int waitQueue[MAX_BEBERAGES + 1][MAX_ORDERS];
int waitQueueHead[MAX_BEBERAGES + 1];
int waitQueueTail[MAX_BEBERAGES + 1];

int hashKey[HASH_SIZE];
int hashValue[HASH_SIZE];
bool hashUsed[HASH_SIZE];

// ====================
// API Helper
// ====================

void hashClear()
{
	std::memset(hashUsed, false, sizeof(hashUsed));
}

int hashFind(int ID)
{
	int h = ID % HASH_SIZE;

	while (hashUsed[h] && hashKey[h] != ID)
	{
		h = (h + 1) % HASH_SIZE;
	}

	return h;
}

void hashInsert(int ID, int idx)
{
	int h = hashFind(ID);

	hashKey[h] = ID;
	hashValue[h] = idx;
	hashUsed[h] = true;
}

int hashGet(int id)
{
	int h = hashFind(id);

	return hashUsed[h] ? hashValue[h] : -1;
}

void queuePush(int beverage, int idx)
{
	waitQueue[beverage][waitQueueTail[beverage]++] = idx;
}

int queuePop(int beverage)
{
	int& head = waitQueueHead[beverage];
	int& tail = waitQueueTail[beverage];

	while (head < tail)
	{
		int idx = waitQueue[beverage][head];

		Order& o = orders[idx];
		if (o.status == ACTIVE && o.neededBeverages[beverage] > 0)
		{
			return idx;
		}

		head++;
	}

	return -1;
}

void bucketInsertOrdered(int bucketHead, int idx)
{
	int cur = orders[bucketHead].bucketPrev;
	while (cur != bucketHead && cur > idx)
	{
		cur = orders[cur].bucketPrev;
	}

	int next = orders[cur].bucketNext;
	orders[cur].bucketNext = idx;
	orders[next].bucketPrev = idx;
	orders[idx].bucketPrev = cur;
	orders[idx].bucketNext = next;
}

void bucketRemove(int idx)
{
	orders[orders[idx].bucketPrev].bucketNext = orders[idx].bucketNext;
	orders[orders[idx].bucketNext].bucketPrev = orders[idx].bucketPrev;
}

// ====================
// API 구현부
// ====================

void init(int N)
{
	beverageTypeCount = N;
	totalOrderCount = 0;
	activeOrderCount = 0;
	firstActiveOrder = 0;

	for (int b = 1; b <= N; ++b)
	{
		waitQueueHead[b] = 0;
		waitQueueTail[b] = 0;
	}

	for (int k = 1; k <= 10; ++k)
	{
		Order& o = orders[DUMMY_START + k];
		o.bucketPrev = DUMMY_START + k;
		o.bucketNext = DUMMY_START + k;
	}

	hashClear();

	return;
}

int order(int mID, int M, int mBeverages[])
{
	int idx = totalOrderCount++;
	Order& o = orders[idx];

	o.ID = mID;
	o.status = ACTIVE;
	o.remainingCount = M;
	std::memset(o.assignedBeverages, 0, sizeof(o.assignedBeverages));
	std::memset(o.neededBeverages, 0, sizeof(o.neededBeverages));

	int head = DUMMY_START + M;
	int tail = orders[head].bucketPrev;
	orders[tail].bucketNext = idx;
	orders[head].bucketPrev = idx;
	o.bucketPrev = tail;
	o.bucketNext = head;

	for (int i = 0; i < M; ++i)
	{
		int beverage = mBeverages[i];
		o.neededBeverages[beverage]++;
		queuePush(beverage, idx);
	}

	hashInsert(mID, idx);
	activeOrderCount++;

	return activeOrderCount;
}

int supply(int mBeverage)
{
	int idx = queuePop(mBeverage);
	if (idx == -1)
	{
		return -1;
	}

	waitQueueHead[mBeverage]++;

	Order& o = orders[idx];
	o.neededBeverages[mBeverage]--;
	o.assignedBeverages[mBeverage]++;

	bucketRemove(idx);

	o.remainingCount--;

	if (o.remainingCount == 0)
	{
		o.status = DONE;
		activeOrderCount--;
	}
	else
	{
		bucketInsertOrdered(DUMMY_START + o.remainingCount, idx);
	}

	return o.ID;
}

int cancel(int mID)
{
	int idx = hashGet(mID);
	if (idx == -1)
	{
		return -1;
	}

	Order& o = orders[idx];
	if (o.status == DONE)
	{
		return 0;
	}
	else if (o.status == CANCELLED)
	{
		return -1;
	}

	int remainingBeforeCancle = o.remainingCount;
	bucketRemove(idx);

	o.status = CANCELLED;
	activeOrderCount--;

	for (int beverage = 1; beverage <= beverageTypeCount; ++beverage)
	{
		int assignedCount = o.assignedBeverages[beverage];

		for (int i = 0; i < assignedCount; ++i)
		{
			int targetIdx = queuePop(beverage);
			if (targetIdx == -1)
			{
				continue;
			}

			waitQueueHead[beverage]++;

			Order& target = orders[targetIdx];
			target.neededBeverages[beverage]--;
			target.assignedBeverages[beverage]++;

			bucketRemove(targetIdx);

			target.remainingCount--;

			if (target.remainingCount == 0)
			{
				target.status = DONE;
				activeOrderCount--;
			}
			else
			{
				bucketInsertOrdered(DUMMY_START + target.remainingCount, targetIdx);
			}
		}
	}

	return remainingBeforeCancle;
}

int getStatus(int mID)
{
	int idx = hashGet(mID);
	if (idx == -1)
	{
		return -1;
	}

	Order& o = orders[idx];
	if (o.status == DONE)
	{
		return 0;
	}
	else if (o.status == CANCELLED)
	{
		return -1;
	}

	return o.remainingCount;
}

RESULT hurry()
{
	RESULT res;
	res.cnt = 0;

	for (int k = MAX_BEBERAGES; k >= 1 && res.cnt < 5; --k)
	{
		int head = DUMMY_START + k;
		int curr = orders[head].bucketNext;

		while (curr != head && res.cnt < 5)
		{
			res.IDs[res.cnt++] = orders[curr].ID;
			curr = orders[curr].bucketNext;
		}
	}

	return res;
}
