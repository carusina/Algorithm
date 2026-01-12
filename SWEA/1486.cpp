#include <iostream>
#include <vector>
#include <climits>

void GetMinDiff(const std::vector<int>& heights, int N, int B, int index, int currentSum, int& minDiff);
int Solution(const std::vector<int>& heights, const int B);

int main()
{
    int T = 0;
    std::cin >> T;

    for(int test_case = 1; test_case <= T; ++test_case)
    {
        int N = 0, B = 0;
        std::cin >> N >> B;

        std::vector<int> heights(N, 0);
        for(int i = 0; i < N; ++i)
        {
            std::cin >> heights[i];
        }

        std::cout << "#" << test_case << " " << Solution(heights, B) << "\n";
    }

    return 0;
}

void GetMinDiff(const std::vector<int>& heights, int N, int B, int index, int currentSum, int& minDiff)
{
    if(currentSum >= B)
    {
        int diff = currentSum - B;
        if(diff < minDiff)
        {
            minDiff = diff;
        }

        return;
    }

    if(index == N)
    {
        return;
    }

    GetMinDiff(heights, N, B, index + 1, currentSum + heights[index], minDiff);
    GetMinDiff(heights, N, B, index + 1, currentSum, minDiff);
}

int Solution(const std::vector<int>& heights, const int B)
{
    int minDiff = INT_MAX;
    int N = heights.size();

    GetMinDiff(heights, N, B, 0, 0, minDiff);

    return minDiff;
}