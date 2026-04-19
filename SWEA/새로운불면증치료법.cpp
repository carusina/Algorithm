// https://swexpertacademy.com/main/talk/solvingClub/problemView.do?contestProbId=AV18_yw6I9MCFAZN&solveclubId=AZwrPjFqFyDHBIT3&problemBoxTitle=1%EC%A3%BC%EC%B0%A8&problemBoxCnt=6&probBoxId=AZwrPjFqFyHHBIT3

#include <iostream>

#define TOTAL_DIGITS 10
#define DECIMAL_BASE 10

constexpr int fullMask = (1 << TOTAL_DIGITS) - 1;

int GetTargetMultiple(int N)
{
	int mask = 0;

	for (int current = N;; current += N)
	{
		int temp = current;

		while (temp > 0)
		{
			int digit = temp % DECIMAL_BASE;
			mask |= (1 << digit);
			temp /= 10;

			if (mask == fullMask) return current;
		}
	}

	return -1;
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	int T;
	std::cin >> T;
	for (int tc = 1; tc <= T; ++tc)
	{
		int N;
		std::cin >> N;
		std::cout << "#" << tc << " " << GetTargetMultiple(N) << "\n";
	}

	return 0;
}