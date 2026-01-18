#include <iostream>
#include <queue>
#include <cstring>

int boards[31][31][31];

const int dz[] = {-1, 1, 0, 0, 0, 0};
const int dy[] = {0, 0, -1, 1, 0, 0};
const int dx[] = {0, 0, 0, 0, -1, 1};

struct Point
{
    int z, y, x;

    const bool operator==(const Point& other) const
    {
        return z == other.z &&
               y == other.y &&
               x == other.x;
    }
};

inline bool IsValid(int L, int R, int C, int z, int y, int x);
int BFS(int L, int R, int C, std::queue<Point>& q, Point dest);

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    while(true)
    {
        int L = 0, R = 0, C = 0;
        std::cin >> L >> R >> C;

        if(L == 0 && R == 0 && C == 0)
        {
            break;
        }

        std::queue<Point> q;
        Point dest;

        memset(&boards[0][0][0], -1, sizeof(boards));
        for(int i = 0; i < L; ++i)
        {
            char c;

            for(int j = 0; j < R; ++j)
            {
                for(int k = 0; k < C; ++k)
                {
                    std::cin >> c;

                    if(c == 'S')
                    {
                        q.push({i, j, k});
                        boards[i][j][k] = 1;
                    }
                    else if(c == 'E')
                    {
                        dest = {i, j, k};
                        boards[i][j][k] = 0;
                    }
                    else if(c == '#')
                    {
                        boards[i][j][k] = -1;
                    }
                    else
                    {
                        boards[i][j][k] = 0;
                    }
                }
            }
        }
        
        int escapedTime = BFS(L, R, C, q, dest);
        if(escapedTime == -1)
        {
            std::cout << "Trapped!\n";
        }
        else
        {
            std::cout << "Escaped in " << escapedTime - 1 << " minute(s).\n";
        }
    }

    return 0;
}

inline bool IsValid(int L, int R, int C, int z, int y, int x)
{
    return 0 <= z && z < L &&
           0 <= y && y < R &&
           0 <= x && x < C;
}

int BFS(int L, int R, int C, std::queue<Point>& q, Point dest)
{
    while(!q.empty())
    {
        Point curr = q.front();
        q.pop();

        if(curr == dest)
        {
            return boards[curr.z][curr.y][curr.x];
        }

        for(int d = 0; d < 6; ++d)
        {
            int nz = curr.z + dz[d];
            int ny = curr.y + dy[d];
            int nx = curr.x + dx[d];

            if(!IsValid(L, R, C, nz, ny, nx))
            {
                continue;
            }

            if(boards[nz][ny][nx] != 0)
            {
                continue;
            }

            boards[nz][ny][nx] = boards[curr.z][curr.y][curr.x] + 1;
            q.push({nz, ny, nx});
        }
    }

    return -1;
}