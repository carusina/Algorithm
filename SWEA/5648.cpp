#include <iostream>

const int MAX_N = 1001;
const int MAX_SIZE = 4001;
const int OFFSET = 2000;

const int dy[] = {1, -1, 0, 0};
const int dx[] = {0, 0, -1, 1};

struct Atom
{
    int y, x;
    int dir;
    int energy;
};

int N;
Atom atoms[MAX_N];
int energyMap[MAX_SIZE][MAX_SIZE];

inline bool IsValid(int y, int x)
{
    return 0 <= y && y < MAX_SIZE &&
           0 <= x && x < MAX_SIZE;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int T = 0;
    std::cin >> T;
    for(int test_case = 1; test_case <= T; ++test_case)
    {
        int totalReleasedEnergy = 0;

        std::cin >> N;
        for(int i = 0; i < N; ++i)
        {
            int x, y, dir, K;
            std::cin >> x >> y >> dir >> K;

            atoms[i] = {(y * 2) + OFFSET, (x * 2) + OFFSET, dir, K};
        }

        for(int time = 0; time < MAX_SIZE; ++time)
        {
            for(int i = 0; i < N; ++i)
            {
                if(atoms[i].energy > 0)
                {
                    atoms[i].y += dy[atoms[i].dir];
                    atoms[i].x += dx[atoms[i].dir];

                    if(!IsValid(atoms[i].y, atoms[i].x))
                    {
                        atoms[i].energy = 0;
                        continue;
                    }

                    energyMap[atoms[i].y][atoms[i].x] += atoms[i].energy; 
                }
            }

            int aliveCnt = 0;

            for(int i = 0; i < N; ++i)
            {
                if(atoms[i].energy > 0)
                {
                    aliveCnt++;

                    int y = atoms[i].y;
                    int x = atoms[i].x;

                    if(energyMap[y][x] != atoms[i].energy)
                    {
                        totalReleasedEnergy += atoms[i].energy;
                        energyMap[y][x] = 0;
                        atoms[i].energy = 0;
                    }
                }
            }

            if(aliveCnt == 0)
            {
                break;
            }

            for(int i = 0; i < N; ++i)
            {
                if(atoms[i].energy > 0)
                {
                    int y = atoms[i].y;
                    int x = atoms[i].x;
                    energyMap[y][x] = 0;
                }
            }
        }
        std::cout << "#" << test_case << " " << totalReleasedEnergy << "\n";
    }

    return 0;
}