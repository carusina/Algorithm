#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <climits>

const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};

struct Point
{
    int y, x;
};

inline bool IsValid(int N, int y, int x);
void BFS(const std::vector<std::vector<int>>& board, std::vector<std::vector<bool>>& visited,
         Point start, int rainHeight);

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N = 0;
    std::cin >> N;

    std::vector<std::vector<int>> board(N, std::vector<int>(N, 0));
    std::vector<std::vector<bool>> visited(N, std::vector<bool>(N, false));

    std::set<int> heights;
    heights.insert(0);

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            std::cin >> board[i][j];
            heights.insert(board[i][j]);
        }
    }

    int maxAreaCnt = 0;

    for(int height : heights)
    {
        int areaCnt = 0;
        
        for(int i = 0; i < N; ++i)
        {
            std::fill(visited[i].begin(), visited[i].end(), false);
        }

        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                if(!visited[i][j] && board[i][j] > height)
                {
                    BFS(board, visited, {i, j}, height);
                    areaCnt++;
                }
            }
        }

        maxAreaCnt = areaCnt > maxAreaCnt ? areaCnt : maxAreaCnt;
    }

    std::cout << maxAreaCnt;

    return 0;
}

inline bool IsValid(int N, int y, int x)
{
    return 0 <= y && y < N &&
           0 <= x && x < N;
}

void BFS(const std::vector<std::vector<int>>& board, std::vector<std::vector<bool>>& visited,
         Point start, int rainHeight)
{
    int N = board.size();

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

            if(!IsValid(N, ny, nx))
            {
                continue;
            }

            if(visited[ny][nx] || board[ny][nx] <= rainHeight)
            {
                continue;
            }

            q.push({ny, nx});
            visited[ny][nx] = true;
        }
    }
}