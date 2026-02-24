#include <iostream>
#include <string>
#include <algorithm>

constexpr int MAX_LEN = 1001;

int dp[MAX_LEN][MAX_LEN];

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::string str1, str2;
	std::cin >> str1 >> str2;

	int len1 = str1.length();
	int len2 = str2.length();

	for (int i = 1; i <= len1; ++i)
	{
		for(int j = 1; j <= len2; ++j)
		{ 
			if (str1[i - 1] == str2[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else
			{
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	std::cout << dp[len1][len2];

	return 0;
}
