#include <iostream>

const int MAX_N = 101;
const int MOD = 1000000000;

int dp[MAX_N][10];

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N = 0;
    std::cin >> N;

    dp[1][0] = 0;
    for(int i = 1; i <= 9; ++i)
    {
        dp[1][i] = 1;
    }
    
    for(int i = 2; i <= N; ++i)
    {
        for(int j = 0; j <= 9; ++j)
        {
            if(j == 0)
            {
                dp[i][j] = dp[i - 1][1] % MOD;
            }
            else if(j == 9)
            {
                dp[i][j] = dp[i - 1][8] % MOD;
            }
            else
            {
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j + 1]) % MOD;
            }
        }
    }

    int cnt = 0;
    for(int i = 0; i <= 9; ++i)
    {
        cnt = (cnt + dp[N][i]) % MOD;
    }

    std::cout << cnt;

    return 0;
}