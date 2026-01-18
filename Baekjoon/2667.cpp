#include <iostream>
#include <vector>
#include <algorithm>

const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};

struct Point
{
    int y, x;
};

inline bool IsValid(int N, Point pos);
void DFS(std::vector<std::string>& board, int N, Point start, int& area);

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N = 0;
    std::cin >> N;

    std::vector<std::string> board(N);
    for(int i = 0; i < N; ++i)
    {
        std::cin >> board[i];
    }

    std::vector<int> areas;
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(board[i][j] == '1')
            {
                int area = 0;

                DFS(board, N, {i, j}, area);
                areas.push_back(area);
            }
        }
    }

    sort(areas.begin(), areas.end());

    std::cout << areas.size() << "\n";
    for(int area : areas)
    {
        std::cout << area << "\n";
    }

    return 0;
}

inline bool IsValid(int N, Point pos)
{
    return 0 <= pos.y && pos.y < N &&
           0 <= pos.x && pos.x < N;
}

void DFS(std::vector<std::string>& board, int N, Point start, int& area)
{
    if(!IsValid(N, start))
    {
        return;
    }

    if(board[start.y][start.x] != '1')
    {
        return;
    }

    board[start.y][start.x] = '0';
    area++;

    for(int d = 0; d < 4; ++d)
    {
        int ny = start.y + dy[d];
        int nx = start.x + dx[d];

        DFS(board, N, {ny, nx}, area);
    }
}