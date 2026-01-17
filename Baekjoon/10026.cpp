#include <iostream>
#include <vector>
#include <string>
#include <queue>

inline bool IsValid(int N, int y, int x);

void BFS(const std::vector<std::string>& board, std::vector<std::vector<bool>>& visited,
         int startY, int startX);

int CountAreas(const std::vector<std::string>& board);

const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N = 0;
    std::cin >> N;

    std::vector<std::string> board(N);
    std::vector<std::vector<bool>> visited(N, std::vector<bool>(N, false));

    for(int i = 0; i < N; ++i)
    {
        std::cin >> board[i];
    }

    int nomalCnt = CountAreas(board);

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(board[i][j] == 'R')
            {
                board[i][j] = 'G';
            }
        }
    }

    int rgCnt = CountAreas(board);

    std::cout << nomalCnt << " " << rgCnt;

    return 0;
}

inline bool IsValid(int N, int y, int x)
{
    return 0 <= y && y < N && 0 <= x && x < N;
}

void BFS(const std::vector<std::string>& board, std::vector<std::vector<bool>>& visited,
         int startY, int startX)
{
    int N = board.size();
    
    std::queue<std::pair<int, int>> q;
    q.push({startY, startX});
    visited[startY][startX] = true;

    while(!q.empty())
    {
        std::pair<int, int> curr = q.front();
        q.pop();

        for(int d = 0; d < 4; ++d)
        {
            int ny = curr.first + dy[d];
            int nx = curr.second + dx[d];

            if(!IsValid(N, ny, nx))
            {
                continue;
            }

            if(board[curr.first][curr.second] != board[ny][nx])
            {
                continue;
            }

            if(visited[ny][nx])
            {
                continue;
            }

            q.push({ny, nx});
            visited[ny][nx] = true;
        }
    }
}

int CountAreas(const std::vector<std::string>& board)
{
    int N = board.size();
    int cnt = 0;

    std::vector<std::vector<bool>> visited(N, std::vector<bool>(N, false));

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(!visited[i][j])
            {
                BFS(board, visited, i, j);
                cnt++;
            }
        }
    }
    
    return cnt;
}