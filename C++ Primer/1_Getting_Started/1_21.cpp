#include <iostream>
#include "Sales_item.h"

int main()
{
		Sales_item item1, item2;
		std::cin >> item1 >> item2;
		if (item1.isbn() == item2.isbn())
		{
				std::cout << item1 + item2 << std::endl;
				return(0);
		}
		else
		{
				std::cout << "Data must refer to same items" << std::endl;
				return(-1);
		}
}
