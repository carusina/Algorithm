#include <iostream>
#include <queue>
#include <algorithm>
#include <climits>

struct Point
{
    int y, x;
};

int board[101][101];
int owner[101][101];
int dist[101][101];

std::queue<Point> q;

const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

inline bool IsValid(int N, int y, int x);
void LabelIslands(int N);
int FindShortestBridge(int N);

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N = 0;
    std::cin >> N;
    
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            std::cin >> board[i][j];
        }
    }

    LabelIslands(N);
    std::cout << FindShortestBridge(N);

    return 0;
}

inline bool IsValid(int N, int y, int x)
{
    return 0 <= y && y < N &&
           0 <= x && x < N;
}

void LabelIslands(int N)
{
    int islandId = 0;
    bool visited[101][101] = {false};

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(board[i][j] == 1 && !visited[i][j])
            {
                islandId++;

                std::queue<Point> labelQ;
                labelQ.push({i, j});
                q.push({i, j});

                visited[i][j] = true;
                owner[i][j] = islandId;
                dist[i][j] = 0;

                while(!labelQ.empty())
                {
                    Point curr = labelQ.front();
                    labelQ.pop();

                    for(int d = 0; d < 4; ++d)
                    {
                        int ny = curr.y + dy[d];
                        int nx = curr.x + dx[d];

                        if(IsValid(N, ny, nx) && !visited[ny][nx] && board[ny][nx] == 1)
                        {
                            visited[ny][nx] = true;

                            owner[ny][nx] = islandId;
                            dist[ny][nx] = 0;

                            labelQ.push({ny, nx});
                            q.push({ny, nx});
                        }
                    }
                }
            }
        }
    }
}

int FindShortestBridge(int N)
{
    int minBridgeDist = INT_MAX;
    
    while(!q.empty())
    {
        Point curr = q.front();
        q.pop();

        if(dist[curr.y][curr.x] * 2 > minBridgeDist)
        {
            break;
        }

        for(int d = 0; d < 4; ++d)
        {
            int ny = curr.y + dy[d];
            int nx = curr.x + dx[d];

            if(!IsValid(N, ny, nx))
            {
                continue;
            }

            if(owner[ny][nx] == 0)
            {
                owner[ny][nx] = owner[curr.y][curr.x];
                dist[ny][nx] = dist[curr.y][curr.x] + 1;
                q.push({ny, nx});
            }
            else if(owner[ny][nx] != owner[curr.y][curr.x])
            {
                int currBridgeDist = dist[ny][nx] + dist[curr.y][curr.x];
                minBridgeDist = std::min(minBridgeDist, currBridgeDist);
            }
        }
    }

    return minBridgeDist;
}