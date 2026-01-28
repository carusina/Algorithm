#include <iostream>
#include <string>
#include <queue>

std::string board[1001];
int dist[1001][1001][11][2];

const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

struct Point
{
    int y, x, k;
    int day;
};

inline bool IsValid(int N, int M, int y, int x);
int BFS(int N, int M, int K);

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N = 0, M = 0, K = 0;
    std::cin >> N >> M >> K;

    for(int i = 0; i < N; ++i)
    {
       std::cin >> board[i];
    }

    std::cout << BFS(N, M, K);

    return 0;
}

inline bool IsValid(int N, int M, int y, int x)
{
    return 0 <= y && y < N &&
           0 <= x && x < M;
}

int BFS(int N, int M, int K)
{
    std::queue<Point> q;
    q.push({0, 0, 0, 1});
    dist[0][0][0][1] = 1;

    while(!q.empty())
    {
        Point curr = q.front();
        q.pop();

        if(curr.y == N - 1 && curr.x == M - 1)
        {
            return dist[curr.y][curr.x][curr.k][curr.day];
        }

        for(int d = 0; d < 4; ++d)
        {
            int ny = curr.y + dy[d];
            int nx = curr.x + dx[d];
            int nk = curr.k;
            int nDay = 1 - curr.day;

            if(!IsValid(N, M, ny, nx))
            {
                continue;
            }

            if(board[ny][nx] == '1')
            {
                nk++;

                if(nk <= K && curr.day == 1)
                {
                    if(dist[ny][nx][nk][nDay] == 0)
                    {
                        q.push({ny, nx, nk, nDay});
                        dist[ny][nx][nk][nDay] = dist[curr.y][curr.x][curr.k][curr.day] + 1;
                    }
                }
            }
            else
            {
                if(dist[ny][nx][nk][nDay] == 0)
                {
                    q.push({ny, nx, nk, nDay});
                    dist[ny][nx][nk][nDay] = dist[curr.y][curr.x][curr.k][curr.day] + 1;
                }
            }
        }

        if(curr.day == 0)
        {
            int nDay = 1;
            if(dist[curr.y][curr.x][curr.k][nDay] == 0)
            {
                q.push({curr.y, curr.x, curr.k, nDay});
                dist[curr.y][curr.x][curr.k][nDay] = dist[curr.y][curr.x][curr.k][curr.day] + 1;
            }
        }
    }

    return -1;
}