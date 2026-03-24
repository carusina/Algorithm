#define MAX_N 1000
#define MAX_CATEGORY 3
#define MAX_CROPS 100000 // sow() 최대 호출 100,000번
#define BUCKET_SIZE 32

#include <cstring>
#include <algorithm>

// ====================
// 구조체 선언
// ====================

struct Crop {
	int row, col;
	int category;
	int plantTime;
	int wateredSize;
	int prev, next;
};

struct Bucket {
	int head;
	int activeCropCount;
	int wateredSize;
};

// ====================
// 전역 변수
// ====================

int farmSize;
int growthTime[MAX_CATEGORY];
bool isPlanted[MAX_N + 1][MAX_N + 1];

Bucket farmBucket[BUCKET_SIZE][BUCKET_SIZE];

Crop cropPool[MAX_CROPS + 1];
int allocatedCropCount;

// ====================
// API 구현부
// ====================

void init(int N, int mGrowthTime[]) {
	farmSize = N;
	allocatedCropCount = 0;

	for (int c = 0; c < MAX_CATEGORY; ++c)
	{
		growthTime[c] = mGrowthTime[c];
	}

	int maxBr = (N - 1) / BUCKET_SIZE;
	int maxBc = (N - 1) / BUCKET_SIZE;

	std::memset(isPlanted, false, sizeof(isPlanted));

	for (int br = 0; br <= maxBr; ++br)
	{
		for (int bc = 0; bc <= maxBc; ++bc)
		{
			farmBucket[br][bc].head = -1;
			farmBucket[br][bc].activeCropCount = 0;
			farmBucket[br][bc].wateredSize = 0;
		}
	}
}

int sow(int mTime, int mRow, int mCol, int mCategory) {
	if (isPlanted[mRow][mCol])
	{
		return 0;
	}

	int br = mRow / BUCKET_SIZE;
	int bc = mCol / BUCKET_SIZE;
	Bucket& bucket = farmBucket[br][bc];

	int cropIdx = allocatedCropCount++;
	Crop& crop = cropPool[cropIdx];

	crop.row = mRow;
	crop.col = mCol;
	crop.category = mCategory;
	crop.plantTime = mTime;
	crop.wateredSize = -bucket.wateredSize;
	crop.prev = -1;
	crop.next = bucket.head;

	if (bucket.head != -1)
	{
		cropPool[bucket.head].prev = cropIdx;
	}

	bucket.head = cropIdx;

	bucket.activeCropCount++;
	isPlanted[mRow][mCol] = true;

	return 1;
}

int water(int mTime, int G, int mRow, int mCol, int mHeight, int mWidth) {
	int wateredCropCount = 0;

	int brStart = mRow / BUCKET_SIZE;
	int bcStart = mCol / BUCKET_SIZE;
	int brEnd = (mRow + mHeight - 1) / BUCKET_SIZE;
	int bcEnd = (mCol + mWidth - 1) / BUCKET_SIZE;

	for (int br = brStart; br <= brEnd; ++br)
	{
		for (int bc = bcStart; bc <= bcEnd; ++bc)
		{
			Bucket& bucket = farmBucket[br][bc];
			if (bucket.activeCropCount == 0)
			{
				continue;
			}

			int rowStart = br * BUCKET_SIZE;
			int colStart = bc * BUCKET_SIZE;
			int rowEnd = std::min(rowStart + BUCKET_SIZE - 1, farmSize - 1);
			int colEnd = std::min(colStart + BUCKET_SIZE - 1, farmSize - 1);

			bool isFullyInside = (mRow <= rowStart && rowEnd <= mRow + mHeight - 1) &&
				(mCol <= colStart && colEnd <= mCol + mWidth - 1);

			if (isFullyInside)
			{
				bucket.wateredSize += G;
				wateredCropCount += bucket.activeCropCount;
			}
			else
			{
				int currCropIdx = bucket.head;
				while (currCropIdx != -1)
				{
					Crop& crop = cropPool[currCropIdx];

					bool isInside = (mRow <= crop.row && crop.row <= mRow + mHeight - 1) &&
						(mCol <= crop.col && crop.col <= mCol + mWidth - 1);

					if (isInside)
					{
						crop.wateredSize += G;
						wateredCropCount++;
					}

					currCropIdx = crop.next;
				}
			}
		}
	}

	return wateredCropCount;
}

int harvest(int mTime, int L, int mRow, int mCol, int mHeight, int mWidth) {
	int harvestedCropCount = 0;

	int brStart = mRow / BUCKET_SIZE;
	int bcStart = mCol / BUCKET_SIZE;
	int brEnd = (mRow + mHeight - 1) / BUCKET_SIZE;
	int bcEnd = (mCol + mWidth - 1) / BUCKET_SIZE;

	for (int br = brStart; br <= brEnd; ++br)
	{
		for (int bc = bcStart; bc <= bcEnd; ++bc)
		{
			Bucket& bucket = farmBucket[br][bc];
			if (bucket.activeCropCount == 0)
			{
				continue;
			}

			int currCropIdx = bucket.head;
			while (currCropIdx != -1)
			{
				Crop& crop = cropPool[currCropIdx];

				bool isInside = (mRow <= crop.row && crop.row <= mRow + mHeight - 1) &&
					(mCol <= crop.col && crop.col <= mCol + mWidth - 1);

				if (isInside)
				{
					harvestedCropCount++;

					int totalWateredSize = crop.wateredSize + bucket.wateredSize;
					int cropSize = ((mTime - crop.plantTime) / growthTime[crop.category]) + totalWateredSize;

					if (cropSize < L)
					{
						return 0;
					}
				}

				currCropIdx = crop.next;
			}
		}
	}

	for (int br = brStart; br <= brEnd; ++br)
	{
		for (int bc = bcStart; bc <= bcEnd; ++bc)
		{
			Bucket& bucket = farmBucket[br][bc];
			if (bucket.activeCropCount == 0)
			{
				continue;
			}
			
			int currCropIdx = bucket.head;
			while (currCropIdx != -1)
			{
				Crop& crop = cropPool[currCropIdx];
				int nextCropIdx = crop.next;

				bool isInside = (mRow <= crop.row && crop.row <= mRow + mHeight - 1) &&
					(mCol <= crop.col && crop.col <= mCol + mWidth - 1);

				if (isInside)
				{
					isPlanted[crop.row][crop.col] = false;
					bucket.activeCropCount--;

					int p = crop.prev;
					int n = crop.next;

					if (p != -1)
					{
						cropPool[p].next = n;
					}
					else
					{
						bucket.head = n;
					}

					if (n != -1)
					{
						cropPool[n].prev = p;
					}
				}

				currCropIdx = nextCropIdx;
			}
		}
	}

	return harvestedCropCount;
}