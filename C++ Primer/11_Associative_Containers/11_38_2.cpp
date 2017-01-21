#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

std::unordered_map<std::string, std::string> buildMap(std::ifstream &input_file)
{
		std::unordered_map<std::string, std::string> trans_map;
		std::string key;
		std::string value;
		while (input_file >> key && std::getline(input_file, value))
				if (value.size() > 1)
						trans_map[key] = value.substr(1);
				else
						throw std::runtime_error("no rulue for " + key);
		return trans_map;
}

const std::string & transform(const std::string &s, const std::unordered_map<std::string, std::string> &m)
{
		auto map_it = m.find(s);
		if (map_it != m.cend())
				return map_it->second;
		else
				return s;
}

void word_transform(std::ifstream &map_file, std::ifstream &input)
{
		auto trans_map = buildMap(map_file);
		std::string text;
		while (std::getline(input, text))
		{
				std::istringstream stream(text);
				std::string word;
				bool firstword = true;
				while (stream >> word)
				{
						if (firstword)
								firstword = false;
						else
								std::cout << " ";
						std::cout << transform(word, trans_map);
				}
				std::cout << std::endl;
		}
}



int main(int argc, char **argv)
{
		assert (argc == 3);
		std::ifstream rule_file(argv[1]), output_file(argv[2]);
		word_transform(rule_file, output_file);
		return 0;
}
