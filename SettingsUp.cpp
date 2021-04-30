#include "SettingsUp.h"
extern HANDLE cConsole;

void SetColor(int text, int bg) {
	SetConsoleTextAttribute(cConsole, (WORD)((bg << 4) | text));
	return;
}

void setUpFont(CONSOLE_FONT_INFOEX* cfi, CONSOLE_CURSOR_INFO* cursor) {
	SetConsoleDisplayMode(cConsole, CONSOLE_FULLSCREEN_MODE, (PCOORD)(0, 0));
	cursor->bVisible = false;
	cursor->dwSize = 99;
	SetConsoleCursorInfo(cConsole, cursor);

	cfi->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfi->nFont = 0;
	cfi->dwFontSize.X = 14;
	cfi->dwFontSize.Y = 25;

	cfi->FontFamily = FF_DONTCARE;
	cfi->FontWeight = 400;
	SetCurrentConsoleFontEx(cConsole, FALSE, cfi);
	SetConsoleCP(1251);         // установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);
	system("mode con cols=96 lines=25");
	setlocale(LC_CTYPE, "rus");
	return;
}
