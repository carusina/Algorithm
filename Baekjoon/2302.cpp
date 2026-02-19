#include <iostream>

constexpr int MAX_N = 41;

int dp[MAX_N];

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	int N, M;
	std::cin >> N;
	std::cin >> M;

	dp[0] = 1;
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= N; ++i)
	{
		dp[i] = dp[i - 1] + dp[i - 2];
	}

	int result = 1;
	int prev = 0;
	for (int i = 0; i < M; ++i)
	{
		int vip;
		std::cin >> vip;
		
		result *= dp[vip - prev - 1];
		prev = vip;
	}
	result *= dp[N - prev];

	std::cout << result;

	return 0;
}
