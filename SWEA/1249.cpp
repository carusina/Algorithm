#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

constexpr int MAX_N = 101;

constexpr int dy[] = {-1, 1, 0, 0};
constexpr int dx[] = {0, 0, -1, 1};

struct Point
{
    int y, x;
    int cost;

    const bool operator>(const Point& other) const
    {
        return cost > other.cost;
    }
};

int N;
int board[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];

inline bool IsValid(int y, int x)
{
    return 0 <= y && y < N &&
           0 <= x && x < N;
}

void BFS()
{
    std::memset(dist, 0x3f3f3f3f, sizeof(dist));
    dist[0][0] = 0;

    std::priority_queue<Point, std::vector<Point>, std::greater<Point>> pq;
    pq.push({0, 0, 0});

    while(!pq.empty())
    {
        Point curr = pq.top();
        pq.pop();

        if(curr.cost > dist[curr.y][curr.x])
        {
            continue;
        }

        if(curr.y == N - 1 && curr.x == N - 1)
        {
            return;
        }

        for(int d = 0; d < 4; ++d)
        {
            int ny = curr.y + dy[d];
            int nx = curr.x + dx[d];

            if(!IsValid(ny, nx))
            {
                continue;
            }

            int nc = curr.cost + board[ny][nx];
            if(nc >= dist[ny][nx])
            {
                continue;
            }

            dist[ny][nx] = nc;
            pq.push({ny, nx, nc});
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int T = 0;
    std::cin >> T;
    for(int test_case = 1; test_case <= T; ++test_case)
    {  
        std::cin >> N;
        for(int i = 0; i < N; ++i)
        {
            std::string row;
            std::cin >> row;

            for(int j = 0; j < N; ++j)
            {
                board[i][j] = row[j] - '0';
            }
        }

        BFS();
        std::cout << "#" << test_case << " " << dist[N - 1][N - 1] << "\n";
    }

    return 0;
}