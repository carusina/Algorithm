#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    std::vector<int> B(N);

    for(int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }

    for(int i = 0; i < N; ++i)
    {
        std::cin >> B[i];
    }

    std::sort(A.begin(), A.end());
    std::sort(B.rbegin(), B.rend());

    int result = 0;
    for(int i = 0; i < N; ++i)
    {
        result += (A[i] * B[i]);
    }

    std::cout << result;

    return 0;
}