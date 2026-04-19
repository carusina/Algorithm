// https://swexpertacademy.com/main/talk/solvingClub/problemView.do?solveclubId=AZwrPjFqFyDHBIT3&contestProbId=AXRSXf_a9qsDFAXS&probBoxId=AZwrPjFqFyHHBIT3&type=PROBLEM&problemBoxTitle=1%EC%A3%BC%EC%B0%A8&problemBoxCnt=6

#include <iostream>
#include <string>

inline bool IsLastNBitsOn(int numBits, int targetNum)
{
	unsigned int targetBitMask = (1 << numBits) - 1;
	return (targetBitMask & targetNum) == targetBitMask;
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
		int N, M;
		std::cin >> N >> M;

		std::string result = IsLastNBitsOn(N, M) ? "ON" : "OFF";
		std::cout << "#" << tc << " " << result << "\n";
	}

	return 0;
}