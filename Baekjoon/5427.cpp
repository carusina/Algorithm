#include <iostream>
#include <vector>
#include <queue>

const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};

struct Point
{
    int y, x;
};

inline bool IsValid(int h, int w, int y, int x);
inline bool IsEdge(int h, int w, int y, int x);
void FireBFS(std::vector<std::vector<char>>& board, std::queue<Point>& fireQ);
int EscapeBFS(std::vector<std::vector<char>>& board, std::queue<Point>& sgQ, std::queue<Point>& fireQ);

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int T = 0;
    std::cin >> T;

    for(int test_case = 1; test_case <= T; ++test_case)
    {
        int h = 0, w = 0;
        std::cin >> w >> h;

        std::vector<std::vector<char>> board(h, std::vector<char>(w));
        std::queue<Point> fireQ;
        std::queue<Point> sgQ;
        
        for(int i = 0; i < h; ++i)
        {
            for(int j = 0; j < w; ++j)
            {
                std::cin >> board[i][j];

                if(board[i][j] == '@')
                {
                    sgQ.push({i, j});
                    board[i][j] = '.';
                }
                else if(board[i][j] == '*')
                {
                    fireQ.push({i, j});
                    board[i][j] = '#';
                }
            }
        }

        int result = EscapeBFS(board, sgQ, fireQ);
        if(result == -1)
        {
            std::cout << "IMPOSSIBLE" << "\n"; 
        }
        else
        {
            std::cout << result << "\n";
        }
    }
    
    return 0;
}

inline bool IsValid(int h, int w, int y, int x)
{
    return 0 <= y && y < h &&
           0 <= x && x < w;
}

inline bool IsEdge(int h, int w, int y, int x)
{
    return y == 0 || y == h - 1 ||
           x == 0 || x == w - 1;
}

void FireBFS(std::vector<std::vector<char>>& board, std::queue<Point>& fireQ)
{
    int h = board.size();
    int w = board[0].size();
    int n = fireQ.size();
    
    while(n--)
    {
        Point curr = fireQ.front();
        fireQ.pop();

        for(int d = 0; d < 4; ++d)
        {
            int ny = curr.y + dy[d];
            int nx = curr.x + dx[d];

            if(!IsValid(h, w, ny, nx))
            {
                continue;
            }

            if(board[ny][nx] != '.')
            {
                continue;
            }

            board[ny][nx] = '#';
            fireQ.push({ny, nx});
        }
    }
}

int EscapeBFS(std::vector<std::vector<char>>& board, std::queue<Point>& sgQ, std::queue<Point>& fireQ)
{
    int h = board.size();
    int w = board[0].size();

    std::vector<std::vector<bool>> visited(h, std::vector<bool>(w, false));
    visited[sgQ.front().y][sgQ.front().x] = true;

    int currTime = 0;
    while(true)
    {
        int n = sgQ.size();
        if(n == 0)
        {
            return -1;
        }

        currTime++;
        FireBFS(board, fireQ);

        while(n--)
        {
            Point curr = sgQ.front();
            sgQ.pop();

            if(IsEdge(h, w, curr.y, curr.x))
            {
                return currTime;
            }

            for(int d = 0; d < 4; ++d)
            {
                int ny = curr.y + dy[d];
                int nx = curr.x + dx[d];

                if(!IsValid(h, w, ny, nx))
                {
                    continue;
                }

                if(visited[ny][nx] || board[ny][nx] != '.')
                {
                    continue;
                }

                sgQ.push({ny, nx});
                visited[ny][nx] = true;
            }
        }
    }
}