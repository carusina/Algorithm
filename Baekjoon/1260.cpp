#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

void DFS(const std::vector<std::vector<int>>& Edges, const int V);
void BFS(const std::vector<std::vector<int>>& Edges, const int V);

std::vector<bool> visited;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int N = 0, M = 0, V = 0;
    std::cin >> N >> M >> V;

    std::vector<std::vector<int>> Edges(N + 1);
    visited.resize(N + 1, false);

    for(int i = 0; i < M; ++i)
    {
        int v1 = 0, v2 = 0;
        std::cin >> v1 >> v2;

        Edges[v1].push_back(v2);
        Edges[v2].push_back(v1);
    }
    
    for(int i = 1; i <= N; ++i)
    {
        sort(Edges[i].begin(), Edges[i].end());
    }

    DFS(Edges, V);
    std::cout << "\n";

    std::fill(visited.begin(), visited.end(), false);

    BFS(Edges, V);
    std::cout << "\n";

    return 0;
}

void DFS(const std::vector<std::vector<int>>& Edges, const int V)
{
    visited[V] = true;
    std::cout << V << " ";

    for(int next : Edges[V])
    {
        if(!visited[next])
        {
            DFS(Edges, next);
        }
    }
}

void BFS(const std::vector<std::vector<int>>& Edges, const int V)
{
    std::queue<int> q;

    q.push(V);
    visited[V] = true;

    while(!q.empty())
    {
        int now = q.front();
        q.pop();

        std::cout << now << " ";

        for(int next : Edges[now])
        {
            if(!visited[next])
            {
                visited[next] = true;
                q.push(next);
            }
        }
    }
}