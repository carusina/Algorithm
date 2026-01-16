#include <iostream>
#include <vector>
#include <queue>
#include <climits>

bool IsValid(int R, int C, int y, int x);

void FireBFS(const std::vector<std::vector<char>>& board,
             std::queue<std::pair<int, int>>& fireQ,
             std::vector<std::vector<int>>& fireBoard);

int BFS(const std::vector<std::vector<char>>& board,
        std::vector<std::vector<int>>& fireBoard,
        std::vector<std::vector<int>>& jhBoard,
        std::queue<std::pair<int, int>>& jhQ);

const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int R = 0, C = 0;
    std::cin >> R >> C;

    std::vector<std::vector<char>> board(R, std::vector<char>(C));
    std::vector<std::vector<int>> fireBoard(R, std::vector<int>(C, INT_MAX));
    std::vector<std::vector<int>> jhBoard(R, std::vector<int>(C, -1));
    std::queue<std::pair<int, int>> fireQ;
    std::queue<std::pair<int, int>> jhQ;

    for(int i = 0; i < R; ++i)
    {
        for(int j = 0; j < C; ++j)
        {
            std::cin >> board[i][j];

            if(board[i][j] == 'J')
            {
                jhQ.push({i, j});
                jhBoard[i][j] = 0;
            }
            else if(board[i][j] == 'F')
            {
                fireQ.push({i, j});
                fireBoard[i][j] = 0;
            }
        }
    }

    FireBFS(board, fireQ, fireBoard);
    int time = BFS(board, fireBoard, jhBoard, jhQ);

    if(time != -1)
    {
        std::cout << time;
    }
    else
    {
        std::cout << "IMPOSSIBLE";
    }

    return 0;
}

inline bool IsValid(int R, int C, int y, int x)
{
    return 0 <= y && y < R && 0 <= x && x < C;
}

void FireBFS(const std::vector<std::vector<char>>& board,
             std::queue<std::pair<int, int>>& fireQ,
             std::vector<std::vector<int>>& fireBoard)
{
    int R = board.size();
    int C = board[0].size();

    while(!fireQ.empty())
    {
        std::pair<int, int> curr = fireQ.front();
        fireQ.pop();

        for(int d = 0; d < 4; ++d)
        {
            int ny = curr.first + dy[d];
            int nx = curr.second + dx[d];

            if(!IsValid(R, C, ny, nx))
            {
                continue;
            }

            if(board[ny][nx] == '#' || fireBoard[ny][nx] != INT_MAX)
            {
                continue;
            }

            fireBoard[ny][nx] = fireBoard[curr.first][curr.second] + 1;
            fireQ.push({ny, nx});
        }
    }
}

int BFS(const std::vector<std::vector<char>>& board,
        std::vector<std::vector<int>>& fireBoard,
        std::vector<std::vector<int>>& jhBoard,
        std::queue<std::pair<int, int>>& jhQ)
{
    int R = board.size();
    int C = board[0].size();

    while(!jhQ.empty())
    {
        std::pair<int, int> curr = jhQ.front();
        jhQ.pop();

        if(curr.first == 0 || curr.first == R - 1 || curr.second == 0 || curr.second == C - 1)
        {
            return jhBoard[curr.first][curr.second] + 1;
        }

        for(int d = 0; d < 4; ++d)
        {
            int ny = curr.first + dy[d];
            int nx = curr.second + dx[d];

            if(!IsValid(R, C, ny, nx))
            {
                continue;;
            }

            if(board[ny][nx] == '#' || jhBoard[ny][nx] != -1)
            {
                continue;
            }

            if(jhBoard[curr.first][curr.second] + 1 >= fireBoard[ny][nx])
            {
                continue;
            }

            jhBoard[ny][nx] = jhBoard[curr.first][curr.second] + 1;
            jhQ.push({ny, nx});
        }
    }

    return -1;
}