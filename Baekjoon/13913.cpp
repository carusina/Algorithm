#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

const int MAX = 100001;

int board[MAX] = {0};
int path[MAX] = {0};

void BFS(int N, int K);

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N = 0, K = 0;
    std::cin >> N >> K;

    board[N] = 1;
    path[N] = N;

    BFS(N, K);
    
    return 0;
}

void BFS(int N, int K)
{
    std::queue<int> q;
    q.push(N);

    while(!q.empty())
    {
        int curr = q.front();
        q.pop();

        if(curr == K)
        {
            std::cout << board[K] - 1 << "\n";
    
            std::vector<int> paths;
            for(int i = K; i != N; i = path[i])
            {
                paths.push_back(i);
            }
            paths.push_back(N);

            std::reverse(paths.begin(), paths.end());

            for(int p : paths)
            {
                std::cout << p << " ";
            }
            return;
        }

        int next_moves[3] = {curr - 1, curr + 1, curr * 2};
        for(int nx : next_moves)
        {
            if(nx < 0 || nx > 100000)
            {
                continue;
            }
            
            if(board[nx] != 0)
            {
                continue;
            }

            board[nx] = board[curr] + 1;
            path[nx] = curr;
            q.push(nx);
        }
    }

    return;
}