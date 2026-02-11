#include <iostream>
#include <algorithm>

const int MAX_N = 1001;

int N;

int nums[MAX_N];
int dp[MAX_N];

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N;
    for(int i = 0; i < N; ++i)
    {
        std::cin >> nums[i];
        dp[i] = 1;
    }

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < i; ++j)
        {
            if(nums[j] < nums[i])
            {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
    }

    int maxResult = 0;
    for(int i = 0; i < N; ++i)
    {
        maxResult = std::max(maxResult, dp[i]);
    }
    std::cout << maxResult;

    return 0;
}