#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N;
    std::cin >> N;
    
    std::vector<int> times(N);
    for(int i = 0; i < N; ++i)
    {
        std::cin >> times[i];
    }
    std::sort(times.begin(), times.end());

    int totalWaitTime = 0;
    for(int i = 0; i < N; ++i)
    {
        totalWaitTime += (times[i] * (N - i));
    }

    std::cout << totalWaitTime;

    return 0;
}