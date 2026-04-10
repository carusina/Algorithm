// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/pirate-captain-coddy/description

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

// ====================
// 구조체 선언
// ====================

struct Ship
{
	int id;
	int power;
	int reloadTime;
	int finishedPrepareTime;
};

struct ReadyItem
{
	int id;
	int hashIdx;
	int power;

	bool operator<(const ReadyItem& other) const
	{
		if (power != other.power)
		{
			return power < other.power;
		}

		return id > other.id;
	}
};

struct CoolDownItem
{
	int id;
	int hashIdx;
	int finishedPrepareTime;

	bool operator<(const CoolDownItem& other) const
	{
		return finishedPrepareTime > other.finishedPrepareTime;
	}
};

// ====================
// 상수 선언
// ====================

#define INIT     100
#define SUPPORT  200
#define CHANGE   300
#define ATTACK   400

#define MOD             100003
#define MAX_SHIP        60000
#define MAX_ATTACK_SHIP 5

// ====================
// 전역 변수
// ====================

int maxTime, currTime;

Ship shipPool[MOD];

std::priority_queue<ReadyItem> readyPq;
std::priority_queue<CoolDownItem> coolDownPq;

// ====================
// 유틸 함수
// ====================

int GetNewHashIndex(int id)
{
	int hash = id % MOD;
	while(shipPool[hash].id != 0)
	{ 
		hash = (hash + 1) % MOD;
	}

	return hash;
}

int GetHashIndex(int id)
{
	int hash = id % MOD;
	while (shipPool[hash].id != id)
	{
		hash = (hash + 1) % MOD;
	}

	return hash;
}

void AddShip(int id, int power, int reloadTime)
{
	int hashIdx = GetNewHashIndex(id);
	Ship& ship = shipPool[hashIdx];

	ship.id = id;
	ship.power = power;
	ship.reloadTime = reloadTime;
	ship.finishedPrepareTime = 0;

	readyPq.push({ ship.id, hashIdx, ship.power });
}

void PopInvalidReadyItems()
{
	while (!readyPq.empty())
	{
		ReadyItem item = readyPq.top();

		if (item.power == shipPool[item.hashIdx].power)
		{
			break;
		}

		readyPq.pop();
	}
}

void ProcessCooldowns()
{
	while (!coolDownPq.empty())
	{
		CoolDownItem item = coolDownPq.top();

		if (item.finishedPrepareTime > currTime)
		{
			break;
		}
		
		readyPq.push({ item.id, item.hashIdx, shipPool[item.hashIdx].power });
		coolDownPq.pop();
	}
}

// ====================
// 공격 준비
// ====================

void Init()
{
	int N;
	std::cin >> N;

	while (N--)
	{
		int id, power, reloadTime;
		std::cin >> id >> power >> reloadTime;
		AddShip(id, power, reloadTime);
	}
}

// ====================
// 지원 요청
// ====================

void AskSupport()
{
	int id, power, reloadTime;
	std::cin >> id >> power >> reloadTime;
	AddShip(id, power, reloadTime);
}

// ====================
// 함포 교체
// ====================

void ChangeCannon()
{
	int id, newPower;
	std::cin >> id >> newPower;

	int hashIdx = GetHashIndex(id);
	Ship& ship = shipPool[hashIdx];

	ship.power = newPower;

	if (ship.finishedPrepareTime <= currTime)
	{
		readyPq.push({ ship.id, hashIdx, ship.power });
	}
}

// ====================
// 공격 명령
// ====================

void Attack()
{
	std::vector<int> attackShipIdxs;
	long long totalAttackPower = 0;
	int attackShipCount = 0;
	
	while (attackShipCount < MAX_ATTACK_SHIP)
	{
		PopInvalidReadyItems();

		if (readyPq.empty())
		{
			break;
		}

		ReadyItem item = readyPq.top();
		readyPq.pop();

		Ship& ship = shipPool[item.hashIdx];

		attackShipIdxs.push_back(ship.id);
		totalAttackPower += ship.power;

		ship.finishedPrepareTime = currTime + ship.reloadTime;
		coolDownPq.push({ ship.id, item.hashIdx, ship.finishedPrepareTime });	

		attackShipCount++;
	}

	std::cout << totalAttackPower << " " << attackShipCount << " ";
	for (int id : attackShipIdxs)
	{
		std::cout << id << " ";
	}
	std::cout << std::endl;
}

// ====================
// main 함수
// ====================

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> maxTime;
	
	currTime = 1;
	for (currTime = 1; currTime <= maxTime; ++currTime)
	{
		ProcessCooldowns();

		int cmd;
		std::cin >> cmd;

		switch (cmd)
		{
		case INIT:
			Init();
			break;

		case SUPPORT:
			AskSupport();
			break;

		case CHANGE:
			ChangeCannon();
			break;

		case ATTACK:
			Attack();
			break;
		}
	}

	return 0;
}