#include <iostream>
#include <string>

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::string input;
	std::cin >> input;

	int result = 0;
	std::string num = "";
	bool isMinusFound = false;

	for (int i = 0; i <= input.size(); ++i)
	{
		if (i == input.size() || input[i] == '+' || input[i] == '-')
		{
			if (isMinusFound)
			{
				result -= std::stoi(num);
			}
			else
			{
				result += std::stoi(num);
			}

			num = "";

			if (i < input.size() && input[i] == '-')
			{
				isMinusFound = true;
			}
		}
		else
		{
			num += input[i];
		}
	}

	std::cout << result;

	return 0;
}
