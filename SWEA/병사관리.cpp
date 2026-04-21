// https://swexpertacademy.com/main/talk/solvingClub/problemView.do?contestProbId=AXxODdXKQAADFASZ&solveclubId=AZwrPjFqFyDHBIT3&problemBoxTitle=1%EC%A3%BC%EC%B0%A8&problemBoxCnt=6&probBoxId=AZwrPjFqFyHHBIT3

// ====================
// 상수 선언
// ====================

#define MAX_SOLDIER 100000
#define MAX_TEAM 5
#define MAX_SCORE 5
#define MIN_SCORE 1

// ====================
// 구조체 선언
// ====================

struct Soldier
{
	int id;
	int team;

	Soldier* prev;
	Soldier* next;
};

// ====================
// 전역 변수
// ====================

Soldier soldierPool[MAX_SOLDIER + 1];
Soldier heads[MAX_TEAM + 1][MAX_SCORE + 1];
Soldier tails[MAX_TEAM + 1][MAX_SCORE + 1];

// ====================
// 유틸 함수
// ====================

inline void splice(Soldier* srcHead, Soldier* srcTail, Soldier* destTail)
{
	if (srcHead->next == srcTail) return;

	Soldier* srcFirst = srcHead->next;
	Soldier* srcLast = srcTail->prev;

	Soldier* destLast = destTail->prev;

	destLast->next = srcFirst;

	srcFirst->prev = destLast;
	srcLast->next = destTail;

	destTail->prev = srcLast;

	srcHead->next = srcTail;
	srcTail->prev = srcHead;
}

// ====================
// API 함수
// ====================

void init()
{
	for (int team = 1; team <= MAX_TEAM; ++team)
	{
		for(int score = MIN_SCORE; score <= MAX_SCORE; ++score)
		{ 
			heads[team][score].next = &tails[team][score];
			tails[team][score].prev = &heads[team][score];
		}
	}
}

void hire(int mID, int mTeam, int mScore)
{
	Soldier* soldier = &soldierPool[mID];
	soldier->id = mID;
	soldier->team = mTeam;

	Soldier* tail = &tails[mTeam][mScore];
	Soldier* prev = tail->prev;

	prev->next = soldier;

	soldier->prev = prev;
	soldier->next = tail;
	
	tail->prev = soldier;
}

void fire(int mID)
{
	Soldier* soldier = &soldierPool[mID];

	Soldier* prev = soldier->prev;
	Soldier* next = soldier->next;

	prev->next = next;
	next->prev = prev;
}

void updateSoldier(int mID, int mScore)
{
	Soldier* soldier = &soldierPool[mID];
	
	Soldier* prev = soldier->prev;
	Soldier* next = soldier->next;

	prev->next = next;
	next->prev = prev;

	Soldier* tail = &tails[soldier->team][mScore];
	prev = tail->prev;

	prev->next = soldier;

	soldier->prev = prev;
	soldier->next = tail;

	tail->prev = soldier;
}

void updateTeam(int mTeam, int mChangeScore)
{
	if (mChangeScore > 0)
	{
		for (int score = MAX_SCORE - 1; score >= MIN_SCORE; --score)
		{
			int targetScore = (score + mChangeScore > MAX_SCORE) ? MAX_SCORE : score + mChangeScore;

			Soldier* currHead = &heads[mTeam][score];
			Soldier* currTail = &tails[mTeam][score];

			Soldier* targetTail = &tails[mTeam][targetScore];

			splice(currHead, currTail, targetTail);
		}
	}
	else if(mChangeScore < 0)
	{
		for (int score = MIN_SCORE + 1; score <= MAX_SCORE; ++score)
		{
			int targetScore = (score + mChangeScore < MIN_SCORE) ? MIN_SCORE : score + mChangeScore;

			Soldier* currHead = &heads[mTeam][score];
			Soldier* currTail = &tails[mTeam][score];

			Soldier* targetTail = &tails[mTeam][targetScore];

			splice(currHead, currTail, targetTail);
		}
	}
}

int bestSoldier(int mTeam)
{
	int maxSoldierId = 0;

	for (int score = MAX_SCORE; score >= MIN_SCORE; --score)
	{
		Soldier* head = &heads[mTeam][score];;
		Soldier* tail = &tails[mTeam][score];;
		
		Soldier* curr = head->next;
		while (curr != tail)
		{
			maxSoldierId = (maxSoldierId > curr->id) ? maxSoldierId : curr->id;
			curr = curr->next;
		}

		if (maxSoldierId != 0) return maxSoldierId;
	}

	return maxSoldierId;
}
