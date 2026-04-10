// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/street-light-installation/description

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

// ====================
// 구조체 선언
// ====================

struct Light
{
	int id;
	int pos;

	Light* prev;
	Light* next;
};

struct PqItem
{
	int leftId;
	int rightId;
	int dist;
	int leftPos;

	bool operator<(const PqItem& other) const
	{
		if (dist != other.dist)
		{
			return dist < other.dist;
		}

		return leftPos > other.leftPos;
	}
};

// ====================
// 상수 선언
// ====================

#define INIT      100
#define ADD       200
#define REMOVE    300
#define CALCULATE 400
#define MAX_LIGHT 200000

// ====================
// 전역 변수
// ====================

int townSize, lightCount;
Light* lights[MAX_LIGHT + 1];

int poolCount;
Light lightPool[MAX_LIGHT + 2];

Light* head;
Light* tail;

std::priority_queue<PqItem> pq;

// ====================
//  유틸 함수
// ====================

void ProcessTop()
{
	while (!pq.empty())
	{
		PqItem item = pq.top();
		Light* left = lights[item.leftId];
		
		if (left != nullptr && left->next != nullptr)
		{
			if (left->next->id == item.rightId)
			{
				break;
			}
		}

		pq.pop();
	}
}

Light* AllocateLight(int id, int pos, Light* prev, Light* next)
{
	Light* light = &lightPool[poolCount++];
	light->id = id;
	light->pos = pos;
	light->prev = prev;
	light->next = next;

	return light;
}

// ====================
// 마을 상태 확인
// ====================

void InitPriorityQueue()
{
	Light* curr = head->next;
	Light* next = curr->next;
	while (next != tail)
	{
		int dist = next->pos - curr->pos;
		pq.push({ curr->id, next->id, dist, curr->pos });

		curr = next;
		next = next->next;
	}
}

void Init()
{
	std::cin >> townSize >> lightCount;

	head = AllocateLight(0, 0, nullptr, nullptr);
	tail = AllocateLight(MAX_LIGHT + 1, 0, nullptr, nullptr);
	head->next = tail;
	tail->prev = head;

	int currId = 1;
	Light* prev = head;
	while (currId <= lightCount)
	{
		int currPos;
		std::cin >> currPos;

		Light* curr = AllocateLight(currId, currPos, nullptr, nullptr);
		lights[currId++] = curr;

		prev->next = curr;
		curr->prev = prev;

		prev = curr;
	}
	prev->next = tail;
	tail->prev = prev;

	InitPriorityQueue();
}

// ====================
// 가로등 추가
// ====================

void AddLight()
{
	ProcessTop();

	PqItem item = pq.top();
	pq.pop();

	Light* prev = lights[item.leftId];
	Light* next = lights[item.rightId];

	int sumPos = prev->pos + next->pos;
	int newPos = (sumPos + 2 - 1) / 2; // sumPos + 2 - 1 => 올림 처리

	Light* newLight = AllocateLight(++lightCount, newPos, prev, next);
	lights[lightCount] = newLight;

	prev->next = newLight;
	next->prev = newLight;

	pq.push({ prev->id, newLight->id, newLight->pos - prev->pos, prev->pos });
	pq.push({ newLight->id, next->id, next->pos - newLight->pos, newLight->pos });
}

// ====================
// 가로등 제거
// ====================

void RemoveLight(int id)
{
	Light* target = lights[id];
	Light* prev = target->prev;
	Light* next = target->next;

	prev->next = next;
	next->prev = prev;

	if (prev != head && next != tail)
	{
		pq.push({ prev->id, next->id, next->pos - prev->pos, prev->pos });
	}

	lights[id] = nullptr;
}

// ====================
// 최소 전력 계산
// ====================

void PrintMinR()
{
	ProcessTop();

	int dist = 0;

	if (!pq.empty())
	{
		PqItem item = pq.top();
		dist = item.dist;
	}
	
	dist = std::max({ (head->next->pos - 1) * 2, dist, (townSize - tail->prev->pos) * 2 });

	std::cout << dist << "\n";
}

// ====================
// main 함수
// ====================

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	int Q;
	std::cin >> Q;
	while (Q--)
	{
		int cmd;
		std::cin >> cmd;

		switch (cmd)
		{
		case INIT:
			Init();
			break;
		case ADD:
			AddLight();
			break;
		case REMOVE:
			int removeId;
			std::cin >> removeId;
			RemoveLight(removeId);
			break;
		case CALCULATE:
			PrintMinR();
			break;
		}
	}

	return 0;
}
