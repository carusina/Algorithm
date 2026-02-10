#include <iostream>

const int MAX_N = 20;

int nums[MAX_N];

int N, S;
int cntS;

void DFS(int depth, int currVal, int usedNumCnt)
{
    if(depth == N)
    {
        if(usedNumCnt > 0 && currVal == S)
        {
            cntS++;
        }
        return;
    }

    DFS(depth + 1, currVal + nums[depth], usedNumCnt + 1);
    DFS(depth + 1, currVal, usedNumCnt);
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N >> S;
    for(int i = 0; i < N; ++i)
    {
        std::cin >> nums[i];
    }

    DFS(0, 0, 0);

    std::cout << cntS;

    return 0;
}