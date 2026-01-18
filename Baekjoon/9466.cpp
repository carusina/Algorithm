#include <iostream>
#include <vector>
#include <queue>

int BFS(const std::vector<int>& s, std::vector<int> indegree);

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int T = 0;
    std::cin >> T;

    for(int test_case = 1; test_case <= T; ++test_case)
    {
        int n;
        std::cin >> n;

        std::vector<int> s(n + 1, 0);
        std::vector<int> indegree(n + 1, 0);
        for(int i = 1; i <= n; ++i)
        {
            std::cin >> s[i];
            indegree[s[i]]++;
        }

        std::cout << BFS(s, indegree) << "\n";
    }

    return 0;
}

int BFS(const std::vector<int>& s, std::vector<int> indegree)
{
    int n = s.size() - 1;

    std::queue<int> q;
    for(int i = 1; i <= n; ++i)
    {
        if(indegree[i] == 0)
        {
            q.push(i);
        }
    }

    int cnt = 0;

    while(!q.empty())
    {
        int curr = q.front();
        q.pop();
        cnt++;

        int next = s[curr];
        indegree[next]--;

        if(indegree[next] == 0)
        {
            q.push(next);
        }
    }

    return cnt;
}