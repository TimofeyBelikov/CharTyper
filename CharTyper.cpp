#include <iostream>
#include <sstream>
#include <windows.h>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <string>
#include <ctime>
#include "SettingsUp.h"
#include "FilesFunc.h"

const int symbByRow = 96;
const bool debag = FALSE;
std::string Homedir;
HANDLE cConsole = GetStdHandle(STD_OUTPUT_HANDLE);


class Timer {
public:
	unsigned int start_time;
	unsigned int end_time;
	unsigned int search_time;
	void calcElapseTime() {
		this->search_time = end_time - start_time;
	}
	void getStartRec() {
		start_time = clock();
	}
	void getEndRec() {
		end_time = clock();
	}
	void convert() {
		search_time /= 1000;
	}
	int calcAvgSpeedPerMin(int amountOfChars) {
		return (int)(((float)amountOfChars / (float)search_time) * 60.0);
	}   
};

class Typer {
	Timer timer;
	std::string text;
	int misstakes = 0;
	int score = 0;
	int tempX = 5;
	int tempY = 4;
	
public:
	Typer(std::string* text) {
		this->text = *text;
		
	}
	
	void addPos() {
		tempX++;
		if (tempX > 96 - 1) {  //96- Символов в коммандной строке
			tempX = 0; tempY++;
		}
		return;
	}
	void addScore(char a) {
		if (a == '+') {
			score++;
			addPos();
		}
		else
		{
			misstakes++;
		}
		return;
	}
	int getCurrentPointer() {
		return (((tempY - 4) * 96) - 5 + tempX);	//96- символов в коммандной строке
	}
	void showStatusBar() {
		COORD statusBar = { 1,1 };          //Status position
		SetConsoleCursorPosition(cConsole, statusBar);
		float accuracy = (float)(misstakes) / ((float)(score / 100.0f));
		printf("Введено:%-4d\tОшибок:%-4d\t", score, misstakes);
		printf("Точность:%-4.1f  ", 100 - accuracy);
	}
	void showFinishPage() {	//In sec
		system("cls");
		std::cout << "\n\n\n\n\t\t\t\t\tResault: ";
		if (((this->timer.search_time) / 60) < 1) {
			std::cout << "\n\t\t\tСкорость: " <<timer.calcAvgSpeedPerMin(score)<< " Символов в минуту\n";
		}
		else
		{
			std::cout << "\n\t\t\tSpeed: " << timer.calcAvgSpeedPerMin(score) << " Символов в минуту\n";
		}
		std::cout << "\t\t\tВсего символов введено: " << score << "\n";
		system("pause");
	}
	void show() {
		system("cls");
		COORD start{ 5,4 };
		SetConsoleCursorPosition(cConsole,start); //temp-start
		std::cout << text;
		return;
	}
	int textEnter() {
		timer.getStartRec();
		int currChar = 0;
		
		int chr = 0;
		bool isPrevRight = true;
		int endSymbol=this->text.length();
		int currentSymbol = 0;
		COORD temp{ 0,0 };
		while (currentSymbol != endSymbol && (chr != 27))
		{
			temp.X = tempX;
			temp.Y = tempY;
			currChar = text[currentSymbol];
			SetConsoleCursorPosition(cConsole, temp);
			if (isPrevRight) {
				SetColor(15, 10);               //текст белый, фон зеленый.
				printf("%c", currChar);
			}
			else
			{
				SetColor(15, 12);               //текст белый, фон красный.
				printf("%c", currChar);
			}
			SetColor(0, 15);                //текст черный, фон белый.
			chr = _getch();
			if ((char)chr == (char)(text[currentSymbol])) {
				SetConsoleCursorPosition(cConsole, temp);
				SetColor(2, 15);    //текст зеленый, фон белый 
				printf("%c", currChar);
				if (isPrevRight) {
					addScore('+'); // && Pos++
				}
				else
				{
					addPos();
					isPrevRight = TRUE;
				}
				currentSymbol++;
			}
			else
			{
				if (isPrevRight) {
					addScore('-');
				}
				isPrevRight = FALSE;
			}
			SetColor(0, 15);
			showStatusBar();
		}
		timer.getEndRec();
		timer.calcElapseTime();
		timer.convert();
		return score;
	}
	int getScore() {
		return score;
	}
	std::string& getText() { return text; }
};

void addToList(std::string filename) { //Требуется HomeDir
	std::ofstream record;
	record.open(Homedir + "\\List.txt", std::ios_base::app);

	if (!record.is_open()) {
		std::cout << "Fail add to list";
		system("pause");
	}
	else {
		record << filename << std::endl;
		record.close();
	}
}

std::string loadText(std::string filename) {	//Возвращает текст, хранящийся по имени
	std::string tempString;
	char buffer[50];
	std::ifstream file;
	file.open(Homedir + filename + ".txt");
	if (!file.is_open()) {
		std::cout << "Fail open text file";
		file.close();
	}
	else
	{
		while (!file.eof())
		{
			file >> buffer;
			tempString += buffer;
			tempString += " ";
		}
		tempString.erase(tempString.length() - 1, 1);
	}
	file.close();
 return tempString;
}

int getlenght(std::string dir) {
	std::ifstream in;
	in.open(dir);
	in.seekg(0, std::ios_base::end);
	int lenght = in.tellg();
	in.close();
	return lenght;
}

void loadPreview(std::string dir) {
	char tempString[50];
	std::string temp;
	std::ifstream out;
	out.open(dir);
	if (!out.is_open()) std::cout << "load preview fail...";
	else {
		out.getline(tempString, 50);
		if (out.eof()) {
			printf("%-49s   \t", tempString);
		}
		else
		{
			printf("%s", tempString);
			std::cout << "...\t";
		}
	}
	out.close();
	printf("%d", getlenght(dir));
}

int catchInput() {
	int ch;
	while (1) {
		ch = _getch();
		if (ch == 13) return 13;
		if (ch == 27) return 27;
		if (ch == 0 || ch == 224)
		{
			return _getch();
		}
	}
}

int textSelection(int amount, int shift) {
	COORD pos{ 0,0 };
	COORD tempPos{ 0,0 };
	int select = 1;
	while (true) {
		SetColor(2, 15);
		SetConsoleCursorPosition(cConsole, pos);
		printf(">");
		SetColor(0, 15);
		switch (catchInput())
		{
		case 72:   //arrow up
			if (pos.Y == 0) {}
			else
			{
				select -= 1;
				tempPos.Y = pos.Y;
				pos.Y -= shift;
			}
			break;
		case 80: //arrow down
			if (pos.Y >= ((amount - 1) * shift));
			else
			{
				select += 1;
				tempPos.Y = pos.Y;
				pos.Y += shift;
			}
			break;
		case 13:   //enter
			return select;
			break;
		case 83: //del
			if (select != amount) {
				return  (-1 * select);
			}
			break;
		case 27:	//esc
			exit(0);
			break;
		}
		SetColor(15, 15);
		SetConsoleCursorPosition(cConsole, tempPos);
		printf(" ");

	}

}

std::string getlist() {
	while (1) {
		system("cls");
		std::string buff,buff2; 
		std::ifstream list;
		
		list.open(Homedir + "List.txt");
		int amount = 0;			//Количество загруженных текстов
		int shift = 2;			//Межстрочное расстояние в меню
		if (!list.is_open()) {
			std::cout << "Getlist open dir fail. "<<Homedir+"List.txt" ;
		}
		else
		{
			while (!list.eof())
			{
				int leftBorder = 0;
				std::string convertedName;
				getline(list, buff);
				if (!list.eof()) {
					buff2 = buff;
					buff2.resize(12,' ');
					printf(" %12s ", buff2.c_str());
					
					std::cout << "\t#\t"; loadPreview(Homedir + buff + ".txt");    //загрузить предпросмотр
					//printf("#\t"); loadPreview(Homedir + buff + ".txt");    //загрузить предпросмотр
					amount++;
					for (int i = shift; i > 0; i--) {
						std::cout << "\n";
					}
				}
			}
			amount++;
			printf(" %10s", "[Добавить текст]");
		}

		list.close();
		list.seekg(0);
		list.open(Homedir + "List.txt");
		int k = textSelection(amount, shift);   //получение выбранного пункта 


		if (k == amount) {
			//Если выбран пункт ДОБАВИТЬ ТЕКСТ
			return "";
		}
		if (k < 0) {    //Удаление записи о тексте в файле Texts.txt
			k *= -1;
			for (int i = 1; i < k; i++) {
				getline(list, buff);
			}
			getline(list, buff);
			list.close();
			remove_line((Homedir + "List.txt").c_str(), k - 1);
			std::remove((Homedir + buff + ".txt").c_str());
			amount--;

		}
		else
		{
			for (int i = 1; i < k; i++) {
				getline(list, buff);
			}
			getline(list, buff);
			list.close();
			return buff;
		}


	}
}

int main(int argc, char* argv[]) {

	

	SetColor(0, 15);
	Homedir = setHomeDir(argv[0]);
	
	CONSOLE_FONT_INFOEX* cfi;    cfi = new CONSOLE_FONT_INFOEX;
	CONSOLE_CURSOR_INFO* cursor; cursor = new CONSOLE_CURSOR_INFO;

	setUpFont(cfi, cursor);
	//system("chcp 1251");

	/* Вывод информации о размерах консольного окна
	CONSOLE_SCREEN_BUFFER_INFO information;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &information);
	std::cout << "X: " << information.dwSize.X << " Y:" << information.dwSize.Y << "\n";
	system("pause");
	*/


	int choise = 0;
	Typer* typer;
	while (choise != 27)	//Пока в меню не будет нажата кнопка выхода- ESC	
	{
		std::string buff = getlist();    
		if (buff != "") {
			std::string ffile;
			ffile=loadText(buff);
			Typer type(&ffile);
			//Typer type(&loadText(buff));
			type.show();
			type.textEnter();
			type.showFinishPage();
		}
		else {	
			//Ветка с добавлением нового текста.
			system("cls");
			std::string texts;
			std::cout << ("Type your text: ");
			std::getline(std::cin, texts); //Ввод текста 
			Sleep(2000);
			system("cls");
			std::cout << "Type text name: ";
			std::string name;
			std::getline(std::cin, name);				    //ввод имени
			Typer type(&texts);
			type.show();
			type.textEnter();
			type.showFinishPage();
			saveText(type.getText(), Homedir + name + ".txt");
			addToList(name);
		}
	}
	return 0;
}
