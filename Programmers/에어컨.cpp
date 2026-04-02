// https://school.programmers.co.kr/learn/courses/30/lessons/214289?language=cpp#fn1

#define TEMP_OFFSET 10
#define INF 0x3f3f3f3f
#define MAX_TEMP 40 + TEMP_OFFSET

#include <string>
#include <vector>
#include <algorithm>


int solution(int temperature, int t1, int t2, int a, int b, std::vector<int> onboard) {
    int minPower = INF;

    int onboardSize = onboard.size();

    temperature += TEMP_OFFSET;
    t1 += TEMP_OFFSET;
    t2 += TEMP_OFFSET;

    // dp[시간][온도] = 최소 전력
    std::vector<std::vector<int>> dp(onboardSize, std::vector<int>(MAX_TEMP + 1, INF));
    dp[0][temperature] = 0;

    for (int time = 0; time < onboardSize - 1; ++time)
    {
        for (int temp = 0; temp <= MAX_TEMP; ++temp)
        {
            if (dp[time][temp] == INF)
            {
                continue;
            }

            if (temp + 1 <= MAX_TEMP)
            {
                dp[time + 1][temp + 1] = std::min(dp[time + 1][temp + 1], dp[time][temp] + a);
            }

            if (temp - 1 >= 0)
            {
                dp[time + 1][temp - 1] = std::min(dp[time + 1][temp - 1], dp[time][temp] + a);
            }

            dp[time + 1][temp] = std::min(dp[time + 1][temp], dp[time][temp] + b);

            int nextTemp = temp;
            if (temp < temperature)
            {
                nextTemp++;
            }
            else if (temp > temperature)
            {
                nextTemp--;
            }

            dp[time + 1][nextTemp] = std::min(dp[time + 1][nextTemp], dp[time][temp]);
        }

        if (onboard[time + 1] == 1)
        {
            for (int temp = 0; temp <= MAX_TEMP; ++temp)
            {
                if (temp < t1 || temp > t2)
                {
                    dp[time + 1][temp] = INF;
                }
            }
        }
    }

    for (int temp = 0; temp <= MAX_TEMP; ++temp)
    {
        minPower = std::min(minPower, dp[onboardSize - 1][temp]);
    }

    return minPower;
}