#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N;
    std::cin >> N;

    std::vector<int> ropes(N);
    for(int i = 0; i < N; ++i)
    {
        std::cin >> ropes[i];
    }
    std::sort(ropes.rbegin(), ropes.rend());

    int maxWeight = 0;
    
    for(int i = 0; i < N; ++i)
    {
        maxWeight = std::max(maxWeight, ropes[i] * (i + 1));
    }
    std::cout << maxWeight;

    return 0;
}