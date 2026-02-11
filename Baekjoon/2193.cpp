#include <iostream>

const int MAX_N = 91;
long long dp[MAX_N]; // 각 자리별 이친수 개수의 합

int N;

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> N;
	
	dp[1] = 1;
	dp[2] = 1;
	for (int i = 3; i <= N; ++i)
	{
		dp[i] = dp[i - 1] + dp[i - 2];
	}

	std::cout << dp[N];

	return 0;
}
