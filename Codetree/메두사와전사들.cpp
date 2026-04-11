// https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/medusa-and-warriors/description

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// ====================
// 상수 및 구조체 선언
// ====================

#define MAX_N 50
#define MAX_WARRIOR 300

constexpr int dy[] = { -1, 1, 0, 0 };
constexpr int dx[] = { 0, 0, -1, 1 };

constexpr int dy2[] = { 0, 0, -1, 1 };
constexpr int dx2[] = { -1, 1, 0, 0 };

struct Pos
{
    int y, x;

    bool operator==(const Pos& other) const
    {
        return y == other.y && x == other.x;
    }
};

// ====================
// 전역 변수
// ====================

int townSize, warriorCount;
int grid[MAX_N + 1][MAX_N + 1];

Pos medusaHomePos, parkPos;
Pos warriorPos[MAX_WARRIOR + 1];
bool isDead[MAX_WARRIOR + 1];
bool isPetrified[MAX_WARRIOR + 1];

std::vector<Pos> medusaPaths;
int currTurn = 0;
Pos currentMedusaPos;
std::vector<std::vector<bool>> activeSightMap; // 현재 턴의 메두사 위험 지역

// ====================
// 유틸 함수
// ====================

inline bool IsValid(int y, int x)
{
    return 0 <= y && y < townSize &&
           0 <= x && x < townSize;
}

inline int GetManhattanDist(Pos a, Pos b)
{
    return abs(a.y - b.y) + abs(a.x - b.x);
}

// ====================
// 메두사의 이동
// ====================

void GetMedusaPaths()
{
    int distMap[MAX_N + 1][MAX_N + 1];

    for (int i = 0; i < townSize; ++i)
    {
        std::fill(distMap[i], distMap[i] + townSize, -1);
    }

    std::queue<Pos> q;

    q.push(parkPos);
    distMap[parkPos.y][parkPos.x] = 0;

    while (!q.empty())
    {
        Pos curr = q.front();
        q.pop();

        for (int d = 0; d < 4; ++d)
        {
            int ny = curr.y + dy[d];
            int nx = curr.x + dx[d];
            if (IsValid(ny, nx) && grid[ny][nx] == 0 && distMap[ny][nx] == -1)
            {
                distMap[ny][nx] = distMap[curr.y][curr.x] + 1;
                q.push({ ny, nx });
            }
        }
    }

    if (distMap[medusaHomePos.y][medusaHomePos.x] == -1) return;

    Pos curr = medusaHomePos;
    medusaPaths.push_back(curr);

    while (!(curr == parkPos))
    {
        for (int d = 0; d < 4; ++d)
        {
            int ny = curr.y + dy[d];
            int nx = curr.x + dx[d];

            if (IsValid(ny, nx) && distMap[ny][nx] == distMap[curr.y][curr.x] - 1)
            {
                curr = { ny, nx };
                medusaPaths.push_back(curr);
                break;
            }
        }
    }
}

// ====================
// 메두사의 시선
// ====================

int ProcessMedusaSight()
{
    int bestPetrifiedCount = -1;
    std::vector<int> bestPetrifiedIdx;
    std::vector<std::vector<bool>> bestSightMap;

    for (int d = 0; d < 4; ++d)
    {
        // 1단계: 시야각(FOV) 내 전사 식별
        std::vector<int> fovIdx;
        for (int i = 0; i < warriorCount; ++i)
        {
            if (isDead[i]) continue;

            int wy = warriorPos[i].y, wx = warriorPos[i].x;
            int my = currentMedusaPos.y, mx = currentMedusaPos.x;

            /*
            inFov 처리 순서
                1. 전사가 메두사가 바라보는 방향에 위치하는지 확인 - "d가 0이면 wy < my"
                2. 전사가 메두사의 시야각 이내에 위치하는지 확인 - 메두사로부터 1칸 위에 있다면, 좌우 1칸 허용
                                                             - 2칸 위에 있다면, 좌우 2칸 허용
            */

            bool inFov = false;
            if (d == 0)      inFov = (wy < my && abs(wx - mx) <= my - wy);
            else if (d == 1) inFov = (wy > my && abs(wx - mx) <= wy - my);
            else if (d == 2) inFov = (wx < mx && abs(wy - my) <= mx - wx);
            else if (d == 3) inFov = (wx > mx && abs(wy - my) <= wx - mx);

            if (inFov) fovIdx.push_back(i);
        }

        // 2단계: 맨해튼 거리 기준 정렬
        sort(fovIdx.begin(), fovIdx.end(), [&](int a, int b) {
            return GetManhattanDist(warriorPos[a], currentMedusaPos) < GetManhattanDist(warriorPos[b], currentMedusaPos);
            });

        // 3단계: 그림자 캐스팅
        // 해설의 3갈래 BFS와 동일한 그림자 범위를 직접 계산으로 구현
        // 전사가 메두사와 같은 열(행)이면 직선, 왼쪽/오른쪽(위/아래)이면 해당 방향 삼각형
        std::vector<int> tempPetrified;
        std::vector<std::vector<bool>> tempShadow(townSize, std::vector<bool>(townSize, false));
        for (int idx : fovIdx)
        {
            int wy = warriorPos[idx].y, wx = warriorPos[idx].x;
            int my = currentMedusaPos.y, mx = currentMedusaPos.x;

            if (tempShadow[wy][wx]) continue; // 앞 전사에게 가려짐

            tempPetrified.push_back(idx);

            for (int y = 0; y < townSize; ++y)
            {
                for (int x = 0; x < townSize; ++x)
                {
                    bool inShadow = false;
                    if (d == 0) // 위: y < wy인 칸
                    {
                        if (y >= wy) continue;

                        int gap = wy - y;
                        if (wx == mx)     inShadow = (x == wx);
                        else if (wx < mx) inShadow = (x <= wx && x >= wx - gap);
                        else              inShadow = (x >= wx && x <= wx + gap);
                    }
                    else if (d == 1) // 아래: y > wy인 칸
                    {
                        if (y <= wy) continue;

                        int gap = y - wy;
                        if (wx == mx)     inShadow = (x == wx);
                        else if (wx < mx) inShadow = (x <= wx && x >= wx - gap);
                        else              inShadow = (x >= wx && x <= wx + gap);
                    }
                    else if (d == 2) // 좌: x < wx인 칸
                    {
                        if (x >= wx) continue;

                        int gap = wx - x;
                        if (wy == my)     inShadow = (y == wy);
                        else if (wy < my) inShadow = (y <= wy && y >= wy - gap);
                        else              inShadow = (y >= wy && y <= wy + gap);
                    }
                    else // 우: x > wx인 칸
                    {
                        if (x <= wx) continue;

                        int gap = x - wx;
                        if (wy == my)     inShadow = (y == wy);
                        else if (wy < my) inShadow = (y <= wy && y >= wy - gap);
                        else              inShadow = (y >= wy && y <= wy + gap);
                    }
                    if (inShadow) tempShadow[y][x] = true;
                }
            }
        }

        // 4단계: 위험 지역(Sight Map) 추출
        std::vector<std::vector<bool>> tempSightMap(townSize, std::vector<bool>(townSize, false));
        for (int y = 0; y < townSize; ++y)
        {
            for (int x = 0; x < townSize; ++x)
            {
                bool inFov = false;
                if (d == 0)      inFov = (y < currentMedusaPos.y && abs(x - currentMedusaPos.x) <= currentMedusaPos.y - y);
                else if (d == 1) inFov = (y > currentMedusaPos.y && abs(x - currentMedusaPos.x) <= y - currentMedusaPos.y);
                else if (d == 2) inFov = (x < currentMedusaPos.x && abs(y - currentMedusaPos.y) <= currentMedusaPos.x - x);
                else if (d == 3) inFov = (x > currentMedusaPos.x && abs(y - currentMedusaPos.y) <= x - currentMedusaPos.x);

                if (inFov && !tempShadow[y][x])
                {
                    tempSightMap[y][x] = true;
                }
            }
        }

        // [핵심 픽스] 눈이 마주친 전사의 셀은 그림자에 묻히지 않고 무조건 위험 지역임
        for (int idx : tempPetrified)
        {
            tempSightMap[warriorPos[idx].y][warriorPos[idx].x] = true;
        }

        // 가장 많은 전사를 보는 방향 갱신
        if ((int)tempPetrified.size() > bestPetrifiedCount)
        {
            bestPetrifiedCount = tempPetrified.size();
            bestPetrifiedIdx = tempPetrified;
            bestSightMap = tempSightMap;
        }
    }

    // 최종 결과 캐싱
    std::fill(isPetrified, isPetrified + MAX_WARRIOR, false);
    for (int idx : bestPetrifiedIdx) isPetrified[idx] = true;
    activeSightMap = bestSightMap;

    return bestPetrifiedCount;
}

// ====================
// 전사들의 이동
// ====================
int ProcessWarriorMove()
{
    int totalDist = 0;

    for (int i = 0; i < warriorCount; ++i)
    {
        if (isDead[i] || isPetrified[i]) continue;

        int curDist = GetManhattanDist(warriorPos[i], currentMedusaPos);
        bool movedFirst = false;

        // 첫 번째 이동
        for (int d = 0; d < 4; ++d)
        {
            int ny = warriorPos[i].y + dy[d];
            int nx = warriorPos[i].x + dx[d];

            if (IsValid(ny, nx) && !activeSightMap[ny][nx])
            {
                int nDist = GetManhattanDist({ ny, nx }, currentMedusaPos);

                if (nDist < curDist)
                {
                    warriorPos[i] = { ny, nx };
                    curDist = nDist;
                    totalDist++;
                    movedFirst = true;
                    break;
                }
            }
        }

        // 1차 이동 실패 시 2차 이동도 하지 않음
        if (!movedFirst) continue;
        // 1차 이동에서 메두사 위치로 이동했다면 2차 이동 스킵
        if (warriorPos[i] == currentMedusaPos) continue;

        // 두 번째 이동
        for (int d = 0; d < 4; ++d)
        {
            int ny = warriorPos[i].y + dy2[d];
            int nx = warriorPos[i].x + dx2[d];

            if (IsValid(ny, nx) && !activeSightMap[ny][nx])
            {
                int nDist = GetManhattanDist({ ny, nx }, currentMedusaPos);

                if (nDist < curDist)
                {
                    warriorPos[i] = { ny, nx };
                    curDist = nDist;
                    totalDist++;
                    break;
                }
            }
        }
    }

    return totalDist;
}

// ====================
// main 함수
// ====================

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> townSize >> warriorCount;
    std::cin >> medusaHomePos.y >> medusaHomePos.x >> parkPos.y >> parkPos.x;

    for (int i = 0; i < warriorCount; ++i)
    {
        std::cin >> warriorPos[i].y >> warriorPos[i].x;
    }
    for (int i = 0; i < townSize; ++i)
    {
        for (int j = 0; j < townSize; ++j)
        {
            std::cin >> grid[i][j];
        }
    }

    GetMedusaPaths();
    if (medusaPaths.empty())
    {
        std::cout << -1;
        return 0;
    }

    int maxTurns = medusaPaths.size() - 1;

    while (currTurn < maxTurns)
    {
        currTurn++;
        currentMedusaPos = medusaPaths[currTurn];

        // 1. 메두사의 이동
        if (currentMedusaPos == parkPos)
        {
            std::cout << 0;
            return 0;
        }
        
        for (int i = 0; i < warriorCount; ++i)
        {
            if (!isDead[i] && warriorPos[i] == currentMedusaPos) isDead[i] = true;
        }

        // 2. 메두사의 시선
        int petrifiedCount = ProcessMedusaSight();

        // 3. 전사들의 이동
        int moveDist = ProcessWarriorMove();

        // 4. 전사의 공격
        int attackCount = 0;
        for (int i = 0; i < warriorCount; ++i) {
            if (!isDead[i] && !isPetrified[i] && warriorPos[i] == currentMedusaPos) {
                isDead[i] = true;
                attackCount++;
            }
        }

        std::cout << moveDist << " " << petrifiedCount << " " << attackCount << "\n";
    }

    return 0;
}