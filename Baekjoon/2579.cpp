#include <iostream>
#include <algorithm>

const int MAX_N = 300;

int N;
int stair[MAX_N];
int dp[MAX_N];

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> stair[i];
	}

	dp[0] = stair[0];
	dp[1] = stair[0] + stair[1];
	dp[2] = std::max(stair[0] + stair[2], stair[1] + stair[2]);

	for (int i = 3; i < N; ++i)
	{
		dp[i] = std::max(dp[i - 2], dp[i - 3] + stair[i - 1]) + stair[i];
	}

	std::cout << dp[N - 1];
	return 0;
}
