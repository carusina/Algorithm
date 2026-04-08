// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/delivery-service/description

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

// ====================
// 구조체 선언
// ====================

struct Box
{
	int id;
	int startR, startC;
	int endR, endC;
};

// ====================
// 상수 선언
// ====================

#define MAX_N 50
#define MAX_K 100

// ====================
// 전역 변수 선언
// ====================

int N, M;
int grid[MAX_N + 1][MAX_N + 1];

Box boxes[MAX_K + 1];

// ====================
// 유틸 함수
// ====================

inline bool IsValid(int r, int c)
{
	return 1 <= r && r <= N &&
		   1 <= c && c <= N;
}

void RemoveBoxFromGrid(const Box& box)
{
	for (int r = box.startR; r <= box.endR; ++r)
	{
		for (int c = box.startC; c <= box.endC; ++c)
		{
			grid[r][c] = 0;
		}
	}
}

void AddBoxToGrid(const Box& box)
{
	for (int r = box.startR; r <= box.endR; ++r)
	{
		for (int c = box.startC; c <= box.endC; ++c)
		{
			grid[r][c] = box.id;
		}
	}
}

void GetUpperBoxIds(const Box& box, std::set<int>& upperBoxIds)
{
	if (IsValid(box.startR - 1, box.startC))
	{
		for (int c = box.startC; c <= box.endC; ++c)
		{
			int upperBoxId = grid[box.startR - 1][c];
			if (upperBoxId != 0)
			{
				upperBoxIds.insert(upperBoxId);
			}
		}
	}
}

void ApplyGravity(Box& box)
{
	int boxHeight = box.endR - box.startR + 1;

	std::set<int> upperBoxIds;
	GetUpperBoxIds(box, upperBoxIds);

	bool blocked = false;
	int maxR = box.endR;
	for (int r = box.endR + 1; r <= N; ++r)
	{
		for (int c = box.startC; c <= box.endC; ++c)
		{
			if (grid[r][c] != 0)
			{
				blocked = true;
				break;
			}
		}

		if (blocked) break;

		maxR++;
	}

	RemoveBoxFromGrid(box);

	box.endR = maxR;
	box.startR = box.endR - boxHeight + 1;
	AddBoxToGrid(box);

	for (int id : upperBoxIds)
	{
		ApplyGravity(boxes[id]);
	}

	return;
}

// ====================
// 택배 투입
// ====================

void InsertBox(Box& box)
{
	AddBoxToGrid(box);
	ApplyGravity(box);
}

// ====================
// 택배 하차
// ====================

bool IsSideEmpty(const Box& box, bool isLeftTurn)
{
	if (isLeftTurn)
	{
		for (int r = box.startR; r <= box.endR; ++r)
		{
			for (int c = 1; c < box.startC; ++c)
			{
				if (grid[r][c] != 0)
				{
					return false;
				}
			}
		}
	}
	else
	{
		for (int r = box.startR; r <= box.endR; ++r)
		{
			for (int c = box.endC + 1; c <= N; ++c)
			{
				if (grid[r][c] != 0)
				{
					return false;
				}
			}
		}
	}

	return true;
}

int GetPickupBoxId(bool isLeftTurn)
{
	for (int id = 1; id <= MAX_K; ++id)
	{
		if (boxes[id].startR != 0)
		{
			if (IsSideEmpty(boxes[id], isLeftTurn))
			{
				return id;
			}
		}
	}
	
	return -1;
}

int PickupBox(int count)
{
	bool isLeftTurn = (count % 2 == 0);

	int boxId = GetPickupBoxId(isLeftTurn);
	Box& box = boxes[boxId];

	std::set<int> upperBoxIds;
	GetUpperBoxIds(box, upperBoxIds);

	RemoveBoxFromGrid(box);
	box.startR = box.startC = 0;
	box.endR = box.endC = 0;

	for (int id : upperBoxIds)
	{
		ApplyGravity(boxes[id]);
	}

	return boxId;
}

// ====================
// main 함수
// ====================

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N >> M;
	for (int i = 1; i <= M; ++i)
	{
		int id, height, width, startC;

		std::cin >> id >> height >> width >> startC;
		boxes[id] = { id, 1, startC, height, startC + width - 1 };

		InsertBox(boxes[id]);
	}

	int count = 0;
	while (count < M)
	{
		std::cout << PickupBox(count++) << std::endl;
	}

	return 0;
}