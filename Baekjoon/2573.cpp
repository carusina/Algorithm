#include <iostream>
#include <queue>
#include <cstring>

struct Point
{
    int y, x;
};

int board[301][301];
int meltAmount[301][301];
bool visited[301][301];

const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

inline bool IsValid(int N, int M, int y, int x);
void BFS(int N, int M, Point start);
int CountIce(int N, int M);
void Melt(int N, int M);

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N = 0, M = 0;
    std::cin >> N >> M;
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < M; ++j)
        {
            std::cin >> board[i][j];
        }
    }

    int year = 0;
    while(true)
    {
        int cnt = CountIce(N, M);

        if(cnt == 0)
        {
            std::cout << 0;
            return 0;
        }
        
        if(cnt >= 2)
        {
            std::cout << year;
            return 0;
        }

        Melt(N, M);
        year++;
    }

    return 0;
}

inline bool IsValid(int N, int M, int y, int x)
{
    return 0 <= y && y < N &&
           0 <= x && x < M;
}

void BFS(int N, int M, Point start)
{
    std::queue<Point> q;
    q.push(start);
    visited[start.y][start.x] = true;

    while(!q.empty())
    {
        Point curr = q.front();
        q.pop();

        for(int d = 0; d < 4; ++d)
        {
            int ny = curr.y + dy[d];
            int nx = curr.x + dx[d];

            if(!IsValid(N, M, ny, nx))
            {
                continue;
            }

            if(board[ny][nx] <= 0 || visited[ny][nx])
            {
                continue;
            }

            q.push({ny, nx});
            visited[ny][nx] = true;
        }
    }
}

int CountIce(int N, int M)
{
    memset(visited, false, sizeof(visited));
    int cnt = 0;

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < M; ++j)
        {
            if(board[i][j] > 0 && !visited[i][j])
            {
                BFS(N, M, {i, j});
                cnt++;
            }
        }
    }

    return cnt;
}

void Melt(int N, int M)
{
    memset(meltAmount, 0, sizeof(meltAmount));

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < M; ++j)
        {
            if(board[i][j] == 0)
            {
                continue;
            }

            int seaCnt = 0;
            for(int d = 0; d < 4; ++d)
            {
                int ny = i + dy[d];
                int nx = j + dx[d];

                if(!IsValid(N, M, ny, nx))
                {
                    continue;
                }

                if(board[ny][nx] == 0)
                {
                    seaCnt++;
                }
            }

            meltAmount[i][j] = seaCnt;
        }
    }

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < M; ++j)
        {
            if(board[i][j] > 0)
            {
                board[i][j] = std::max(0, board[i][j] - meltAmount[i][j]);
            }
        }
    }
}