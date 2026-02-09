#include <iostream>
#include <algorithm>

const int INF = 0x3f3f3f3f;
const int MAX_N = 1000001;

int N;
int dp[MAX_N] = { INF };

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> N;
	dp[1] = 0;

	for (int i = 2; i <= N; ++i)
	{
		dp[i] = dp[i - 1] + 1;

		if (i % 2 == 0)
		{
			dp[i] = std::min(dp[i], dp[i / 2] + 1);
		}

		if (i % 3 == 0)
		{
			dp[i] = std::min(dp[i], dp[i / 3] + 1);
		}
	}

	std::cout << dp[N];

	return 0;
}
