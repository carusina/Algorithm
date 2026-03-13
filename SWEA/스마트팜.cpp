constexpr int MAX_N = 1001;
constexpr int MAX_CATEGORY = 3;

constexpr int MAX_BLOCKS = 32; // sqrt(1000) ~= 31.~~
constexpr int BLOCK_SIZE = 32;

constexpr long long INF = 0x3f3f3f3f3f3f3f3f;

struct CropCell {
	bool activate;
	int category;
	int plantTime;
	int wateredSize;
};

struct BucketMeta {
	int cropCount; // 버킷의 심어진 작물 수
	int lazyWater; // 버킷에 급수된 물의 G 크기
	long long worstGrowthState[3]; // 버킷에서 가장 덜 자란 작물 상태 캐싱
	short activeRows[1024]; // 심어진 작물의 행 좌표 기록 (MAX_BLOCKS * MAX_BLOCKS)
	short activeCols[1024]; // 심어진 작물의 열 좌표 기록 (MAX_BLOCKS * MAX_BLOCKS)
};

CropCell farm[MAX_N][MAX_N];
BucketMeta buckets[MAX_BLOCKS][MAX_BLOCKS];

int farmSize;
int growthTime[MAX_CATEGORY];

// ============================
// API Helper
// ============================
inline void PushDownLazyWater(int br, int bc) {
	if (buckets[br][bc].lazyWater == 0)
	{
		return;
	}

	int addedWater = buckets[br][bc].lazyWater;
	for (int i = 0; i < buckets[br][bc].cropCount; ++i)
	{
		int ar = buckets[br][bc].activeRows[i];
		int ac = buckets[br][bc].activeCols[i];
		farm[ar][ac].wateredSize += addedWater;
	}
	buckets[br][bc].lazyWater = 0;

	// 버킷의 최악 상태 값도 동기화
	for (int c = 0; c < MAX_CATEGORY; ++c)
	{
		if (buckets[br][bc].worstGrowthState[c] != INF)
		{
			buckets[br][bc].worstGrowthState[c] += (long long)growthTime[c] * addedWater;
		}
	}
}

inline void RecalculateBucketState(int br, int bc) {
	for (int c = 0; c < MAX_CATEGORY; ++c)
	{
		buckets[br][bc].worstGrowthState[c] = INF;
	}

	for (int i = 0; i < buckets[br][bc].cropCount; ++i)
	{
		int ar = buckets[br][bc].activeRows[i];
		int ac = buckets[br][bc].activeCols[i];
		int category = farm[ar][ac].category;

		// 상태 방정식: (물 * 성장시간) - 심은시간
		long long currentState = (long long)growthTime[category] * farm[ar][ac].wateredSize - farm[ar][ac].plantTime;
		if (currentState < buckets[br][bc].worstGrowthState[category])
		{
			buckets[br][bc].worstGrowthState[category] = currentState;
		}
	}
}

inline bool IsCropHaverstable(int r, int c, int mTime, int L) {
	int category = farm[r][c].category;
	
	long long currentState = (long long)growthTime[category] * farm[r][c].wateredSize - farm[r][c].plantTime;
	long long requiredThreshold = (long long)growthTime[category] * L - mTime;

	return currentState >= requiredThreshold;
}

inline void RemoveCropSwapAndPop(int br, int bc, int index) {
	int ar = buckets[br][bc].activeRows[index];
	int ac = buckets[br][bc].activeCols[index];

	farm[ar][ac].activate = false;

	int lastIndex = buckets[br][bc].cropCount - 1;
	buckets[br][bc].activeRows[index] = buckets[br][bc].activeRows[lastIndex];
	buckets[br][bc].activeCols[index] = buckets[br][bc].activeCols[lastIndex];
	buckets[br][bc].cropCount--;
}

// ============================
// API 구현부
// ============================

void init(int N, int mGrowthTime[]) {
	farmSize = N;
	for (int i = 0; i < MAX_CATEGORY; ++i)
	{
		growthTime[i] = mGrowthTime[i];
	}

	int maxBr = (farmSize - 1) / BLOCK_SIZE;
	int maxBc = (farmSize - 1) / BLOCK_SIZE;

	for (int br = 0; br <= maxBr; ++br)
	{
		for (int bc = 0; bc <= maxBc; ++bc)
		{
			// 심어졌던 곳만 찾아서 초기화
			for (int i = 0; i < buckets[br][bc].cropCount; ++i)
			{
				int ar = buckets[br][bc].activeRows[i];
				int ac = buckets[br][bc].activeCols[i];
				farm[ar][ac].activate = false;
			}

			buckets[br][bc].cropCount = 0;
			buckets[br][bc].lazyWater = 0;
			for (int c = 0; c < MAX_CATEGORY; ++c)
			{
				buckets[br][bc].worstGrowthState[c] = INF;
			}
		}
	}
}

int sow(int mTime, int mRow, int mCol, int mCategory) {
	if (farm[mRow][mCol].activate)
	{
		return 0;
	}

	int br = mRow / BLOCK_SIZE;
	int bc = mCol / BLOCK_SIZE;

	PushDownLazyWater(br, bc);

	farm[mRow][mCol].activate = true;
	farm[mRow][mCol].category = mCategory;
	farm[mRow][mCol].plantTime = mTime;
	farm[mRow][mCol].wateredSize = 0;

	int currentCropCount = buckets[br][bc].cropCount;
	buckets[br][bc].activeRows[currentCropCount] = mRow;
	buckets[br][bc].activeCols[currentCropCount] = mCol;
	buckets[br][bc].cropCount++;

	RecalculateBucketState(br, bc);

	return 1;
}
 
int water(int mTime, int G, int mRow, int mCol, int mHeight, int mWidth) {
	int wateredCount = 0;

	int startBr = mRow / BLOCK_SIZE;
	int startBC = mCol / BLOCK_SIZE;
	int endBr = (mRow + mHeight - 1) / BLOCK_SIZE;
	int endBc = (mCol + mWidth - 1) / BLOCK_SIZE;

	for (int br = startBr; br <= endBr; ++br)
	{
		for(int bc = startBC; bc <= endBc; ++bc)
		{
			if (buckets[br][bc].cropCount == 0)
			{
				continue;
			}

			int tileR1 = br * BLOCK_SIZE;
			int tileR2 = tileR1 + BLOCK_SIZE - 1;
			int tileC1 = bc * BLOCK_SIZE;
			int tileC2 = tileC1 + BLOCK_SIZE - 1;

			bool isFullyInside = (mRow <= tileR1 && tileR2 <= mRow + mHeight - 1) &&
						         (mCol <= tileC1 && tileC2 <= mCol + mWidth - 1);

			if (isFullyInside)
			{
				buckets[br][bc].lazyWater += G;
				wateredCount += buckets[br][bc].cropCount;
			}
			else
			{
				PushDownLazyWater(br, bc);

				for (int i = 0; i < buckets[br][bc].cropCount; ++i)
				{
					int ar = buckets[br][bc].activeRows[i];
					int ac = buckets[br][bc].activeCols[i];

					bool isInside = (mRow <= ar && ar <= mRow + mHeight - 1) &&
									(mCol <= ac && ac <= mCol + mWidth - 1);

					if (isInside)
					{
						farm[ar][ac].wateredSize += G;
						wateredCount++;
					}
				}

				RecalculateBucketState(br, bc);
			}
		}
	}

	return wateredCount;
}

int harvest(int mTime, int L, int mRow, int mCol, int mHeight, int mWidth) {
	int startBr = mRow / BLOCK_SIZE;
	int startBC = mCol / BLOCK_SIZE;
	int endBr = (mRow + mHeight - 1) / BLOCK_SIZE;
	int endBc = (mCol + mWidth - 1) / BLOCK_SIZE;

	for (int br = startBr; br <= endBr; ++br)
	{
		for (int bc = startBC; bc <= endBc; ++bc)
		{
			if (buckets[br][bc].cropCount == 0)
			{
				continue;
			}

			int tileR1 = br * BLOCK_SIZE;
			int tileR2 = tileR1 + BLOCK_SIZE - 1;
			int tileC1 = bc * BLOCK_SIZE;
			int tileC2 = tileC1 + BLOCK_SIZE - 1;

			bool isFullyInside = (mRow <= tileR1 && tileR2 <= mRow + mHeight - 1) &&
								 (mCol <= tileC1 && tileC2 <= mCol + mWidth - 1);

			if (isFullyInside)
			{
				for (int c = 0; c < MAX_CATEGORY; ++c)
				{
					if (buckets[br][bc].worstGrowthState[c] != INF)
					{
						long long currentWorstState = buckets[br][bc].worstGrowthState[c] +
													  (long long)growthTime[c] * buckets[br][bc].lazyWater;
						long long requiredThreshold = (long long)growthTime[c] * L - mTime;

						if (currentWorstState < requiredThreshold)
						{
							return 0;
						}
					}
				}
			}
			else
			{
				PushDownLazyWater(br, bc);
				
				for (int i = 0; i < buckets[br][bc].cropCount; ++i)
				{
					int ar = buckets[br][bc].activeRows[i];
					int ac = buckets[br][bc].activeCols[i];

					bool isInside = (mRow <= ar && ar <= mRow + mHeight - 1) &&
									(mCol <= ac && ac <= mCol + mWidth - 1);

					if (isInside)
					{
						if (!IsCropHaverstable(ar, ac, mTime, L))
						{
							return 0;
						}
					}
				}
			}
		}
	}

	int harvestedCount = 0;
	for (int br = startBr; br <= endBr; ++br)
	{
		for (int bc = startBC; bc <= endBc; ++bc)
		{
			if (buckets[br][bc].cropCount == 0)
			{
				continue;
			}

			int tileR1 = br * BLOCK_SIZE;
			int tileR2 = tileR1 + BLOCK_SIZE - 1;
			int tileC1 = bc * BLOCK_SIZE;
			int tileC2 = tileC1 + BLOCK_SIZE - 1;

			bool isFullyInside = (mRow <= tileR1 && tileR2 <= mRow + mHeight - 1) &&
								 (mCol <= tileC1 && tileC2 <= mCol + mWidth - 1);

			if (isFullyInside)
			{
				harvestedCount += buckets[br][bc].cropCount;
				for (int i = 0; i < buckets[br][bc].cropCount; ++i)
				{
					int ar = buckets[br][bc].activeRows[i];
					int ac = buckets[br][bc].activeCols[i];

					farm[ar][ac].activate = false;
				}
				buckets[br][bc].cropCount = 0;
				buckets[br][bc].lazyWater = 0;
				for (int c = 0; c < MAX_CATEGORY; ++c)
				{
					buckets[br][bc].worstGrowthState[c] = INF;
				}
			}
			else
			{
				for (int i = 0; i < buckets[br][bc].cropCount; ++i)
				{
					int ar = buckets[br][bc].activeRows[i];
					int ac = buckets[br][bc].activeCols[i];

					bool isInside = (mRow <= ar && ar <= mRow + mHeight - 1) &&
									(mCol <= ac && ac <= mCol + mWidth - 1);

					if (isInside)
					{
						RemoveCropSwapAndPop(br, bc, i);
						harvestedCount++;
						i--;
					}
				}

				RecalculateBucketState(br, bc);
			}
		}
	}

	return harvestedCount;
}
