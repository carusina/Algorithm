#define MAX_NUM 999
#define LEFT 0
#define RIGHT 1

#include <string>

std::string left1, left2;
std::string core1, core2;
std::string right1, right2;

int count1[MAX_NUM + 1];
int count2[MAX_NUM + 1];

// ====================
// API Helper
// ====================

char getDigitFromFront(const std::string& left, const std::string& core, const std::string& right, int pos) {
    int leftSize = (int)left.size();
    if (pos < leftSize)
    {
        return left[leftSize - 1 - pos];
    }

    pos -= leftSize;
    
    int coreSize = (int)core.size();
    if (pos < coreSize)
    {
        return core[pos];
    }

    pos -= coreSize;
    return right[pos];
}

char getDigitFromBack(const std::string& left, const std::string& core, const std::string& right, int fromEnd) {
    int rightSize = (int)right.size();
    if (fromEnd <= rightSize)
    {
        return right[rightSize - fromEnd];
    }

    fromEnd -= rightSize;

    int coreSize = (int)core.size();
    if (fromEnd <= coreSize)
    {
        return core[coreSize - fromEnd];
    }

    fromEnd -= coreSize;
    return left[fromEnd - 1];
}

void addToCount(int id, int d0, int d1, int d2) {
    int num = d0 * 100 + d1 * 10 + d2;

    if (id == 1)
    {
        count1[num]++;
    }
    else
    {
        count2[num]++;
    }
}

void updateCountFromWindow(int id, const std::string& window) {
    for (int i = 0; i <= (int)window.size() - 3; ++i)
    {
        addToCount(id, window[i] - '0', window[i + 1] - '0', window[i + 2] - '0');
    }
}

// ====================
// API 구현부
// ====================

void init(int mCnt1, int mDigitList1[30000], int mCnt2, int mDigitList2[30000]) {
    left1 =left2 = core1 = core2 = right1 = right2 = "";
    for (int i = 111; i <= MAX_NUM; ++i)
    {
        count1[i] = count2[i] = 0;
    }

    for (int i = 0; i < mCnt1; ++i)
    {
        core1 += (mDigitList1[i] + '0');

        if (i >= 2)
        {
            addToCount(1, mDigitList1[i - 2], mDigitList1[i - 1], mDigitList1[i]);
        }
    }

    for (int i = 0; i < mCnt2; ++i)
    {
        core2 += (mDigitList2[i] + '0');

        if (i >= 2)
        {
            addToCount(2, mDigitList2[i - 2], mDigitList2[i - 1], mDigitList2[i]);
        }
    }
}

void append(int mDir, int mNum1, int mNum2) {
    std::string appendNum1 = std::to_string(mNum1);
    std::string appendNum2 = std::to_string(mNum2);

    switch (mDir)
    {
    case LEFT:
        {
            std::string window = appendNum1;
            window += getDigitFromFront(left1, core1, right1, 0);
            window += getDigitFromFront(left1, core1, right1, 1);
            updateCountFromWindow(1, window);

            for (int i = (int)appendNum1.size() - 1; i >= 0; --i)
            {
                left1.push_back(appendNum1[i]);
            }

            window = appendNum2;
            window += getDigitFromFront(left2, core2, right2, 0);
            window += getDigitFromFront(left2, core2, right2, 1);
            updateCountFromWindow(2, window);

            for (int i = (int)appendNum2.size() - 1; i >= 0; --i)
            {
                left2.push_back(appendNum2[i]);
            }
        }

        break;
    case RIGHT:
        {
            std::string window = "";
            window += getDigitFromBack(left1, core1, right1, 2);
            window += getDigitFromBack(left1, core1, right1, 1);
            window += appendNum1;
            updateCountFromWindow(1, window);

            right1 += appendNum1;

            window = "";
            window += getDigitFromBack(left2, core2, right2, 2);
            window += getDigitFromBack(left2, core2, right2, 1);
            window += appendNum2;
            updateCountFromWindow(2, window);

            right2 += appendNum2;
        }

        break;
    }
}

int countNum(int mNum) {
    std::string boundary = "";
    boundary += getDigitFromBack(left1, core1, right1, 2);
    boundary += getDigitFromBack(left1, core1, right1, 1);
    boundary += getDigitFromFront(left2, core2, right2, 0);
    boundary += getDigitFromFront(left2, core2, right2, 1);

    int boundaryCount = 0;

    for (int i = 0; i <= (int)boundary.size() - 3; ++i)
    {
        int num = (boundary[i] - '0') * 100 + (boundary[i + 1] - '0') * 10 + (boundary[i + 2] - '0');
        if (num == mNum)
        {
            boundaryCount++;
        }
    }

    return count1[mNum] + boundaryCount + count2[mNum];
}
