#include <iostream>
#include <string>

int main()
{
		const std::string s = "Keep out!";
		for (auto &c : s); // const char &
		return(0);
}
