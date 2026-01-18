#include <iostream>
#include <vector>
#include <queue>

int BFS(const std::vector<std::vector<int>>& networks, int N);

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int C = 0;
    std::cin >> C;

    int N = 0;
    std::cin >> N;

    std::vector<std::vector<int>> networks(C + 1);
    for(int i = 1; i <= N; ++i)
    {
        int first = 0, second = 0;
        std::cin >> first >> second;

        networks[first].push_back(second);
        networks[second].push_back(first);
    }

    std::cout << BFS(networks, N);

    return 0;
}

int BFS(const std::vector<std::vector<int>>& networks, int N)
{
    int cnt = 0;

    std::vector<bool> visited(N + 1, false);

    std::queue<int> q;
    q.push(1);
    visited[1] = true;

    while(!q.empty())
    {
        int computer = q.front();
        q.pop();

        for(int d : networks[computer])
        {
            if(visited[d])
            {
                continue;
            }

            q.push(d);
            visited[d] = true;
            cnt++;
        }
    }

    return cnt;
}