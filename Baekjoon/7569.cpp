#include <iostream>
#include <vector>
#include <queue>

struct Point
{
    int z, y, x;
};


inline bool IsValid(int H, int N, int M, int z, int y, int x);
void BFS(std::vector<std::vector<std::vector<int>>>& board, std::queue<Point>& q,
         int& minDay, int& unripedTomatoes);

const int dz[6] = {-1, 1, 0, 0, 0, 0};
const int dy[6] = {0, 0, -1, 1, 0, 0};
const int dx[6] = {0, 0, 0, 0, -1, 1};

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int M = 0, N = 0, H = 0;
    std::cin >> M >> N >> H;

    int unripedTomatoes = 0;
    
    std::vector<std::vector<std::vector<int>>> board(H, std::vector<std::vector<int>>(N, std::vector<int>(M, 0)));
    std::queue<Point> q;

    for(int i = 0; i < H; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            for(int k = 0; k < M; ++k)
            {
                std::cin >> board[i][j][k];

                if(board[i][j][k] == 0)
                {
                    unripedTomatoes++;
                }
                else if(board[i][j][k] == 1)
                {
                    q.push({i, j, k});
                }
            }
        }
    }

    if(unripedTomatoes == 0)
    {
        std::cout << 0;
        return 0;
    }

    int minDay = 0;
    
    BFS(board, q, minDay, unripedTomatoes);

    if(unripedTomatoes > 0)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << minDay - 1;
    }

    return 0;
}

inline bool IsValid(int H, int N, int M, int z, int y, int x)
{
    return 0 <= z && z < H &&
           0 <= y && y < N &&
           0 <= x && x < M;
}

void BFS(std::vector<std::vector<std::vector<int>>>& board, std::queue<Point>& q,
         int& minDay, int& unripedTomatoes)
{
    int H = board.size();
    int N = board[0].size();
    int M = board[0][0].size();

    while(!q.empty())
    {
        Point curr = q.front();
        q.pop();

        if(board[curr.z][curr.y][curr.x] > minDay)
        {
            minDay = board[curr.z][curr.y][curr.x];
        }

        for(int d = 0; d < 6; ++d)
        {
            int nz = curr.z + dz[d];
            int ny = curr.y + dy[d];
            int nx = curr.x + dx[d];

            if(!IsValid(H, N, M, nz, ny, nx))
            {
                continue;
            }

            if(board[nz][ny][nx] != 0)
            {
                continue;
            }

            board[nz][ny][nx] = board[curr.z][curr.y][curr.x] + 1;
            q.push({nz, ny, nx});
            
            unripedTomatoes--;
        }
    }
}