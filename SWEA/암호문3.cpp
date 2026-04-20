// https://swexpertacademy.com/main/talk/solvingClub/problemView.do?contestProbId=AV14zIwqAHwCFAYD&solveclubId=AZwrPjFqFyDHBIT3&problemBoxTitle=1%EC%A3%BC%EC%B0%A8&problemBoxCnt=6&probBoxId=AZwrPjFqFyHHBIT3

#include <iostream>

// ====================
// 상수 선언
// ====================

#define MAX_N 500000
#define RESULT_COUNT 10

// ====================
// 구조체 선언
// ====================

struct Node
{
	int num;
	Node* prev;
	Node* next;
};

// ====================
// 전역 변수
// ====================

Node* head;
Node* tail;

int nodeCount;
Node nodePool[MAX_N + 2];

// ====================
// 유틸 함수
// ====================

void Init()
{
	nodeCount = 0;

	head = &nodePool[MAX_N];
	tail = &nodePool[MAX_N + 1];

	head->prev = nullptr;
	head->next = tail;

	tail->prev = head;
	tail->next = nullptr;
}

Node* AllocateNode(int num)
{
	Node& node = nodePool[nodeCount++];

	node.num = num;
	node.prev = nullptr;
	node.next = nullptr;

	return &node;
}

// ====================
// 명령어 함수
// ====================

void Insert(int offset, int count)
{
	Node* prev = head;
	while (offset--)
	{
		prev = prev->next;
	}
	Node* next = prev->next;

	for (int i = 0; i < count; ++i)
	{
		int num;
		std::cin >> num;
		Node* node = AllocateNode(num);

		prev->next = node;
		node->prev = prev;
		
		prev = node;
	}
	prev->next = next;
	next->prev = prev;
}

void Delete(int offset, int count)
{
	Node* prev = head;
	while (offset--)
	{
		prev = prev->next;
	}

	Node* next = prev->next;
	while (count--)
	{
		next = next->next;
	}

	prev->next = next;
	next->prev = prev;
}

void Append(int count)
{
	Node* prev = tail->prev;
	for (int i = 0; i < count; ++i)
	{
		int num;
		std::cin >> num;
		Node* node = AllocateNode(num);

		prev->next = node;
		node->prev = prev;

		prev = node;
	}
	prev->next = tail;
	tail->prev = prev;
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
		Init();

		int N;
		std::cin >> N;
		
		Node* prev = head;
		for (int i = 0; i < N; ++i)
		{
			int num;
			std::cin >> num;
			Node* node = AllocateNode(num);

			prev->next = node;
			node->prev = prev;
			
			prev = node;
		}
		prev->next = tail;
		tail->prev = prev;

		int M;
		std::cin >> M;
		for (int i = 0; i < M; ++i)
		{
			char cmd;
			std::cin >> cmd;

			switch (cmd)
			{
				case 'I':
				{
					int x, y;
					std::cin >> x >> y;
					Insert(x, y);
					break;
				}
				case 'D':
				{
					int x, y;
					std::cin >> x >> y;
					Delete(x, y);
					break;
				}
				case 'A':
				{
					int y;
					std::cin >> y;
					Append(y);
					break;
				}
			}
		}

		std::cout << "#" << tc << " ";

		Node* curr = head->next;
		for (int i = 0; i < RESULT_COUNT; ++i)
		{
			std::cout << curr->num << " ";
			curr = curr->next;
		}
		std::cout << "\n";
	}

	return 0;
}
