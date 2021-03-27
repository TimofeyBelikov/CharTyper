#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <fstream>
#include "SettingsUp.h"
#include "FilesFunc.h"

HANDLE cConsole = GetStdHandle(STD_OUTPUT_HANDLE);
std::string HomeDir;



int main(int argc, char* argv[]) {
	HomeDir = setHomeDir(argv[0]);

	CONSOLE_FONT_INFOEX* cfi; cfi = new CONSOLE_FONT_INFOEX;
	CONSOLE_CURSOR_INFO* cursor; cursor = new CONSOLE_CURSOR_INFO;	
	
	setUpFont(cfi, cursor);
	


	
	return 0;
}