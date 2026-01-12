#include <iostream>
#include <vector>
#include <string>
#include <queue>
 
bool IsValid(int N, int y, int x);
int CountSurroundingMines(const std::vector<std::string>& board, int N, int y, int x);
void ClickZero(const std::vector<std::string>& board, const std::vector<std::vector<int>>& mine_counts,
               std::vector<std::vector<bool>>& visited, int N, int startY, int startX);
int Solution(const std::vector<std::string>& board);
 
const int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
 
int main()
{
    int T = 0;
    std::cin >> T;
 
    for(int test_case = 1; test_case <= T; ++test_case)
    {
        int N = 0;
        std::cin >> N;
 
        std::vector<std::string> board(N);
        for(int i = 0; i < N; ++i)
        {
            std::cin >> board[i];
        }
 
        std::cout << "#" << test_case << " " << Solution(board) << "\n";
    }
 
    return 0;
}
 
bool IsValid(int N, int y, int x)
{
    return 0 <= y && y < N && 0 <= x && x < N;
}
 
int CountSurroundingMines(const std::vector<std::string>& board, int N, int y, int x)
{
    int count = 0;
 
    for(int d = 0; d < 8; ++d)
    {
        int ny = y + dy[d];
        int nx = x + dx[d];
        if(IsValid(N, ny, nx) && board[ny][nx] == '*')
        {
            count++;
        }
    }
 
    return count;
}
 
void ClickZero(const std::vector<std::string>& board, const std::vector<std::vector<int>>& mine_counts,
               std::vector<std::vector<bool>>& visited, int N, int startY, int startX)
{
    std::queue<std::pair<int, int>> q;
    q.push({startY, startX});
    visited[startY][startX] = true;
 
    while(!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
 
        for(int d = 0; d < 8; ++d)
        {
            int ny = y + dy[d];
            int nx = x + dx[d];
 
            if(IsValid(N, ny, nx) && !visited[ny][nx] && board[ny][nx] == '.')
            {
                visited[ny][nx] = true;
 
                if(mine_counts[ny][nx] == 0)
                {
                    q.push({ny, nx});
                }
            }
        }
    }
}
 
int Solution(const std::vector<std::string>& board)
{
    int clicks = 0;
     
    int N = board.size();
    std::vector<std::vector<int>> mine_counts(N, std::vector<int>(N, 0));
    std::vector<std::vector<bool>> visited(N, std::vector<bool>(N, false));
 
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(board[i][j] == '.')
            {
                mine_counts[i][j] = CountSurroundingMines(board, N, i, j);
            }
        }
    }
 
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(board[i][j] == '.' && !visited[i][j] && mine_counts[i][j] == 0)
            {
                clicks++;
                ClickZero(board, mine_counts, visited, N, i, j);
            }
        }
    }
 
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(board[i][j] == '.' && !visited[i][j])
            {
                clicks++;
                visited[i][j] = true;
            }
        }
    }
 
    return clicks; 
}