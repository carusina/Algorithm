#include <iostream>
#include <vector>
#include <queue>

const int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dx[8] = {-2, -1, 1, 2, -2, -1, 1, 2};

struct Point
{
    int y, x;
};

inline bool IsValid(int I, int y, int x);
int BFS(std::vector<std::vector<int>>& board, std::queue<Point>& q, Point dest);

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int T = 0;
    std::cin >> T;

    for(int test_case = 1; test_case <= T; ++test_case)
    {
        int I = 0;
        std::cin >> I;

        Point start, dest;
        std::cin >> start.y >> start.x;
        std::cin >> dest.y >> dest.x;

        std::vector<std::vector<int>> board(I, std::vector<int>(I, -1));
        
        std::queue<Point> q;
        q.push(start);
        board[start.y][start.x] = 0;

        std::cout << BFS(board, q, dest) << "\n";
    }

    return 0;
}

inline bool IsValid(int I, int y, int x)
{
    return 0 <= y && y < I &&
           0 <= x && x < I;
}

int BFS(std::vector<std::vector<int>>& board, std::queue<Point>& q, Point dest)
{
    int I = board.size();

    while(!q.empty())
    {
        Point curr = q.front();
        q.pop();

        if(curr.y == dest.y && curr.x == dest.x)
        {
            return board[curr.y][curr.x];
        }

        for(int d = 0; d < 8; ++d)
        {
            int ny = curr.y + dy[d];
            int nx = curr.x + dx[d];

            if(!IsValid(I, ny, nx))
            {
                continue;
            }

            if(board[ny][nx] != -1)
            {
                continue;
            }

            board[ny][nx] = board[curr.y][curr.x] + 1;
            q.push({ny, nx});
        }
    }

    return -1;
}