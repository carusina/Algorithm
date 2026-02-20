#include <iostream>
#include <algorithm>

constexpr int MAX_N = 50001;
int dp[MAX_N];

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	int n;
	std::cin >> n;
	
	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 3;

	for (int i = 4; i <= n; ++i)
	{
		dp[i] = dp[i - 1] + 1;

		for (int j = 2; j * j <= i; ++j)
		{
			dp[i] = std::min(dp[i], dp[i - j * j] + 1);
		}
	}

	std::cout << dp[n];

	return 0;	
}
