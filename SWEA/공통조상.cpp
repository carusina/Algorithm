// https://swexpertacademy.com/main/talk/solvingClub/problemView.do?contestProbId=AV15PTkqAPYCFAYD&solveclubId=AZwrPjFqFyDHBIT3&problemBoxTitle=2%EC%A3%BC%EC%B0%A8&problemBoxCnt=6&probBoxId=AZxWf_YKvf3HBIT3

#include <iostream>

// ====================
// 상수 선언
// ====================

#define MAX_V 10000
#define ROOT 1

// ====================
// 구조체 선언
// ====================

struct Node
{
	int parent;
	int left, right;
};

// ====================
// 전역 선언
// ====================

Node tree[MAX_V + 1];
int visitedStamp[MAX_V + 1];

// ====================
// 공통 조상
// ====================

int FindLowestCommonAncestor(int idx1, int idx2, int stamp)
{
	int curr = idx1;
	while (curr != -1)
	{
		visitedStamp[curr] = stamp;
		curr = tree[curr].parent;
	}

	curr = idx2;
	while (curr != -1)
	{
		if (visitedStamp[curr] == stamp) return curr;
		curr = tree[curr].parent;
	}

	return ROOT;
}

// ====================
// 트리 크기
// ====================

int GetSubTreeSize(int idx)
{
	int cnt = 1;

	if (tree[idx].left != -1) cnt += GetSubTreeSize(tree[idx].left);
	if (tree[idx].right != -1) cnt += GetSubTreeSize(tree[idx].right);

	return cnt;
}

// ====================
// main 함수
// ====================

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	int T;
	std::cin >> T;
	for (int tc = 1; tc <= T; ++tc)
	{
		int V, E, idx1, idx2;
		std::cin >> V >> E >> idx1 >> idx2;

		for (int i = 1; i <= V; ++i)
		{
			Node& node = tree[i];
			node.parent = node.left = node.right = -1;
		}

		for (int i = 0; i < E; ++i)
		{
			int parent, child;
			std::cin >> parent >> child;
			
			Node& parentNode = tree[parent];
			Node& childNode = tree[child];

			if (parentNode.left == -1) parentNode.left = child;
			else parentNode.right = child;

			childNode.parent = parent;
		}

		int sharedParent = FindLowestCommonAncestor(idx1, idx2, tc);
		int subTreeSize = GetSubTreeSize(sharedParent);

		std::cout << "#" << tc << " " << sharedParent << " " << subTreeSize << "\n";
	}

	return 0;
}
