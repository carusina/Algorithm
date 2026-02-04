#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <set>

const int INF = 0x3f3f3f3f;

int N, R; // 도시 개수, 내일로 티켓 가격
int M;    // 여행할 도시 개수
int K;    // 교통수단 개수

int cityIndex = 0;                    // 도시 인덱스
std::map<std::string, int> city2idx;  // 도시 인덱스 변환
std::vector<int> path;                // 여행 경로

int dist[2][100][100];		          // 교통수단 비용, 0: 내일로X / 1: 내일로O

const std::set<std::string> FREE_TYPES = { "Mugunghwa", "ITX-Saemaeul", "ITX-Cheongchun" };
const std::set<std::string> HALF_TYPES = { "S-Train", "V-Train" };

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> N >> R;
	R *= 2;

	for (int i = 0; i < N; ++i)
	{
		std::string city;
		std::cin >> city;

		if (city2idx.find(city) == city2idx.end())
		{
			city2idx[city] = cityIndex++;
		}
	}
	
	std::cin >> M;
	for (int i = 0; i < M; ++i)
	{
		std::string city;
		std::cin >> city;

		path.push_back(city2idx[city]);
	}

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (i == j)
			{
				dist[0][i][j] = 0;
				dist[1][i][j] = 0;
			}
			else
			{
				dist[0][i][j] = INF;
				dist[1][i][j] = INF;
			}
		}
	}

	std::cin >> K;
	for (int i = 0; i < K; ++i)
	{
		std::string type, src, dest;
		int cost;
		std::cin >> type >> src >> dest >> cost;

		cost *= 2;
		
		int u = city2idx[src];
		int v = city2idx[dest];

		int ticketCost = cost;

		if (FREE_TYPES.count(type))
		{
			ticketCost = 0;
		}
		else if (HALF_TYPES.count(type))
		{
			ticketCost = cost / 2;
		}

		dist[0][u][v] = std::min(dist[0][u][v], cost);
		dist[0][v][u] = std::min(dist[0][v][u], cost);

		dist[1][u][v] = std::min(dist[1][u][v], ticketCost);
		dist[1][v][u] = std::min(dist[1][v][u], ticketCost);
	}

	for (int k = 0; k < N; ++k)
	{
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				dist[0][i][j] = std::min(dist[0][i][j], dist[0][i][k] + dist[0][k][j]);
				dist[1][i][j] = std::min(dist[1][i][j], dist[1][i][k] + dist[1][k][j]);
			}
		}
	}

	int totalNoTicketCost = 0;
	int totalTicketCost = R;

	for (int i = 0; i < M - 1; ++i)
	{
		int u = path[i];
		int v = path[i + 1];

		totalNoTicketCost += dist[0][u][v];
		totalTicketCost += dist[1][u][v];
	}

	std::cout << (totalNoTicketCost <= totalTicketCost ? "No" : "Yes");

	return 0;
}
