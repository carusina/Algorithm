// https://www.codetree.ai/ko/frequent-problems/hsat/problems/next-generation-ITS/description

#define MAX_N 100
#define MAX_SIGN 12

#include <iostream>
#include <queue>
#include <vector>

// 상=0, 하=1, 좌=2, 우=3
constexpr int dy[] = { -1, 1, 0, 0 };
constexpr int dx[] = { 0, 0, -1, 1 };

struct Pos {
    int y, x;
    int dir;
};

const std::vector<int> signals[MAX_SIGN + 1] = {
    {},
    {3, 0, 1}, // 1:  우진입 → 우,상,하
    {0, 3, 2}, // 2:  상진입 → 상,우,좌
    {2, 0, 1}, // 3:  좌진입 → 좌,상,하
    {1, 3, 2}, // 4:  하진입 → 하,우,좌
    {3, 0},    // 5:  우진입 → 우,상
    {0, 2},    // 6:  상진입 → 상,좌
    {2, 1},    // 7:  좌진입 → 좌,하
    {1, 3},    // 8:  하진입 → 하,우
    {3, 1},    // 9:  우진입 → 우,하
    {0, 3},    // 10: 상진입 → 상,우
    {2, 0},    // 11: 좌진입 → 좌,상
    {1, 2},    // 12: 하진입 → 하,좌
};

int N, T;
int grid[MAX_N + 1][MAX_N + 1][4];

bool vis[MAX_N + 1][MAX_N + 1][4][4];
bool visited[MAX_N + 1][MAX_N + 1];

inline bool IsValid(int y, int x) {
    return 1 <= y && y <= N && 1 <= x && x <= N;
}

int BFS() {
    std::queue<Pos> q;

    vis[1][1][0][0] = true;
    visited[1][1] = true;
    q.push({ 1, 1, 0 });

    for (int currT = 0; currT < T && !q.empty(); currT++)
    {
        int onSign = currT % 4;

        int qSize = q.size();
        while (qSize--)
        {
            Pos curr = q.front();
            q.pop();

            int currSign = grid[curr.y][curr.x][onSign];

            if (signals[currSign][0] == curr.dir)
            {
                for (int dir : signals[currSign])
                {
                    int ny = curr.y + dy[dir];
                    int nx = curr.x + dx[dir];

                    if (IsValid(ny, nx) && !vis[ny][nx][onSign][dir])
                    {
                        vis[ny][nx][onSign][dir] = true;
                        visited[ny][nx] = true;
                        q.push({ ny, nx, dir });
                    }
                }
            }
        }
    }

    int passedCross = 0;
    for (int y = 1; y <= N; ++y)
    {
        for (int x = 1; x <= N; ++x)
        {
            if (visited[y][x])
            {
                passedCross++;
            }
        }
    }

    return passedCross;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N >> T;

    for (int r = 1; r <= N; ++r)
    {
        for (int c = 1; c <= N; ++c)
        {
            std::cin >> grid[r][c][0] >> grid[r][c][1] >> grid[r][c][2] >> grid[r][c][3];
        }
    }
        
    std::cout << BFS();

    return 0;
}