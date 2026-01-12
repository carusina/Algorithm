#include <iostream>
#include <vector>
#include <queue>
#include <climits>

bool IsValid(int N, int y, int x);
int Solution(const std::vector<std::vector<int>>& board);

const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};

// 상태를 저장할 구조체 (시간이 작은 게 우선순위가 높아야 함)
struct Node
{
    int time;
    int y;
    int x;

    // Min-Heap을 위한 연산자 오버로딩 (시간이 작은 순서)
    bool operator>(const Node& other) const
    {
        return time > other.time;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T = 0;
    std::cin >> T;

    for(int test_case = 1; test_case <= T; ++test_case)
    {
        int N = 0;
        std::cin >> N;
        
        std::vector<std::vector<int>> board(N, std::vector<int>(N, 0));
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                std::cin >> board[i][j];
            }
        }

        std::cout << "#" << test_case << " " << Solution(board) << "\n";
    }

    return 0;
}

bool IsValid(int N, int y, int x)
{
    return 0 <= y && y < N && 0 <= x && x < N;
}

int Solution(const std::vector<std::vector<int>>& board)
{
    int startY = 0, startX = 0;
    int destY = 0, destX = 0;
    std::cin >> startY >> startX;
    std::cin >> destY >> destX;

    int N = board.size();
    
    // [다익스트라 준비]
    // dist[y][x]: (y, x)까지 가는 최소 시간 기록
    std::vector<std::vector<int>> dist(N, std::vector<int>(N, INT_MAX));

    // 우선순위 큐 선언 (greater를 써서 오름차순 정렬 -> 시간이 짧은 게 top으로)
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

    // 시작점 초기화
    dist[startY][startX] = 0;
    pq.push({0, startY, startX});

    while(!pq.empty())
    {
        int time = pq.top().time;
        int y = pq.top().y;
        int x = pq.top().x;
        pq.pop();

        // 목적지 도착! (PQ를 썼으므로 가장 먼저 도착한 게 최단 시간임이 보장됨)
        if(y == destY && x == destX)
        {
            return time;
        }

        // 이미 더 짧은 경로로 방문한 적이 있다면 스킵
        if(dist[y][x] < time)
        {
            continue;
        }

        for(int d = 0; d < 4; ++d)
        {
            int ny = y + dy[d];
            int nx = x + dx[d];

            if(!IsValid(N, ny, nx))
            {
                continue;
            }

            if(board[ny][nx] == 1)
            {
                continue;
            }
            
            int nextTime = 0;

            if(board[ny][nx] == 0)
            {
                nextTime = time + 1;
            }
            else if(board[ny][nx] == 2)
            {
                if(time % 3 == 2)
                {
                    nextTime = time + 1;
                }
                else if(time % 3 == 1)
                {
                    nextTime = time + 2;
                }
                else
                {
                    nextTime = time + 3;
                }
            }

            // [최단 거리 갱신]
            // 새로 계산한 시간이 기존에 알고 있던 시간보다 짧으면 갱신
            if(nextTime < dist[ny][nx])
            {
                dist[ny][nx] = nextTime;
                pq.push({nextTime, ny, nx});
            }
        }
    }

    return -1;
}