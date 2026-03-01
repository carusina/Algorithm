constexpr int MAX_SOLDIER = 100001;
constexpr int DUMMY_START = 100000;

struct Soldier
{
    int prev;
    int next;
};

Soldier soldierPool[MAX_SOLDIER + 25];
int soldierTeam[MAX_SOLDIER];

inline int getDummy(int team, int score)
{
    return DUMMY_START + (team - 1) * 5 + score;
}

void init()
{
    for (int t = 1; t <= 5; ++t)
    {
        for (int s = 1; s <= 5; ++s)
        {
            int dummy = getDummy(t, s);
            soldierPool[dummy].prev = dummy;
            soldierPool[dummy].next = dummy;
        }
    }
}

void insertNode(int mID, int team, int score)
{
    int dummy = getDummy(team, score);
    int first = soldierPool[dummy].next;

    soldierPool[mID].next = first;
    soldierPool[mID].prev = dummy;

    soldierPool[first].prev = mID;
    soldierPool[dummy].next = mID;
}

void removeNode(int mID)
{
    int prev = soldierPool[mID].prev;
    int next = soldierPool[mID].next;

    soldierPool[prev].next = next;
    soldierPool[next].prev = prev;

    soldierPool[mID].prev = 0;
    soldierPool[mID].next = 0;
}

void splice(int destDummy, int srcDummy)
{
    if (soldierPool[srcDummy].next == srcDummy)
    {
        return;
    }

    int srcFirst = soldierPool[srcDummy].next;
    int srcLast = soldierPool[srcDummy].prev;
    int destLast = soldierPool[destDummy].prev;

    soldierPool[destLast].next = srcFirst;
    soldierPool[srcFirst].prev = destLast;

    soldierPool[srcLast].next = destDummy;
    soldierPool[destDummy].prev = srcLast;

    soldierPool[srcDummy].prev = srcDummy;
    soldierPool[srcDummy].next = srcDummy;
}

void hire(int mID, int mTeam, int mScore)
{
    soldierTeam[mID] = mTeam;
    insertNode(mID, mTeam, mScore);
}

void fire(int mID)
{
    removeNode(mID);
}

void updateSoldier(int mID, int mScore)
{
    removeNode(mID);
    insertNode(mID, soldierTeam[mID], mScore);
}

void updateTeam(int mTeam, int mChangeScore)
{
    if (mChangeScore == 0)
    {
        return;
    }

    if (mChangeScore > 0)
    {
        for (int s = 4; s >= 1; --s)
        {
            int destScore = s + mChangeScore;
            if (destScore > 5)
            {
                destScore = 5;
            }

            if (s == destScore)
            {
                continue;
            }

            splice(getDummy(mTeam, destScore), getDummy(mTeam, s));
        }
    }
    else
    {
        for (int s = 2; s <= 5; ++s)
        {
            int destScore = s + mChangeScore;
            if (destScore < 1)
            {
                destScore = 1;
            }

            if (s == destScore)
            {
                continue;
            }

            splice(getDummy(mTeam, destScore), getDummy(mTeam, s));
        }
    }
}

int bestSoldier(int mTeam)
{
    for (int s = 5; s >= 1; --s)
    {
        int dummy = getDummy(mTeam, s);
        if (soldierPool[dummy].next == dummy)
        {
            continue;
        }

        int maxID = -1;
        for (int curr = soldierPool[dummy].next; curr != dummy; curr = soldierPool[curr].next)
        {
            if (curr > maxID)
            {
                maxID = curr;
            }
        }

        if (maxID != -1)
        {
            return maxID;
        }
    }

    return -1;
}