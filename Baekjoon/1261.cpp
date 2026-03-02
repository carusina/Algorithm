#include <iostream>
#include <queue>

constexpr int MAX_N = 100;
constexpr int MAX_M = 100;

constexpr int dy[] = {-1, 1, 0, 0};
constexpr int dx[] = {0, 0, -1, 1};

struct Node
{
    int y, x;
    int cntUsedAOJ;
};

int N, M;
int board[MAX_M][MAX_N];
bool visited[MAX_M][MAX_N];

inline bool IsValid(int y, int x)
{
    return 0 <= y && y < M &&
           0 <= x && x < N;
}

int BFS()
{
    std::deque<Node> dq;
    dq.push_back({0, 0, 0});
    visited[0][0] = true;

    while(!dq.empty())
    {
        Node curr = dq.front();
        dq.pop_front();

        if(curr.y == M - 1 && curr.x == N - 1)
        {
            return curr.cntUsedAOJ;
        }

        for(int d = 0; d < 4; ++d)
        {
            int ny = curr.y + dy[d];
            int nx = curr.x + dx[d];

            if(IsValid(ny, nx) && !visited[ny][nx])
            {
                visited[ny][nx] = true;

                if(board[ny][nx] == 1)
                {
                    dq.push_back({ny, nx, curr.cntUsedAOJ + 1});
                }
                else
                {
                    dq.push_front({ny, nx, curr.cntUsedAOJ});
                }
            }
        }
    }

    return -1;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N >> M;
    for(int i = 0; i < M; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            char ch;
            std::cin >> ch;
            board[i][j] = ch - '0';
        }
    }

    std::cout << BFS();

    return 0;
}