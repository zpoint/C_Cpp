#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

template <typename T>
void PRINT_ELEMENTS(const T& CONTAINER, const std::string& tip="")
{
		std::cout << tip << ": ";
		for (const auto& i : CONTAINER)
				std::cout << i << " ";
		std::cout << std::endl;
}

int square(int value)
{
		return value * value;
}

int main()
{
		std::set<int> coll1;
		std::vector<int> coll2;

		// insert elements from 1 to 9 into coll1
		for (int i=0; i<=9; ++i)
				coll1.insert(i);
		PRINT_ELEMENTS(coll1, "initialized:\t");

		// transform each element from coll1 to coll2
		// - square transformed values
		std::transform(coll1.cbegin(), coll1.cend(), std::back_inserter(coll2), square);
		PRINT_ELEMENTS(coll2, "squared:\t");
		return 0;
}
