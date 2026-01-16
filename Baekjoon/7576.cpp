#include <iostream>
#include <vector>
#include <queue>

bool IsValid(int N, int M, int y, int x);
void BFS(std::vector<std::vector<int>>& board, std::queue<std::pair<int, int>>& q,
         int& unripeCnt, int& maxDay);

const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N = 0, M = 0;
    std::cin >> M >> N;

    std::vector<std::vector<int>> board(N, std::vector<int>(M, 0));
    std::queue<std::pair<int, int>> q;

    int unripeCnt = 0;

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < M; ++j)
        {
            std::cin >> board[i][j];
            
            if(board[i][j] == 1)
            {
                q.push({i, j});
            }
            else if(board[i][j] == 0)
            {
                unripeCnt++;
            }
        }
    }

    if(unripeCnt == 0)
    {
        std::cout << 0 << "\n";
        return 0;
    }

    int maxDay = 0;
    BFS(board, q, unripeCnt, maxDay);

    if(unripeCnt > 0)
    {
        std::cout << -1 << "\n";
    }
    else
    {
        std::cout << maxDay - 1 << "\n";
    }

    return 0;
}

bool IsValid(int N, int M, int y, int x)
{
    return 0 <= y && y < N && 0 <= x && x < M;
}

void BFS(std::vector<std::vector<int>>& board, std::queue<std::pair<int, int>>& q,
         int& unripeCnt, int& maxDay)
{
    int N = board.size();
    int M = board[0].size();

    while(!q.empty())
    {
        std::pair<int, int> curr = q.front();
        q.pop();

        for(int d = 0; d < 4; ++d)
        {
            int ny = curr.first + dy[d];
            int nx = curr.second + dx[d];

            if(!IsValid(N, M, ny, nx))
            {
                continue;
            }

            if(board[ny][nx] == 0)
            {
                board[ny][nx] = board[curr.first][curr.second] + 1;
                q.push({ny, nx});

                maxDay = board[ny][nx];
                unripeCnt--;
            }
        }
    }
}