#include <iostream>
#include <vector>
#include <string>
#include <queue>

bool IsValid(int N, int M, int y, int x);
int BFS(const std::vector<std::string>& board);

const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};

struct Point
{
    int y, x;
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N = 0, M = 0;
    std::cin >> N >> M;

    std::vector<std::string> board(N);
    for(int i = 0; i < N; ++i)
    {
        std::cin >> board[i];
    }

    std::cout << BFS(board) << "\n";

    return 0;
}

bool IsValid(int N, int M, int y, int x)
{
    return 0 <= y && y < N && 0 <= x && x < M;
}

int BFS(const std::vector<std::string>& board)
{
    int N = board.size();
    int M = board[0].length();

    std::queue<Point> q;
    std::vector<std::vector<int>> dist(N, std::vector<int>(M, - 1));
    
    dist[0][0] = 1;
    q.push({0, 0});

    while(!q.empty())
    {
        Point curr = q.front();
        q.pop();

        if(curr.y == N - 1 && curr.x == M - 1)
        {
            return dist[curr.y][curr.x];
        }

        for(int d = 0; d < 4; ++d)
        {
            int ny = curr.y + dy[d];
            int nx = curr.x + dx[d];

            if(!IsValid(N, M, ny, nx))
            {
                continue;
            }

            if(board[ny][nx] == '1' && dist[ny][nx] == -1)
            {
                dist[ny][nx] = dist[curr.y][curr.x] + 1;
                q.push({ny, nx});
            }
        }
    }

    return -1;
}