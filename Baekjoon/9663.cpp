#include <iostream>

constexpr int MAX_N = 15;

int cnt;
int N;

bool isUsedCol[MAX_N];
bool isUsedDiagPositive[MAX_N * 2];
bool isUsedDiagNegative[MAX_N * 2];

void DFS(int y)
{
	if (y == N)
	{
		cnt++;
		return;
	}

	for (int x = 0; x < N; ++x)
	{
		if (isUsedCol[x] || isUsedDiagPositive[y + x] || isUsedDiagNegative[y - x + N - 1])
		{
			continue;
		}

		isUsedCol[x] = true;
		isUsedDiagPositive[y + x] = true;
		isUsedDiagNegative[y - x + N - 1] = true;

		DFS(y + 1);

		isUsedCol[x] = false;
		isUsedDiagPositive[y + x] = false;
		isUsedDiagNegative[y - x + N - 1] = false;
	}
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> N;
	DFS(0);
	std::cout << cnt;

	return 0;
}
