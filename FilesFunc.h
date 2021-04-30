#pragma once
#include <iostream>

bool setTextFolder(std::string fullPath);

std::string setHomeDir(char* argv);

void saveText(std::string& text, std::string path);

bool remove_line(const char* filename, size_t index);
