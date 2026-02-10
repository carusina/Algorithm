#include <iostream>

const int MAX_N = 100001;

int N, M;
int dp[MAX_N]; // 0에서 j까지의 합

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i)
	{
		int num;
		std::cin >> num;
		
		dp[i] = dp[i - 1] + num;
	}

	for (int cnt = 0; cnt < M; ++cnt)
	{
		int i, j;
		std::cin >> i >> j;

		std::cout << dp[j] - dp[i - 1] << "\n";
	}
	
	return 0;
}
