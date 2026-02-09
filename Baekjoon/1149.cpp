#include <iostream>
#include <algorithm>

const int MAX_N = 1001;
const int INF = 0x3f3f3f3f;

int N;
int dp[MAX_N][3];
int cost[MAX_N][3];

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N;
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            std::cin >> cost[i][j];
        }
    }
    dp[0][0] = cost[0][0];
    dp[0][1] = cost[0][1];
    dp[0][2] = cost[0][2];

    for(int i = 1; i < N; ++i)
    {
        dp[i][0] = std::min(dp[i - 1][1], dp[i - 1][2]) + cost[i][0];
        dp[i][1] = std::min(dp[i - 1][0], dp[i - 1][2]) + cost[i][1];
        dp[i][2] = std::min(dp[i - 1][0], dp[i - 1][1]) + cost[i][2];
    }

    std::cout << std::min({dp[N - 1][0], dp[N - 1][1], dp[N - 1][2]});

    return 0;
}