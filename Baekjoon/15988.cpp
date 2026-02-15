#include <iostream>

constexpr int MAX_N = 1000000;
constexpr int MOD = 1000000009;

long long dp[MAX_N + 1];

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4; 
    
    for(int i = 4; i <= MAX_N; ++i)
    {
        dp[i] = (dp[i - 1] + dp[i - 2] + dp[i - 3]) % MOD;
    }

    int T;
    std::cin >> T;
    for(int test_case = 1; test_case <= T; ++test_case)
    {
        int n;
        std::cin >> n;
        std::cout << dp[n] << "\n";
    }

    return 0;
}