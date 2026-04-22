// https://swexpertacademy.com/main/talk/solvingClub/problemView.do?contestProbId=AV140YnqAIECFAYD&solveclubId=AZwrPjFqFyDHBIT3&problemBoxTitle=2%EC%A3%BC%EC%B0%A8&problemBoxCnt=6&probBoxId=AZxWf_YKvf3HBIT3

#include <iostream>

// ====================
// 상수 선언
// ====================

#define MAX_N 100

// ====================
// 전역 변수
// ====================

char tree[MAX_N + 1];
int N;

// ====================
// 중위 순회
// ====================

void PrintInOrder(int idx)
{
	if (idx > N) return;

	PrintInOrder(idx * 2);
	std::cout << tree[idx];
	PrintInOrder(idx * 2 + 1);
}

// ====================
// main 함수
// ====================

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	int T = 10;
	for (int tc = 1; tc <= T; ++tc)
	{
		std::cin >> N;

		for (int i = 0; i < N; ++i)
		{
			int idx;
			char value;
			std::cin >> idx >> value;

			tree[idx] = value;

			int dummy;
			if (idx * 2 <= N) std::cin >> dummy;
			if (idx * 2 + 1 <= N) std::cin >> dummy;
		}

		std::cout << "#" << tc << " ";
		PrintInOrder(1);
		std::cout << "\n";
	}

	return 0;
}
