#include <iostream>
#include <algorithm>

constexpr int MAX_T = 1001;
constexpr int MAX_W = 31;

int dp[MAX_T][MAX_W]; // w번 움직였을 때, time에 받은 자두 누적합

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int T, W;
    std::cin >> T >> W;
    for(int time = 1; time <= T; ++time)
    {
        int plumTree;
        std::cin >> plumTree;

        for(int currW = 0; currW <= W; ++currW)
        {
            int currTree = (currW % 2 == 0) ? 1 : 2;
            int getPlum = (plumTree == currTree) ? 1 : 0;

            if(currW == 0)
            {
                dp[time][currW] = dp[time - 1][currW] + getPlum;
            }
            else
            {
                dp[time][currW] = std::max(dp[time - 1][currW], dp[time - 1][currW - 1]) + getPlum;
            }
        }
    }

    int maxPlum = dp[T][0];
    for(int currW = 1; currW <= W; ++currW)
    {
        maxPlum = std::max(maxPlum, dp[T][currW]);
    }
    std::cout << maxPlum;

    return 0;
}