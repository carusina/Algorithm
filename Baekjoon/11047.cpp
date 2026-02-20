#include <iostream>

constexpr int MAX_N = 10;

int coins[MAX_N];

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	int N, K;
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> coins[i];
	}

	int minCoins = 0;
	for (int i = N - 1; i >= 0 && K > 0; --i)
	{
		minCoins += (K / coins[i]);
		K %= coins[i];
	}

	std::cout << minCoins;

	return 0;
}
