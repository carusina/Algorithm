#include <iostream>
#include <vector>
#include <queue>
#include <climits>

inline bool IsValid(int F, int x);
int BFS(std::vector<int>& floors, int F, int S, int G, int U, int D);

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int F = 0, U = 0, D = 0; // 정보
    int S = 0, G = 0; // 현재 층, 목표 층

    std::cin >> F >> S >> G >> U >> D;
    
    std::vector<int> floors(F + 1, -1);
    floors[0] = INT_MAX;
    floors[S] = 0;

    int result = BFS(floors, F, S, G, U, D);
    if(result == -1)
    {
        std::cout << "use the stairs";
    }
    else
    {
        std::cout << result;
    }

    return 0;
}

inline bool IsValid(int F, int x)
{
    return 1 <= x && x <= F;
}

int BFS(std::vector<int>& floors, int F, int S, int G, int U, int D)
{
    const int dx[2] = {U, -D};

    std::queue<int> q;
    q.push(S);

    while(!q.empty())
    {
        int curr = q.front();
        q.pop();

        if(curr == G)
        {
            return floors[curr];
        }

        for(int d = 0; d < 2; ++d)
        {
            int nx = curr + dx[d];

            if(!IsValid(F, nx))
            {
                continue;
            }

            if(floors[nx] != -1)
            {
                continue;
            }

            floors[nx] = floors[curr] + 1;
            q.push(nx);
        }
    }

    return -1;
}