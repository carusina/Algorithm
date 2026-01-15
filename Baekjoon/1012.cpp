#include <iostream>
#include <vector>
#include <queue>

bool IsValid(int N, int M, int y, int x);
void BFS(const std::vector<std::vector<int>>& board, std::vector<std::vector<bool>>& visited, 
         int startY, int startX);

const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T = 0;
    std::cin >> T;

    for(int test_case = 1; test_case <= T; ++test_case)
    {
        int M = 0, N = 0, K = 0;
        std::cin >> M >> N >> K;

        std::vector<std::vector<int>> board(N, std::vector<int>(M, 0));
        std::vector<std::vector<bool>> visited(N, std::vector<bool>(M, false));
        for(int i = 0; i < K; ++i)
        {
            int y = 0, x = 0;
            std::cin >> x >> y;
            board[y][x] = 1;
        }

        int wormCnt = 0;

        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < M; ++j)
            {
                if(board[i][j] == 1 && !visited[i][j])
                {
                    wormCnt++;
                    BFS(board, visited, i, j);
                }
            }
        }

        std::cout << wormCnt << "\n";
    }
}

bool IsValid(int N, int M, int y, int x)
{
    return 0 <= y && y < N && 0 <= x && x < M;
}

void BFS(const std::vector<std::vector<int>>& board, std::vector<std::vector<bool>>& visited, 
         int startY, int startX)
{
    int N = board.size();
    int M = board[0].size();

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

            if(!IsValid(N, M, ny, nx))
            {
                continue;
            }

            if(board[ny][nx] == 0 || visited[ny][nx])
            {
                continue;
            }

            q.push({ny, nx});
            visited[ny][nx] = true;
        }
    }
}