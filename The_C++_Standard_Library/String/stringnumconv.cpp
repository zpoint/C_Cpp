#include <string>
#include <iostream>
#include <limits>
#include <exception>

int main()
{
		try
		{
				// convert to numeric type
				std::cout << std::stoi(" 77") << std::endl;
				std::cout << std::stod(" 77.7") << std::endl;
				std::cout << std::stoi("-0x77") << std::endl;

				// use index of characters not processed
				std::size_t idx;
				std::cout << std::stoi(" 42 is the truth", &idx) << std::endl;
				std::cout << " idx of first unprocessed char: " << idx << std::endl;

				// use base 16 and 8
				std::cout << std::stoi(" 42", nullptr, 16) << std::endl;
				std::cout << std::stol("789", &idx, 8) << std::endl;
				std::cout << " idx of first unprocessed char: " << idx << std::endl;

				// convert nuymeric value to string
				long long ll = std::numeric_limits<long long>::max();
				std::string s = std::to_string(ll); // convert maximum long long to string
				std::cout << s << std::endl;

				// try to convert back
				std::cout << std::stoi(s) << std::endl; // throw out_of_range
		}
		catch (const std::exception& e)
		{
				std::cout << e.what() << std::endl;
		}

		return 0;
}
