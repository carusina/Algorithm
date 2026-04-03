// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/rudolph-rebellion/description

#define MAX_N 50
#define MAX_SANTA 30
#define RETIRE 0x3f3f3f3f
#define RUDOLF -1

#include <iostream>

struct Pos {
    int y, x;
};

struct Santa {
    int id;
    Pos pos;
    int stunUntil;
    int score;
};

// 상 우 하 좌 좌상 우상 좌하 우하
constexpr int dy[] = { -1, 0, 1, 0, -1, -1, 1, 1 };
constexpr int dx[] = { 0, 1, 0, -1, -1, 1, -1, 1 };

int boardSize;
int board[MAX_N + 1][MAX_N + 1];

int maxTurn;
int currTurn;

int powerRudolf;
Pos rudolf;

int santaCount;
int powerSanta;
Santa santas[MAX_SANTA + 1];

inline int GetDist(Pos p1, Pos p2) {
    int deltaY = p1.y - p2.y;
    int deltaX = p1.x - p2.x;

    return (deltaY * deltaY) + (deltaX * deltaX);
}

inline bool IsValid(int y, int x) {
    return 1 <= y && y <= boardSize &&
           1 <= x && x <= boardSize;
}

void Interact(int santaID, int y, int x, int moveY, int moveX) {
    if (!IsValid(y, x))
    {
        santas[santaID].stunUntil = RETIRE;
        return;
    }

    if (board[y][x] != 0)
    {
        int nextSantaID = board[y][x];
        Interact(nextSantaID, y + moveY, x + moveX, moveY, moveX);
    }

    board[y][x] = santaID;
    santas[santaID].pos = { y, x };
}

void Collision(int santaID, int y, int x, int moveY, int moveX, int power) {
    santas[santaID].score += power;
    santas[santaID].stunUntil = currTurn + 1;

    int ny = y + (moveY * power);
    int nx = x + (moveX * power);

    Interact(santaID, ny, nx, moveY, moveX);
}

void RudolfTurn() {
    int targetSantaID = 0;
    int minDist = 0x3f3f3f3f;

    for (int s = 1; s <= santaCount; ++s)
    {
        if (santas[s].stunUntil == RETIRE)
        {
            continue;
        }

        int dist = GetDist(rudolf, santas[s].pos);
        if (dist < minDist)
        {
            minDist = dist;
            targetSantaID = s;
        }
        else if (dist == minDist)
        {
            if (santas[s].pos.y > santas[targetSantaID].pos.y)
            {
                targetSantaID = s;
            }
            else if (santas[s].pos.y == santas[targetSantaID].pos.y && santas[s].pos.x > santas[targetSantaID].pos.x)
            {
                targetSantaID = s;
            }
        }
    }

    if (targetSantaID == 0)
    {
        return;
    }

    Pos target = santas[targetSantaID].pos;

    int moveY = 0, moveX = 0;
    if (target.y > rudolf.y) moveY = 1;
    else if (target.y < rudolf.y) moveY = -1;

    if (target.x > rudolf.x) moveX = 1;
    else if (target.x < rudolf.x) moveX = -1;

    board[rudolf.y][rudolf.x] = 0;
    rudolf.y += moveY;
    rudolf.x += moveX;
    board[rudolf.y][rudolf.x] = RUDOLF;

    if (rudolf.y == target.y && rudolf.x == target.x)
    {
        board[rudolf.y][rudolf.x] = RUDOLF;
        Collision(targetSantaID, rudolf.y, rudolf.x, moveY, moveX, powerRudolf);
    }
}

void SantaTurn() {
    for (int s = 1; s <= santaCount; ++s)
    {
        if (currTurn <= santas[s].stunUntil)
        {
            continue;
        }

        int minDist = GetDist(rudolf, santas[s].pos);
        int bestDir = -1;

        for (int d = 0; d < 4; ++d)
        {
            int ny = santas[s].pos.y + dy[d];
            int nx = santas[s].pos.x + dx[d];

            if (IsValid(ny, nx) && board[ny][nx] <= 0)
            {
                int dist = GetDist({ ny, nx }, rudolf);
                if (dist < minDist)
                {
                    minDist = dist;
                    bestDir = d;
                }
            }
        }

        if (bestDir != -1)
        {
            board[santas[s].pos.y][santas[s].pos.x] = 0;
            santas[s].pos.y += dy[bestDir];
            santas[s].pos.x += dx[bestDir];

            if (santas[s].pos.y == rudolf.y && santas[s].pos.x == rudolf.x)
            {
                int bounceDir = (bestDir + 2) % 4;
                Collision(s, rudolf.y, rudolf.x, dy[bounceDir], dx[bounceDir], powerSanta);
            }
            else
            {
                board[santas[s].pos.y][santas[s].pos.x] = s;
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> boardSize >> maxTurn >> santaCount >> powerRudolf >> powerSanta;
    std::cin >> rudolf.y >> rudolf.x;
    board[rudolf.y][rudolf.x] = RUDOLF;

    for (int i = 0; i < santaCount; ++i)
    {
        int id, y, x;
        std::cin >> id >> y >> x;
        santas[id] = { id, {y, x}, 0, 0 };
        board[y][x] = id;
    }

    currTurn = 1;
    while (currTurn <= maxTurn)
    {
        RudolfTurn();
        SantaTurn();

        bool isAnyoneAlive = false;
        for (int i = 1; i <= santaCount; ++i)
        {
            if (santas[i].stunUntil != RETIRE)
            {
                santas[i].score += 1;
                isAnyoneAlive = true;
            }
        }

        if (!isAnyoneAlive)
        {
            break;
        }

        currTurn++;
    }

    for (int s = 1; s <= santaCount; ++s)
    {
        std::cout << santas[s].score << " ";
    }

    return 0;
}