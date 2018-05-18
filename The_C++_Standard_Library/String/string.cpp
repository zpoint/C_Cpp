#include <iostream>
#include <string>

int main(int argc, char **argv)
{
		std::string filename, basename, extname, tmpname;
		const std::string suffix("tmp");

		// for each command-line argument (which is an ordinary C-string)
		for (int i = 0; i < argc; ++i)
		{
				// process argument as filename
				filename = argv[i];

				// search period in filename
				std::string::size_type idx = filename.find('.');
				if (idx == std::string::npos)
				{
						// filename does not contain any period
						tmpname = filename + '.' + suffix;
				}
				else
				{
						// split filename into base name and extension
						// - base name contains all characters before the period
						// - extension contains all characters after the period
						basename = filename.substr(0, idx);
						extname = filename.substr(idx + 1);
						if (extname.empty())
						{
								// contains period but no extension: append tmp
								tmpname = filename;
								tmpname += suffix;
						}
						else if (extname == suffix)
						{
								// replace extension tmp with xxx
								tmpname = filename;
								tmpname.replace(idx + 1, extname.size(), "xxx");
						}
						else
						{
								// replace any extension with tmp
								tmpname = filename;
								tmpname.replace(idx + 1, std::string::npos, suffix);
						}
				}

				// print filename and temporary name
				std::cout << filename << " => " << tmpname << std::endl;
		}

		return 0;
}
