#include <iostream>
#include "inbuf.hpp"

int main()
{
		inbuf ib; // create special stream buffer
		std::istream in(&ib); // initialize input stream with that buffer

		char c;
		for (int i = 0; i <= 20; ++i)
		{
				// read next character (out of buffer)
				in.get(c);

				// print that character (and flush)
				std::cout << c << std::flush;

				// after eight characters, put two characters back into the stream
				if (i == 8)
				{
						in.unget();
						in.unget();
				}
		}	
		std::cout << std::endl;

		return 0;
}
