#include <iostream>
#include <vector>
#include <algorithm>

struct Meeting
{
	int start;
	int end;

	const bool operator<(const Meeting& other) const
	{
		if (end == other.end)
		{
			return start < other.start;
		}

		return end < other.end;
	}
};

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	int N;
	std::cin >> N;

	std::vector<Meeting> meetings;
	meetings.assign(N, { 0, 0 });

	for (int i = 0; i < N; ++i)
	{
		int s, e;
		std::cin >> s >> e;
		meetings[i] = { s, e };
	}

	std::sort(meetings.begin(), meetings.end());

	int meetingCnt = 0;
	int currentEndTime = 0;

	for (int i = 0; i < N; ++i)
	{
		if (currentEndTime <= meetings[i].start)
		{
			meetingCnt++;
			currentEndTime = meetings[i].end;
		}
	}

	std::cout << meetingCnt << "\n";

	return 0;
}
