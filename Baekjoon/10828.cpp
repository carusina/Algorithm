#include <iostream>
#include <string>
#include <vector>

void Stack(int N);

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N = 0;
    std::cin >> N;

    Stack(N);
    
    return 0;
}

void Stack(int N)
{
    std::vector<int> s;

    for(int i = 0; i < N; ++i)
    {
        std::string cmd;

        std::cin >> cmd;
        if(cmd == "push")
        {
            int x = -1;
            std::cin >> x;

            s.push_back(x);
        }
        else if(cmd == "pop")
        {
            if(s.size() > 0)
            {
                std::cout << s[s.size() - 1] << "\n";
                s.pop_back();
            }
            else
            {
                std::cout << "-1\n";
            }
        }
        else if(cmd == "size")
        {
            std::cout << s.size() << "\n";
        }
        else if(cmd == "empty")
        {
            if(s.size() > 0)
            {
                std::cout << "0\n";
            }
            else
            {
                std::cout << "1\n";
            }
        }
        else if(cmd == "top")
        {
            if(s.size() > 0)
            {
                std::cout << s[s.size() - 1] << "\n";
            }
            else
            {
                std::cout << "-1\n";
            }
        }
    }
}