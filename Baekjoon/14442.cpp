#include <iostream>
#include <string>
#include <queue>

std::string board[1001];
int dist[1001][1001][11];
int N, M, K;

const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

struct Point
{
    int y, x;
    int k;
};

inline bool IsValid(int y, int x);
int BFS();

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N >> M >> K;
    
    for(int i = 0; i < N; ++i)
    {
        std::cin >> board[i];
    }

    std::cout << BFS();

    return 0;
}

inline bool IsValid(int y, int x)
{
    return 0 <= y && y < N &&
           0 <= x && x < M;
}

int BFS()
{
    std::queue<Point> q;
    q.push({0, 0, 0});
    dist[0][0][0] = 1;

    while(!q.empty())
    {
        Point curr = q.front();
        q.pop();

        if(curr.y == N - 1 && curr.x == M - 1)
        {
            return dist[curr.y][curr.x][curr.k];
        }

        for(int d = 0; d < 4; ++d)
        {
            int ny = curr.y + dy[d];
            int nx = curr.x + dx[d];
            int nk = curr.k;

            if(!IsValid(ny, nx))
            {
                continue;
            }

            if(board[ny][nx] == '1')
            {
                nk++;
            }

            if(nk > K || dist[ny][nx][nk] != 0)
            {
                continue;
            }

            q.push({ny, nx, nk});
            dist[ny][nx][nk] = dist[curr.y][curr.x][curr.k] + 1;
        }
    }

    return -1;
}