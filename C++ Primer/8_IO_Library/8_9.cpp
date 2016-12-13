#include <iostream>
#include <sstream>

std::istream& read(std::istream& is)
{
		std::cout << "\nCalling read" << std::endl;
		std::string s;
		while(is >> s)
				std::cout << s << "\n";
		is.clear();
		return is;
}

int main()
{
		std::istringstream is("I am istringstream");
		read(is);
		return 0;
}
