#include <iostream>
#include <vector>
#include <algorithm>

constexpr int MAX_N = 8;
constexpr int INF = 0x3f3f3f3f;

constexpr int dy[] = {-1, 0, 1, 0};
constexpr int dx[] = {0, 1, 0, -1};

struct CCTV
{
    int y, x, type;
};

int N, M;
int minBlindSpot = INF;
std::vector<CCTV> cctvs;

inline bool IsValid(int y, int x)
{
    return 0 <= y && y < N && 0 <= x && x < M;
}

void DrawVision(int currentBoard[MAX_N][MAX_N], int y, int x, int dir)
{
    dir %= 4; 
    
    while (true)
    {
        y += dy[dir];
        x += dx[dir];

        if (!IsValid(y, x) || currentBoard[y][x] == 6)
        {
            break;
        }

        if (currentBoard[y][x] == 0)
        {
            currentBoard[y][x] = -1; 
        }
    }
}

void SolveDFS(int depth, int currentBoard[MAX_N][MAX_N])
{
    if (depth == cctvs.size())
    {
        int blindSpotCount = 0;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                if (currentBoard[i][j] == 0) blindSpotCount++;
            }
        }
        minBlindSpot = std::min(minBlindSpot, blindSpotCount);
        return;
    }

    int nextBoard[MAX_N][MAX_N];
    int type = cctvs[depth].type;
    int y = cctvs[depth].y;
    int x = cctvs[depth].x;

    for (int dir = 0; dir < 4; ++dir)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                nextBoard[i][j] = currentBoard[i][j];
            }
        }

        if (type == 1)
        {
            DrawVision(nextBoard, y, x, dir);
        }
        else if (type == 2)
        {
            DrawVision(nextBoard, y, x, dir);
            DrawVision(nextBoard, y, x, dir + 2);
        }
        else if (type == 3)
        {
            DrawVision(nextBoard, y, x, dir);
            DrawVision(nextBoard, y, x, dir + 1);
        }
        else if (type == 4)
        {
            DrawVision(nextBoard, y, x, dir);
            DrawVision(nextBoard, y, x, dir + 1);
            DrawVision(nextBoard, y, x, dir + 2);
        }
        else if (type == 5)
        {
            DrawVision(nextBoard, y, x, dir);
            DrawVision(nextBoard, y, x, dir + 1);
            DrawVision(nextBoard, y, x, dir + 2);
            DrawVision(nextBoard, y, x, dir + 3);
        }

        SolveDFS(depth + 1, nextBoard);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int board[MAX_N][MAX_N];

    std::cin >> N >> M;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            std::cin >> board[i][j];
            
            if (1 <= board[i][j] && board[i][j] <= 5)
            {
                cctvs.push_back({i, j, board[i][j]});
            }
        }
    }

    SolveDFS(0, board);

    std::cout << minBlindSpot << "\n";

    return 0;
}