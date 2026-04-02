// https://school.programmers.co.kr/learn/courses/30/lessons/214288

#define MAX_K 5
#define INF 0x3f3f3f3f

#include <vector>
#include <queue>
#include <algorithm>

int GetWaitTime(int type, int mentoCount, const std::vector<std::vector<int>> requests[])
{
	int waitTime = 0;

	const std::vector<std::vector<int>>& req = requests[type];
	
	std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
	for (int i = 0; i < mentoCount; ++i)
	{
		pq.push(0);
	}

	for (const std::vector<int>& r : req)
	{
		int requestTime = r[0];
		int requiredTime = r[1];

		int minFinishedTime = pq.top();
		pq.pop();

		waitTime += std::max(minFinishedTime - requestTime, 0);
		int currFinishedTime = std::max(minFinishedTime, requestTime) + requiredTime;

		pq.push(currFinishedTime);
	}

	return waitTime;
}

int solution(int k, int n, std::vector<std::vector<int>> reqs) {
	int answer = 0;

	std::vector<std::vector<int>> requests[MAX_K + 1];
	for (const std::vector<int>& req : reqs)
	{
		requests[req[2]].push_back({ req[0], req[1] });
	}

	int maxMentoCount = n - k + 1;

	std::vector<std::vector<int>> cost(k + 1, std::vector<int>(maxMentoCount + 1, 0));
	for (int t = 1; t <= k; ++t)
	{
		for (int m = 1; m <= maxMentoCount; ++m)
		{
			cost[t][m] = GetWaitTime(t, m, requests);
		}
	}

	std::vector<int> mentors(k + 1, 1);
	int remainMentors = n - k;

	while (remainMentors-- > 0)
	{
		int maxSavedTime = -1;
		int bestType = -1;

		for (int type = 1; type <= k; ++type)
		{
			int currentMentors = mentors[type];

			int savedTime = cost[type][currentMentors] - cost[type][currentMentors + 1];

			if (savedTime > maxSavedTime)
			{
				maxSavedTime = savedTime;
				bestType = type;
			}
		}

		mentors[bestType]++;
	}

	int totalWaitTime = 0;
	for (int type = 1; type <= k; ++type)
	{
		totalWaitTime += cost[type][mentors[type]];
	}

	return totalWaitTime;
}