#include <iostream>

const int MAX_N = 50;
const int NUM_PLAYERS = 9;

int N;
int inningInfo[MAX_N + 1][NUM_PLAYERS + 1];
int batters[NUM_PLAYERS + 1];
bool participated[NUM_PLAYERS + 1];

int maxScore;

int PlayInning(const int batters[], int& startBatter, int inning)
{
    int outCnt = 0;
    int score = 0;
    bool base[4] = {false};

    while(true)
    {
        int player = batters[startBatter++];
        if(startBatter > NUM_PLAYERS)
        {
            startBatter = 1;
        }

        int batResult = inningInfo[inning][player];
        
        switch (batResult)
        {
        case 0:
            outCnt++;
            if(outCnt == 3)
            {
                return score;
            }
            break;
        case 4:
            for(int i = 1; i <= 3; ++i)
            {
                if(base[i])
                {
                    score++;
                    base[i] = false;
                }
            }
            score++;
            break;
        default:
            for(int i = 0; i < batResult; ++i)
            {
                for(int j = 3; j >= 1; --j)
                {
                    if(base[j])
                    {
                        if(j == 3)
                        {
                            score++;
                        }
                        else
                        {
                            base[j + 1] = true;
                        }
                        base[j] = false;
                    }
                }
            }
            base[batResult] = true;
            break;
        }
    }

    return score;
}

int PlayGame(const int batters[])
{
    int score = 0;
    int startBatter = 1;

    for(int i = 1; i <= N; ++i)
    {
        score += PlayInning(batters, startBatter, i);
    }
    
    return score;
}

void DFS(int depth)
{
    if(depth > NUM_PLAYERS)
    {
        int score = PlayGame(batters);
        maxScore = std::max(maxScore, score);
        return;
    }

    if(depth == 4)
    {
        DFS(depth + 1);
        return;
    }

    for(int player = 2; player <= NUM_PLAYERS; ++player)
    {
        if(participated[player] == false)
        {
            participated[player] = true;
            batters[depth] = player;
            DFS(depth + 1);
            participated[player] = false;
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> N;

    for(int i = 1; i <= N; ++i)
    {
        for(int j = 1; j <= NUM_PLAYERS; ++j)
        {
            std::cin >> inningInfo[i][j];
        }
    }

    batters[4] = 1;
    participated[1] = true;
    DFS(1);
    std::cout << maxScore;

    return 0;
}