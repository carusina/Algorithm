#include <iostream>
#include <algorithm>
#include <cstring>

const int INF = 0x3f3f3f3f;
const int MAX_N = 12;
const int MAX_CORE = 12;

const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

int N;
int board[MAX_N][MAX_N];

int minLineLength;
bool lineBoard[MAX_N][MAX_N];

int numOfCores;
std::pair<int, int> cores[MAX_CORE];

int maxConnectedCores;

inline bool IsBoundary(int y, int x)
{
    return y == 0 || y == N - 1 ||
           x == 0 || x == N - 1;
}

int CanConnectLine(std::pair<int, int> core, int d)
{
    int y = core.first;
    int x = core.second;
    int len = 0;
    
    while(true)
    {
        if(IsBoundary(y, x))
        {
            return len;
        }

        y += dy[d];
        x += dx[d];

        if(lineBoard[y][x] == true)
        {
            return -1;
        }

        len++;
    }
}

void SetLine(int depth, int d, bool flag)
{
    int y = cores[depth].first;
    int x = cores[depth].second;

    while(true)
    {
        y += dy[d];
        x += dx[d];

        lineBoard[y][x] = flag;

        if(IsBoundary(y, x))
        {
            return;
        }
    }
}

void DFS(int depth, int connectedCores, int lineLength)
{
    if(connectedCores + (numOfCores - depth) < maxConnectedCores)
    {
        return;
    }

    if(depth == numOfCores)
    {
        if(connectedCores > maxConnectedCores)
        {
            maxConnectedCores = connectedCores;
            minLineLength = lineLength;
        }
        else if(connectedCores == maxConnectedCores)
        {
            minLineLength = std::min(minLineLength, lineLength);
        }

        return;
    }

    for(int d = 0; d < 4; ++d)
    {
        int len = CanConnectLine(cores[depth], d);

        if(len != -1)
        {
            SetLine(depth, d, true);
            DFS(depth + 1, connectedCores + 1, lineLength + len);
            SetLine(depth, d, false);
        }
    }

    DFS(depth + 1, connectedCores, lineLength);
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int T = 0;
    std::cin >> T;
    for(int test_case = 1; test_case <= T; ++test_case)
    {
        numOfCores = 0;
        maxConnectedCores = 0;
        minLineLength = INF;
        std::memset(lineBoard, 0, sizeof(lineBoard));

        std::cin >> N;

        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                std::cin >> board[i][j];

                if(board[i][j] == 1)
                {
                    lineBoard[i][j] = true;

                    if(!IsBoundary(i, j))
                    {
                        cores[numOfCores++] = {i, j};
                    }
                }
            }
        }
        DFS(0, 0, 0);
        std::cout << "#" << test_case << " " << minLineLength << "\n";
    } // test_case

    return 0;
}