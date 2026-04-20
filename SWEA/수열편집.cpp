// https://swexpertacademy.com/main/talk/solvingClub/problemView.do?contestProbId=AX5MBiQqAbQDFASv&solveclubId=AZwrPjFqFyDHBIT3&problemBoxTitle=1%EC%A3%BC%EC%B0%A8&problemBoxCnt=6&probBoxId=AZwrPjFqFyHHBIT3

#include <iostream>

// ====================
// 상수 선언
// ====================

#define MAX_N 1000
#define MAX_M 1000

// ====================
// 구조체 선언
// ====================

struct Node
{
	int data;
	Node* prev;
	Node* next;
};

// ====================
// 전역 변수
// ====================

int nodeCount;
Node nodePool[MAX_N + MAX_M + 2];

Node* head;
Node* tail;

// ====================
// 유틸 함수
// ====================

void Init()
{
	nodeCount = 0;

	head = &nodePool[MAX_N + MAX_M];
	tail = &nodePool[MAX_N + MAX_M + 1];

	head->prev = nullptr;
	head->next = tail;

	tail->prev = head;
	tail->next = nullptr;
}

Node* AllocateNode(int data)
{
	Node* node = &nodePool[nodeCount++];
	node->data = data;
	node->prev = nullptr;
	node->next = nullptr;

	return node;
}

// ====================
// 편집 함수
// ====================

void Insert(int targetIndex, int data)
{
	Node* prev = head;
	while (targetIndex--)
	{
		prev = prev->next;
	}
	Node* next = prev->next;

	Node* node = AllocateNode(data);
	prev->next = node;
	node->prev = prev;
	node->next = next;
	next->prev = node;
}

void Delete(int targetIndex)
{
	Node* curr = head->next;
	while (targetIndex--)
	{
		curr = curr->next;
	}
	Node* prev = curr->prev;
	Node* next = curr->next;

	prev->next = next;
	next->prev = prev;
}

void Change(int targetIndex, int data)
{
	Node* curr = head->next;
	while (targetIndex--)
	{
		curr = curr->next;
	}

	curr->data = data;
}

int GetDataAt(int index)
{
	Node* curr = head->next;
	while (index-- && curr != tail)
	{
		curr = curr->next;
	}

	return (curr != tail) ? curr->data : -1;
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
		Init();

		int N, M, L;
		std::cin >> N >> M >> L;

		Node* prev = head;
		for (int i = 0; i < N; ++i)
		{
			int data;
			std::cin >> data;
			Node* node = AllocateNode(data);
			prev->next = node;
			node->prev = prev;

			prev = node;
		}
		prev->next = tail;
		tail->prev = prev;

		for (int i = 0; i < M; ++i)
		{
			char cmd;
			std::cin >> cmd;
			
			switch (cmd)
			{
				case 'I':
				{
					int targetIndex, data;
					std::cin >> targetIndex >> data;
					Insert(targetIndex, data);
					break;
				}
				case 'D':
				{
					int targetIndex;
					std::cin >> targetIndex;
					Delete(targetIndex);
					break;
				}
				case 'C':
				{
					int targetIndex, data;
					std::cin >> targetIndex >> data;
					Change(targetIndex, data);
					break;
				}
			}
		}

		std::cout << "#" << tc << " " << GetDataAt(L) << "\n";
	}

	return 0;
}
