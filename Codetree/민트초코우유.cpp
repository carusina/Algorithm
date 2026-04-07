// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/mint-choco-milk/description

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

// ====================
// 상수 정의
// ====================

#define MAX_N 50

constexpr int MINT  = 1; // T = 001
constexpr int CHOCO = 2; // C = 010
constexpr int MILK  = 4; // M = 100
constexpr int FULL  = 7; // TCM = 111

constexpr int PRINT_ORDER[] = { 7, 3, 5, 6, 4, 2, 1 };
constexpr int dy[] = { -1, 1, 0, 0 };
constexpr int dx[] = { 0, 0,-1, 1 };

// ====================
// 자료구조
// ====================

struct Student
{
	int y, x;
	int food;
	int belif;
	int shieldTurn;
};

// ====================
// 전역 변수
// ====================

int N, maxTurn, currTurn;
Student students[MAX_N + 1][MAX_N + 1];
bool visited[MAX_N + 1][MAX_N + 1];
std::vector<Student*> presidents;
int belifs[FULL + 1];

// ====================
// 유틸
// ====================

inline bool IsValid(int y, int x)
{
	return 1 <= y && y <= N &&
		   1 <= x && x <= N;
}

// a가 b보다 우선순위 높으면 true
bool IsMorePrior(const Student* a, const Student* b)
{
	if (a->belif != b->belif) return a->belif > b->belif;
	if (a->y != b->y)         return a->y < b->y;

	return a->x < b->x;
}

inline int FoodLevel(int food)
{
	int cnt = 0;

	while (food)
	{ 
		cnt += (food & 1);
		food >>= 1;
	}

	return cnt;
}

// ====================
// 아침
// ====================

void MorningTurn()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			students[i][j].belif++;
		}
	}
}

// ====================
// 점심
// ====================

void BFS(std::vector<Student*>& group, int sy, int sx)
{
	std::queue<std::pair<int, int>> q;

	q.push({ sy, sx });
	visited[sy][sx] = true;
	group.push_back(&students[sy][sx]);

	int targetFood = students[sy][sx].food;

	while (!q.empty())
	{
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();

		for (int d = 0; d < 4; d++)
		{
			int ny = cy + dy[d];
			int nx = cx + dx[d];

			if (IsValid(ny, nx) && !visited[ny][nx] && students[ny][nx].food == targetFood)
			{
				visited[ny][nx] = true;
				q.push({ ny, nx });
				group.push_back(&students[ny][nx]);
			}
		}
	}
}

void LunchTurn()
{
	std::memset(visited, false, sizeof(visited));
	presidents.clear();

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (!visited[i][j])
			{
				std::vector<Student*> group;
				BFS(group, i, j);

				Student* president = *std::max_element(
					group.begin(), group.end(),
					[](const Student* a, const Student* b) {
						return IsMorePrior(b, a);
					}
				);

				int n = (int)group.size();
				president->belif += (n - 1);
				presidents.push_back(president);

				for (Student* s : group)
				{
					if (s != president) s->belif--;
				}
			}
		}
	}
}

// ====================
// 저녁
// ====================

void Spread(Student* pres)
{
	if (pres->shieldTurn == currTurn) return;

	int dir = pres->belif % 4;
	int x = pres->belif - 1;
	pres->belif = 1;

	int cy = pres->y + dy[dir];
	int cx = pres->x + dx[dir];

	while (x > 0 && IsValid(cy, cx))
	{
		Student& t = students[cy][cx];

		if (t.food == pres->food)
		{
			// 같은 음식 → x 소모 없이 통과
		}
		else if (x > t.belif)
		{
			x -= (t.belif + 1);
			t.food = pres->food;
			t.belif++;
			t.shieldTurn = currTurn;
		}
		else
		{
			t.food |= pres->food;
			t.belif += x;
			x = 0;
			t.shieldTurn = currTurn;
		}

		cy += dy[dir];
		cx += dx[dir];
	}
}

void DinnerTurn()
{
	std::vector<Student*> bucket[4];
	for (Student* p : presidents)
	{
		bucket[FoodLevel(p->food)].push_back(p);
	}

	for (int level = 1; level <= 3; level++)
	{
		std::sort(bucket[level].begin(), bucket[level].end(), IsMorePrior);

		for (Student* p : bucket[level])
		{
			Spread(p);
		}
	}

	std::memset(belifs, 0, sizeof(belifs));
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			belifs[students[i][j].food] += students[i][j].belif;
		}
	}
}

// ====================
// 출력
// ====================

void PrintResult()
{
	for (int food : PRINT_ORDER)
	{
		std::cout << belifs[food] << " ";
	}
	std::cout << "\n";
}

// ====================
// main
// ====================

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N >> maxTurn;

	for (int i = 1; i <= N; i++)
	{
		std::string row;
		std::cin >> row;

		for (int j = 1; j <= N; j++)
		{
			char c = row[j - 1];
			if (c == 'T')      students[i][j].food = MINT;
			else if (c == 'C') students[i][j].food = CHOCO;
			else if (c == 'M') students[i][j].food = MILK;

			students[i][j].y = i;
			students[i][j].x = j;
			students[i][j].shieldTurn = 0;
		}
	}

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			std::cin >> students[i][j].belif;

	for (currTurn = 1; currTurn <= maxTurn; currTurn++)
	{
		MorningTurn();
		LunchTurn();
		DinnerTurn();
		PrintResult();
	}

	return 0;
}
