#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>

const int MAX_N = 15;
const int MAX_M = 15;
const int MAX_ARCHER = 3;

int N, M, D;
int orgBoard[MAX_N][MAX_M];
int archerPos[MAX_ARCHER];

int totalEnemies;
int maxKilled;

void EnemyTurn(int board[][MAX_M], int& currentEnemies)
{
    for(int i = N - 1; i >= 0; --i)
    {
        for(int j = 0; j < M; ++j)
        {
            if(board[i][j] == 1)
            {
                if(i == N - 1)
                {
                    board[i][j] = 0;
                    currentEnemies--;
                }
                else
                {
                    board[i + 1][j] = 1;
                    board[i][j] = 0;
                }
            }
        }
    }
}

void ArcherTurn(int board[][MAX_M], int& currentEnemies, int& killCnt)
{
    std::set <std::pair<int, int>> targets;

    for(int k = 0; k < MAX_ARCHER; ++k)
    {
        int minY = -1, minX = -1;
        int minDist = 0x3f3f3f3f;

        for(int j = 0; j < M; ++j)
        {
            for(int i = N - 1; i >= N - D; --i)
            {
                if(i < 0) continue;

                if(board[i][j] == 1)
                {
                    int dist = std::abs(N - i) + std::abs(archerPos[k] - j);
                    
                    if(dist <= D)
                    {
                        if(dist < minDist)
                        {
                            minDist = dist;
                            minY = i;
                            minX = j;
                        }
                    }
                }
            }
        }

        if(minY != -1)
        {
            targets.insert({minY, minX});
        }
    }

    for(std::pair<int, int> pos : targets)
    {
        board[pos.first][pos.second] = 0;
        currentEnemies--;
        killCnt++;
    }
}

void DFS(int depth, int idx)
{
    if(depth == 3)
    {
        int copyBoard[MAX_N][MAX_M];
        std::memcpy(copyBoard, orgBoard, sizeof(orgBoard));

        int killCnt = 0;
        int currentEnemies = totalEnemies;
        while(true)
        {
            if(currentEnemies == 0)
            {
                maxKilled = std::max(maxKilled, killCnt);
                return;
            }

            ArcherTurn(copyBoard, currentEnemies, killCnt);
            EnemyTurn(copyBoard, currentEnemies);
        }
    }
    
    for(int i = idx; i < M; ++i)
    {
        archerPos[depth] = i;
        DFS(depth + 1, i + 1);
    }
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N >> M >> D;
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < M; ++j)
        {
            std::cin >> orgBoard[i][j];

            if(orgBoard[i][j] == 1)
            {
                totalEnemies++;
            }
        }
    }

    DFS(0, 0);
    std::cout << maxKilled;

    return 0;
}