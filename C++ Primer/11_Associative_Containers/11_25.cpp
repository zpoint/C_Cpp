#include <vector>
#include <iostream>

int main()
{
		std::vector<int> v;
		v.push_back(2);
		v[0] = 1;
		for (const auto &i : v)
				std::cout << i << " " << std::endl;
		return 0;
}
