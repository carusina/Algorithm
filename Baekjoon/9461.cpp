#include <iostream>

const int MAX_N = 101;

int N;
long long p[MAX_N];

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    p[1] = p[2] = p[3] = 1;

    for(int i = 4; i < MAX_N; ++i)
    {
        p[i] = p[i - 2] + p[i - 3];
    }

    int T = 0;
    std::cin >> T;
    for(int test_case = 1; test_case <= T; ++test_case)
    {
        std::cin >> N;
        std::cout << p[N] << "\n";
    }

    return 0;
}