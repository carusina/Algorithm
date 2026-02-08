#include <iostream>

const int MAX_N = 16;

int N;
int board[MAX_N + 1][MAX_N + 1];
int dp[MAX_N + 1][MAX_N + 1][3];

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N;
    for(int i = 1; i <= N; ++i)
    {
        for(int j = 1; j <= N; ++j)
        {
            std::cin >> board[i][j];
        }
    }

    dp[1][2][0] = 1;

    for(int i = 1; i <= N; ++i)
    {
        for(int j = 1; j <= N; ++j)
        {
            if(board[i][j] == 1)
            {
                continue;
            }

            if(j - 1 >= 1)
            {
                dp[i][j][0] += dp[i][j - 1][0] + dp[i][j - 1][2];
            }
            if(i - 1 >= 1)
            {
                dp[i][j][1] += dp[i - 1][j][1] + dp[i - 1][j][2];
            }
            if(i - 1 >= 1 && j - 1 >= 1 && board[i - 1][j] == 0 && board[i][j - 1] == 0)
            {
                dp[i][j][2] = dp[i - 1][j - 1][0] + dp[i - 1][j - 1][1] + dp[i - 1][j - 1][2];
            }
        }
    }
    std::cout << dp[N][N][0] + dp[N][N][1] + dp[N][N][2];

    return 0;
}