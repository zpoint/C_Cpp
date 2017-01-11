#include <map>
#include <string>
#include <iostream>

int main()
{
		std::map<std::string, std::string> family;
		std::string family_name, children_name;
		while (std::cin >> family_name >> children_name)
				family[family_name] = children_name;
		for (const auto &i : family)
				std::cout << i.first << ": " << i.second << "\n";
		std::cout << std::endl;
		return 0;
}
