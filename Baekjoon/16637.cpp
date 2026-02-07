#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

const int MAX_N = 19;

int N;
std::string expr;
std::vector<int> nums;
std::vector<char> ops;

int maxResult = INT_MIN;

int Calculate(int a, char op, int b)
{
    if(op == '+')
    {
        return a + b;
    }
    else if(op == '-')
    {
        return a - b;
    }
    else
    {
        return a * b;
    }

    return INT_MIN;
}

void DFS(int opIdx, int currentVal)
{
    if(opIdx == ops.size())
    {
        maxResult = std::max(maxResult, currentVal);
        return;
    }

    int result = Calculate(currentVal, ops[opIdx], nums[opIdx + 1]);
    DFS(opIdx + 1, result);

    if(opIdx + 1 < ops.size())
    {
        int braketValue = Calculate(nums[opIdx + 1], ops[opIdx + 1], nums[opIdx + 2]);
        result = Calculate(currentVal, ops[opIdx], braketValue);

        DFS(opIdx + 2, result);
    }
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N;
    std::cin >> expr;

    for(int i = 0; i < N; ++i)
    {
        if(i % 2 == 0)
        {
            nums.push_back(expr[i] - '0');
        }
        else
        {
            ops.push_back(expr[i]);
        }
    }

    DFS(0, nums[0]);
    std::cout << maxResult;

    return 0;
}