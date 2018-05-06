#include <map>
#include <iostream>
#include <algorithm>
#include <utility>

int main()
{
		// map with floats as key and value
		// - initializing keys and values are automatically converted to float
		std::map<float, float> coll = { {1, 7}, {2, 4}, {3, 2}, {4, 3}, {5, 6}, {6, 1}, {7, 3}};

		// search an element with key 3.0 (logarithmic complexity)
		std::map<float, float>::iterator posKey = coll.find(3.0);
		if (posKey != coll.end())
		{
				std::cout << "key 3.0 found ("
						  << posKey->first << ":"
						  << posKey->second << ")" << std::endl;
		}

		// search an element with value 3.0 (linear complexity)
		std::map<float, float>::iterator posVal = std::find_if(coll.begin(), coll.end(), [] (const std::pair<float, float>& elem) { return elem.second == 3.0; });
		if (posVal != coll.end())
		{
				std::cout << "value 3.0 found ("
					      << posVal->first << ":"
						  << posVal->second << ")" << std::endl;
		}
		return 0;
}
