#include <iostream>

const int MAX_N = 100;
const int MAX_HEIGHT = 120;

int N;
int trees[MAX_N];
int treesHeight[2][MAX_N];

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int T = 0;
    std::cin >> T;
    
    for(int test_case = 1; test_case <= T; ++test_case)
    {
        std::cin >> N;

        int maxHeight = 0;
        int needWaterTrees = 0;

        for(int i = 0; i < N; ++i)
        {
            std::cin >> trees[i];
            
            if(maxHeight < trees[i])
            {
                maxHeight = trees[i];
            }
        }

        int even = 0;
        int odd = 0;

        for(int i = 0; i < N; ++i)
        {
            int needHeight = maxHeight - trees[i];

            if(needHeight % 2 == 0)
            {
                even += needHeight / 2;
            }
            else
            {
                even += needHeight / 2;
                odd++;
            }
        }

        while(even > odd + 1)
        {
            even -= 1;
            odd += 2;
        }

        if(odd > even)
        {
            std::cout << "#" << test_case << " " << odd * 2 - 1 << "\n";
        }
        else
        {
            std::cout << "#" << test_case << " " << even * 2 << "\n";
        }
    }

    return 0;
}