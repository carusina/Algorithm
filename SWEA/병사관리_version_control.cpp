// https://swexpertacademy.com/main/talk/solvingClub/problemView.do?contestProbId=AXxODdXKQAADFASZ&solveclubId=AZwrPjFqFyDHBIT3&problemBoxTitle=1%EC%A3%BC%EC%B0%A8&problemBoxCnt=6&probBoxId=AZwrPjFqFyHHBIT3

// ====================
// 상수 선언
// ====================

#define MAX_SOLDIER 100000
#define MAX_UPDATE_SOLDIER 100000
#define MAX_TEAM 5
#define MAX_SCORE 5
#define MIN_SCORE 1

// ====================
// 구조체 선언
// ====================

struct Soldier
{
	int id;
	int version;
	Soldier* next;
};

struct SoldierInfo
{
	int team;
	int version;
};

// ====================
// 전역 변수 선언
// ====================

int soldierCount;
Soldier soldierPool[MAX_SOLDIER + MAX_UPDATE_SOLDIER + 1];
SoldierInfo soldierInfo[MAX_SOLDIER + 1];

Soldier heads[MAX_TEAM + 1][MAX_SCORE + 1];
Soldier* tails[MAX_TEAM + 1][MAX_SCORE + 1];

// ====================
// 유틸 함수 구현부
// ====================

inline void Splice(int mTeam, int mScore, int targetScore)
{
	if (heads[mTeam][mScore].next == nullptr) return;

	tails[mTeam][targetScore]->next = heads[mTeam][mScore].next;
	tails[mTeam][targetScore] = tails[mTeam][mScore];

	heads[mTeam][mScore].next = nullptr;
	tails[mTeam][mScore] = &heads[mTeam][mScore];
}

// ====================
// API 구현부
// ====================

void init()
{
	soldierCount = 0;

	for (int team = 1; team <= MAX_TEAM; ++team)
	{
		for (int score = MIN_SCORE; score <= MAX_SCORE; ++score)
		{
			heads[team][score].next = nullptr;
			tails[team][score] = &heads[team][score];
		}
	}
}

void hire(int mID, int mTeam, int mScore)
{
	Soldier& soldier = soldierPool[soldierCount++];
	soldier.id = mID;
	soldier.version = ++soldierInfo[mID].version;
	soldier.next = nullptr;

	soldierInfo[mID].team = mTeam;

	tails[mTeam][mScore]->next = &soldier;
	tails[mTeam][mScore] = &soldier;
}

void fire(int mID)
{
	soldierInfo[mID].version = -1;
}

void updateSoldier(int mID, int mScore)
{
	hire(mID, soldierInfo[mID].team, mScore);
}

void updateTeam(int mTeam, int mChangeScore)
{
	if (mChangeScore > 0)
	{
		for (int score = MAX_SCORE - 1; score >= MIN_SCORE; --score)
		{
			int targetScore = (score + mChangeScore) > MAX_SCORE ? MAX_SCORE : (score + mChangeScore);
			Splice(mTeam, score, targetScore);
		}
	}
	else if (mChangeScore < 0)
	{
		for (int score = MIN_SCORE + 1; score <= MAX_SCORE; ++score)
		{
			int targetScore = (score + mChangeScore) < MIN_SCORE ? MIN_SCORE : (score + mChangeScore);
			Splice(mTeam, score, targetScore);
		}
	}
}

int bestSoldier(int mTeam)
{
	int bestSoldierID = 0;

	for (int score = MAX_SCORE; score >= MIN_SCORE; --score)
	{
		const Soldier* curr = heads[mTeam][score].next;
		while (curr != nullptr)
		{
			if (curr->version == soldierInfo[curr->id].version)
			{
				bestSoldierID = curr->id > bestSoldierID ? curr->id : bestSoldierID;
			}

			curr = curr->next;
		}

		if (bestSoldierID != 0) return bestSoldierID;
	}

	return -1;
}
