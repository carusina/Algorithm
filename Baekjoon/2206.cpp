#include <iostream>
#include <vector>
#include <queue>
#include <string>

std::string map[1001];
int dist[1001][1001][2];

const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

struct Point
{
    int y, x;
    int broken;
};

inline bool IsValid(int N, int M, int y, int x);
int BFS(int N, int M);

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N = 0, M = 0;
    std::cin >> N >> M;
    
    for(int i = 0; i < N; ++i)
    {
        std::cin >> map[i];
    }

    std::cout << BFS(N, M);

    return 0;
}

inline bool IsValid(int N, int M, int y, int x)
{
    return 0 <= y && y < N &&
           0 <= x && x < M;
}

int BFS(int N, int M)
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
            return dist[curr.y][curr.x][curr.broken];
        }

        for(int d = 0; d < 4; ++d)
        {
            int ny = curr.y + dy[d];
            int nx = curr.x + dx[d];

            if(!IsValid(N, M, ny, nx))
            {
                continue;
            }

            int nbroken = curr.broken + (map[ny][nx] - '0');

            if(nbroken > 1)
            {
                continue;
            }

            if(dist[ny][nx][nbroken] > 0)
            {
                continue;
            }

            dist[ny][nx][nbroken] = dist[curr.y][curr.x][curr.broken] + 1;
            q.push({ny, nx, nbroken});
        }
    }

    return -1;
}