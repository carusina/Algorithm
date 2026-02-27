#include <iostream>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int T;
    std::cin >> T;
    for(int test_case = 1; test_case <= T; ++test_case)
    {
        int N;
        std::cin >> N;
        
        std::vector<int>prices(N);
        for(int i = 0; i < N; ++i)
        {
            std::cin >> prices[i];
        }

        int maxPrice = 0;
        long long profit = 0;
        for(int i = N - 1; i >= 0; --i)
        {
            if(prices[i] > maxPrice)
            {
                maxPrice = prices[i];
            }
            else
            {
                profit += (maxPrice - prices[i]);
            }
        }

        std::cout << profit << "\n";
    }

    return 0;
}