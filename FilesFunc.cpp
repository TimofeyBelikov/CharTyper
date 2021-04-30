#include "FilesFunc.h"
#include <direct.h>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>

bool setTextFolder(std::string fullPath) {
	if (!_mkdir(fullPath.c_str())) {
		std::cout << "ok";
		std::ofstream output;
		output.open(fullPath + "List.txt");
		output.close();
		return true;
	}
	else
	{
		return false;
	}
}

std::string setHomeDir(char* argv) {
	std::string fullPath = argv;
	fullPath.erase(fullPath.find_last_of("\\") + 1, fullPath.length() - fullPath.find_last_of("\\"));
	fullPath += "Texts\\";
	setTextFolder(fullPath);
	return fullPath;
};

bool remove_line(const char* filename, size_t index)
{
	std::vector<std::string> vec;
	std::ifstream file(filename);
	if (file.is_open())
	{
		std::string str;
		while (std::getline(file, str))
			vec.push_back(str);
		file.close();
		if (vec.size() < index)
			return false;
		vec.erase(vec.begin() + index);
		std::ofstream outfile(filename);
		if (outfile.is_open())
		{
			std::copy(vec.begin(), vec.end(),
				std::ostream_iterator<std::string>(outfile, "\n"));
			outfile.close();
			return true;
		}
		return false;
	}
	return false;
}

void saveText(std::string& text, std::string path) {
	std::ofstream output;
	output.open(path);
	output << text;
	output.close();
}
