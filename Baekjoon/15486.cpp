#include <iostream>
#include <algorithm>

const int MAX_N = 1500001;

int N;
int T[MAX_N];
int P[MAX_N];
int dp[MAX_N];

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N;
    for(int i = 0; i < N; ++i)
    {
        std::cin >> T[i] >> P[i];
    }

    for(int i = N - 1; i >= 0; --i)
    {
        int endDay = i + T[i];

        if(endDay <= N)
        {
            dp[i] = std::max(dp[i + 1], dp[endDay] + P[i]);
        }
        else
        {
            dp[i] = dp[i + 1];
        }
    }

    std::cout << dp[0];

    return 0;
}