#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <string>
#include <set>

constexpr int MAX_NUM = 10001;
constexpr int MAX_N = 8;

int N, M;
std::vector<int> input;
int currentSeq[MAX_N];
bool isUsed[MAX_N];

void DFS(int depth, std::string currString)
{
	if (depth == M)
	{
		for (int i = 0; i < M; ++i)
		{
			std::cout << currentSeq[i] << " ";
		}
		std::cout << "\n";

		return;
	}

	int lastUsedNum = -1;

	for (int i = 0; i < input.size(); ++i)
	{
		if (!isUsed[i] && input[i] != lastUsedNum)
		{
			lastUsedNum = input[i];

			isUsed[i] = true;
			currentSeq[depth] = input[i];
			DFS(depth + 1, currString + std::to_string(input[i]) + " ");
			isUsed[i] = false;
		}
	}
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::memset(isUsed, false, sizeof(isUsed));

	std::cin >> N >> M;
	input.assign(N, 0);

	for (int i = 0; i < N; ++i)
	{
		std::cin >> input[i];
	}
	std::sort(input.begin(), input.end());

	DFS(0, "");

	return 0;
}
