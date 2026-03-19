#define MAX_WIDTH 500
#define MAX_HEIGHT 1500
#define MAX_CAGES 20
#define MAX_PATTERNS 64

#include <vector>
#include <algorithm>

struct Result {
	int ID;
	int height;
	int used;
};

struct Cage {
	int ID;
	int* lengths;
	int* upShapes;
	int currEmptySpace;
	int heightInfo[MAX_HEIGHT + 1];

	int patternPos[MAX_PATTERNS][MAX_WIDTH];
	int patternCount[MAX_PATTERNS];
};

int cageCount;
int maxCageWidth, maxCageHeight;

std::vector<int> sortedIndex;
Cage cages[MAX_CAGES];

// ====================
// API Helper
// ====================

inline int encodeShape(int d0, int d1, int d2)
{
	return d0 * 16 + d1 * 4 + d2;
}

bool compareCage(int a, int b)
{
	return cages[a].ID < cages[b].ID;
}

inline bool checkHeights(int cage, int mLengths[], int start)
{
	for (int i = 0; i < 2; ++i)
	{
		int leftBot = cages[cage].lengths[start + i] + 1;
		int leftTop = leftBot + mLengths[i] - 1;
		if (leftTop > maxCageHeight)
		{
			return false;
		}

		int rightBot = cages[cage].lengths[start + (i + 1)] + 1;
		int rightTop = rightBot + mLengths[i + 1] - 1;
		if (rightTop > maxCageHeight)
		{
			return false;
		}

		if (leftTop < rightBot || rightTop < leftBot)
		{
			return false;
		}
	}

	return true;
}

inline void removeFromPatternTable(int cage, int start)
{
	int oldPattern = encodeShape(cages[cage].upShapes[start],
		cages[cage].upShapes[start + 1],
		cages[cage].upShapes[start + 2]);

	int& cnt = cages[cage].patternCount[oldPattern];
	int* positions = cages[cage].patternPos[oldPattern];

	for (int i = 0; i < cnt; ++i)
	{
		if (positions[i] == start)
		{
			positions[i] = positions[--cnt];
			return;
		}
	}
}

inline void addToPatternTable(int cage, int start)
{
	int newPattern = encodeShape(cages[cage].upShapes[start],
		cages[cage].upShapes[start + 1],
		cages[cage].upShapes[start + 2]);

	int& cnt = cages[cage].patternCount[newPattern];
	cages[cage].patternPos[newPattern][cnt++] = start;
}

inline void buildStructure(int cage, int mLengths[], int mUpShapes[], int start)
{
	int updateStart = std::max(0, start - 2);
	int updateEnd = std::min(maxCageWidth - 3, start + 2);

	for (int s = updateStart; s <= updateEnd; ++s)
	{
		removeFromPatternTable(cage, s);
	}

	for (int i = 0; i < 3; ++i)
	{
		cages[cage].lengths[start + i] += mLengths[i];
		cages[cage].upShapes[start + i] = mUpShapes[i];
		cages[cage].currEmptySpace -= mLengths[i];

		for (int cnt = 0; cnt < mLengths[i]; ++cnt)
		{
			cages[cage].heightInfo[cages[cage].lengths[start + i] - cnt]++;
		}
	}

	for (int s = updateStart; s <= updateEnd; ++s)
	{
		addToPatternTable(cage, s);
	}
}

// ====================
// API 구현부
// ====================

void init(int N, int mWidth, int mHeight, int mIDs[], int mLengths[][MAX_WIDTH], int mUpShapes[][MAX_WIDTH])
{
	cageCount = N;
	maxCageWidth = mWidth;
	maxCageHeight = mHeight;
	sortedIndex.assign(N, -1);

	for (int i = 0; i < N; ++i)
	{
		cages[i] = { mIDs[i], mLengths[i], mUpShapes[i], mWidth * mHeight };
		sortedIndex[i] = i;

		for (int p = 0; p < MAX_PATTERNS; ++p)
		{
			cages[i].patternCount[p] = 0;
		}

		int diff[MAX_HEIGHT + 2] = {};
		for (int c = 0; c < maxCageWidth; ++c)
		{
			cages[i].currEmptySpace -= cages[i].lengths[c];

			int L = cages[i].lengths[c];
			diff[1]++;
			diff[L + 1]--;
		}

		int running = 0;
		for (int h = 1; h <= maxCageHeight; ++h)
		{
			running += diff[h];
			cages[i].heightInfo[h] = running;
		}

		for (int s = 0; s <= maxCageWidth - 3; ++s)
		{
			addToPatternTable(i, s);
		}
	}

	std::sort(sortedIndex.begin(), sortedIndex.end(), compareCage);
}

int checkStructures(int mLengths[], int mUpShapes[], int mDownShapes[])
{
	int answer = 0;
	int targetPattern = encodeShape(mDownShapes[0], mDownShapes[1], mDownShapes[2]);

	for (int cage = 0; cage < cageCount; ++cage)
	{
		int cnt = cages[cage].patternCount[targetPattern];
		int* positions = cages[cage].patternPos[targetPattern];

		for (int i = 0; i < cnt; ++i)
		{
			if (checkHeights(cage, mLengths, positions[i]))
			{
				answer++;
			}
		}
	}

	return answer;
}

int addStructures(int mLengths[], int mUpShapes[], int mDownShapes[])
{
	int targetPattern = encodeShape(mDownShapes[0], mDownShapes[1], mDownShapes[2]);

	for (int cage : sortedIndex)
	{
		int cnt = cages[cage].patternCount[targetPattern];
		int* positions = cages[cage].patternPos[targetPattern];

		std::sort(positions, positions + cnt);

		for (int i = 0; i < cnt; ++i)
		{
			if (checkHeights(cage, mLengths, positions[i]))
			{
				int s = positions[i];
				buildStructure(cage, mLengths, mUpShapes, s);

				return cages[cage].ID * 1000 + s + 1;
			}
		}
	}

	return 0;
}

Result pourIn(int mWater)
{
	Result ret;
	ret.ID = ret.height = ret.used = 0;

	for (int cage : sortedIndex)
	{
		int emptySpace = cages[cage].currEmptySpace;

		for (int h = maxCageHeight; h >= ret.height; --h)
		{
			int leftWater = mWater - emptySpace;
			int usedWater = mWater - leftWater;

			if (leftWater >= 0 && usedWater >= 1 && (h > ret.height || usedWater > ret.used))
			{
				ret.ID = cages[cage].ID;
				ret.height = h;
				ret.used = usedWater;
				break;
			}

			emptySpace -= (maxCageWidth - cages[cage].heightInfo[h]);
		}
	}

	return ret;
}
