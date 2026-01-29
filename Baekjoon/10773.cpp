#include <iostream>
#include <stack>

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int K = 0;
    std::cin >> K;

    std::stack<int> s;
    
    int num = 0;
    for(int i = 0; i < K; ++i)
    {
        std::cin >> num;

        if(num == 0)
        {
            s.pop();
        }
        else
        {
            s.push(num);
        }
    }

    unsigned int sum = 0;
    while(!s.empty())
    {
        sum += s.top();
        s.pop();
    }

    std::cout << sum;

    return 0;
}