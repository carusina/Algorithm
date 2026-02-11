#include <iostream>
#include <algorithm>

const int MIN_INF = -0x3f3f3f3f;
const int MAX_N = 100000;

int nums[MAX_N];

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	int N = 0;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> nums[i];
	}
	
	int maxResult = nums[0];
	int currentSum = nums[0];
	for (int i = 1; i < N; ++i)
	{
		currentSum = std::max(nums[i], nums[i] + currentSum);
		maxResult = std::max(maxResult, currentSum);
	}

	std::cout << maxResult;

	return 0;
}
