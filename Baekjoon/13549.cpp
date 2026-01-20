#include <iostream>
#include <queue>

const int max = 100001;
const int dx[] = {-1, 1, 2};
int board[max] = { 0 };

inline bool IsValid(int x);
void BFS(std::queue<int>& q, int K);

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	int N = 0, K = 0;
	std::cin >> N >> K;

	std::queue<int> q;
	q.push(N);
	board[N] = 1;

	BFS(q, K);
	
	std::cout << board[K] - 1;

	return 0;
}

inline bool IsValid(int x)
{
	return 0 <= x && x < max;
}

void BFS(std::queue<int>& q, int K)
{
	while (!q.empty())
	{
		int curr = q.front();
		q.pop();

		if (curr == K)
		{
			continue;
		}

		for (int d = 0; d < 3; ++d)
		{
			int nx = curr;
			int nxDist = board[curr];

			if (d == 2)
			{
				nx *= dx[d];
			}
			else
			{
				nx += dx[d];
				nxDist += 1;
			}

			if (!IsValid(nx))
			{
				continue;
			}

			if (board[nx] == 0 || board[nx] > nxDist)
			{
				board[nx] = nxDist;
				q.push(nx);
			}
		}
	}
}
