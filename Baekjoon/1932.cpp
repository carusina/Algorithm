#include <iostream>
#include <algorithm>

const int INF = 5000001;
const int MAX_N = 502;

int N;
int dp[MAX_N * (MAX_N + 1) / 2] = { 0 }; // 각 i별 최대 누적합
int tri[MAX_N * (MAX_N + 1) / 2];

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> N;
	for (int i = 1; i <= N * (N + 1) / 2; ++i)
	{
		std::cin >> tri[i];
	}
	
	int parentIdx = N * (N + 1) / 2;
	for (int i = N; i >= 1; --i, --parentIdx)
	{
		dp[parentIdx] = tri[parentIdx];
	}

	for (int level = N - 1; level >= 1; --level)
	{
		for (int j = level; j >= 1; --j, --parentIdx)
		{
			int leftChildIdx = parentIdx + level;
			int rightChildIdx = parentIdx + level + 1;

			dp[parentIdx] = std::max(dp[leftChildIdx], dp[rightChildIdx]) + tri[parentIdx];
		}
	}

	std::cout << dp[1];

	return 0;
}
