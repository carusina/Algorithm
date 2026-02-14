#include <iostream>
#include <algorithm>

constexpr int MAX_N = 10001;

int N;
int wine[MAX_N];
int dp[MAX_N];

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N;
    for(int i = 1; i <= N; ++i)
    {
        std::cin >> wine[i];
    }

    dp[1] = wine[1];
    dp[2] = wine[1] + wine[2];

    for(int i = 3; i <= N; ++i)
    {
        dp[i] = std::max({dp[i - 1], wine[i] + dp[i - 2], wine[i] + wine[i - 1] + dp[i - 3]});
    }
    std::cout << dp[N];

    return 0;
}