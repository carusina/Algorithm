#include <iostream>
#include <vector>
#include <queue>

bool IsValid(int n, int m, int y, int x);
int BFS(const std::vector<std::vector<int>>& board, std::vector<std::vector<bool>>& visited,
        int startY, int startX);

const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n = 0, m = 0;
    std::cin >> n >> m;

    std::vector<std::vector<int>> board(n, std::vector<int>(m, 0));
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            std::cin >> board[i][j];
        }
    }

    int numPicture = 0;
    int maxArea = 0;

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            if(board[i][j] == 1 && !visited[i][j])
            {
                numPicture++;

                int area = BFS(board, visited, i, j);
                maxArea = maxArea > area ? maxArea : area;
            }
        }
    }

    std::cout << numPicture << "\n" << maxArea << "\n";

    return 0;
}

bool IsValid(int n, int m, int y, int x)
{
    return 0 <= y && y < n && 0 <= x && x < m;
}

int BFS(const std::vector<std::vector<int>>& board, std::vector<std::vector<bool>>& visited,
        int startY, int startX)
{
    int n = board.size();
    int m = board[0].size();

    std::queue<std::pair<int, int>> q;

    visited[startY][startX] = true;
    q.push({startY, startX});

    int area = 0;

    while(!q.empty())
    {
        std::pair<int, int> curr = q.front();
        q.pop();

        area++;

        for(int d = 0; d < 4; ++d)
        {
            int ny = curr.first + dy[d];
            int nx = curr.second + dx[d];

            if(!IsValid(n, m, ny, nx))
            {
                continue;
            }
            
            if(visited[ny][nx] || board[ny][nx] == 0)
            {
                continue;
            }

            visited[ny][nx] = true;
            q.push({ny, nx});
        }
    }

    return area;
}