#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};

struct Point
{
    int y, x;
};

inline bool IsValid(int M, int N, int y, int x);
int BFS(std::vector<std::vector<int>>& board, Point start);

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int M = 0, N = 0, K = 0;
    std::cin >> M >> N >> K;

    std::vector<std::vector<int>> board(M, std::vector<int>(N, 0));

    for(int t = 0; t < K; ++t)
    {
        Point p1, p2;
        std::cin >> p1.x >> p1.y >> p2.x >> p2.y;

        for(int i = p1.y; i < p2.y; ++i)
        {
            for(int j = p1.x; j < p2.x; ++j)
            {
                board[i][j] = -1;
            }
        }
    }

    std::vector<int> areas;

    for(int i = 0; i < M; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(board[i][j] == 0)
            {
                board[i][j] = 1;
                areas.push_back(BFS(board, {i, j}));
            }
        }
    }

    sort(areas.begin(), areas.end());

    std::cout << areas.size() << "\n";
    for(int area : areas)
    {
        std::cout << area << " ";
    }

    return 0;
}

inline bool IsValid(int M, int N, int y, int x)
{
    return 0 <= y && y < M &&
           0 <= x && x < N;
}

int BFS(std::vector<std::vector<int>>& board, Point start)
{
    int M = board.size();
    int N = board[0].size();
    
    int area = 1;

    std::queue<Point> q;
    q.push(start);

    while(!q.empty())
    {
        Point curr = q.front();
        q.pop();

        for(int d = 0; d < 4; ++d)
        {
            int ny = curr.y + dy[d];
            int nx = curr.x + dx[d];

            if(!IsValid(M, N, ny, nx))
            {
                continue;
            }

            if(board[ny][nx] != 0)
            {
                continue;
            }

            area++;
            board[ny][nx] = 1;
            q.push({ny, nx});
        }
    }
    
    return area;
}