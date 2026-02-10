#include <iostream>

const int MAX_N = 1001;

int n;
int dp[MAX_N];

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n;

    dp[1] = 1;
    dp[2] = 3;

    for(int i = 3; i <= n; ++i)
    {
        dp[i] = (dp[i - 2] + dp[i - 2] + dp[i - 1]) % 10007;
    }

    std::cout << dp[n];

    return 0;
}