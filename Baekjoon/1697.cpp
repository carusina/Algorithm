#include <iostream>
#include <vector>
#include <queue>

int BFS(std::vector<bool>& visited, std::queue<std::pair<int, int>>& q, int K);

const int Max = 100001;
const int dx[3] = {-1, 1, 2};

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N = 0, K = 0;
    std::cin >> N >> K;

    std::vector<bool> visited(Max, false);

    std::queue<std::pair<int, int>> q;
    q.push({N, 0});
    visited[N] = true;

    std::cout << BFS(visited, q, K);

    return 0;
}

int BFS(std::vector<bool>& visited, std::queue<std::pair<int, int>>& q, int K)
{
    while(!q.empty())
    {
        std::pair<int, int> curr = q.front();
        q.pop();

        if(curr.first == K)
        {
            return curr.second;
        }

        for(int d = 0; d < 3; ++d)
        {
            int nx = curr.first;

            if(dx[d] == -1 || dx[d] == 1)
            {
                nx += dx[d];
            }
            else
            {
                nx *= dx[d];
            }

            if(nx >= Max || nx < 0 || visited[nx])
            {
                continue;
            }

            q.push({nx, curr.second + 1});
            visited[nx] = true;
        }
    }
}