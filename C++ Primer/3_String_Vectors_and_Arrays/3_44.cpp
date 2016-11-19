#include <iostream>
typedef int int_arr[4];
typedef int (*int_ptr)[4];

int main()
{
		int ia[3][4] = {
				{0, 1, 2, 3},
				{4, 5, 6, 7},
				{8, 9, 10, 11}
		};

		for (int_arr &p : ia)
		{
				for (int i : p)
						std::cout << i << " ";
				std::cout << std::endl;
		}
		std::cout << std::endl;

		for (int i = 0; i < 3; i++)
		{
				for (int j = 0; j < 4; j++)
						std::cout << ia[i][j] << " ";
				std::cout << std::endl;
		}
		std::cout << std::endl;

		for (int_ptr p = ia; p != ia + 3; ++p)
		{
				for (int *i = *p; i != *p + 4; ++i)
						std::cout << *i << " ";
				std::cout << std::endl;
		}

		return(0);
}
