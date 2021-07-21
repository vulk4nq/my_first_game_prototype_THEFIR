#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <conio.h>
#include <string>
#include <WinUser.h>
#pragma comment(lib, "user32.lib")
void update();
using namespace std;
int theme = 0;
int level_exp[15] = { 15,30,50,80,140,300,500,800,1300,2500,4000, 5800,7500,10000,150000 };
int count_obj = 0;
class Items
{
public:
	int cost;
	int type;//0-weapon 1 - head 2-chest 3-arms 4-legs 5-bo0ts
	string name;
	int id;
	int damage;
	int health;
	int armor;
	int magic;
	int stabil;
	int agility;
	int strength;
	int crit;
	int iq;
	int color;//1 - red 2- blue 3 - green 4 - cyan

	
}Item[100];

class Player
{
public:
	int x;
	float strength;
	float iq;
	float agility;
	float spelwords;
	int y;
	int loc;
	int level;//loc level
	int dopusk;
	string name;
	int lvl;
	int exp;
	string Class;
	string race;
	int money;
	Items inventory[20];
	int inventory_last;
	Items equipment[6];
	int map;
	int good;
	int bad;
	int neutral;
	int difficulty;
	
	int mainQProgress[100][100];
}player;
class buttons
{
public:
	bool pressed;
}button0_1;
class Town
{
public:
	int x;
	int y;
	
	int level;
}broghird,clounto_ridge,orzodh,ghedg;

class Chars
{
public:
	int id;
	int x;
	int y;
	char Char;
	int level;
	int loc;
	int color;//1 - red 2- blue 3 - green 4 - cyan;
	bool IsAlive;
	bool Movable;
	int xDest;
	int yDest;
	bool IsHeWantToSpeak;
}Objects[100];


void set_towns_coordinate()
{
	broghird.x = 80; orzodh.x = broghird.x + 9; clounto_ridge.x = orzodh.x - 35; ghedg.x = clounto_ridge.x + 7;
	broghird.y = 24; orzodh.y = broghird.y - 8; clounto_ridge.y = orzodh.y + 1; ghedg.y = broghird.y + 11;
}

void setColor(int color)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (color)
	{
	case 0:
	case 1:
		if (theme == 0)
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
		else SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);//red
		break;
	case 2:
		
		if (theme == 0)
			SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
		else SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);//blue
		break;
	case 3:
		
		if (theme == 0)
			SetConsoleTextAttribute(hStdOut, 2);
		else SetConsoleTextAttribute(hStdOut, 2 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);//green
		break;
	case 4:
		if (theme == 0)
			SetConsoleTextAttribute(hStdOut, 3);
		else SetConsoleTextAttribute(hStdOut, 3 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);//cyan
		break;
	default:
		break;
	}
}
void setTextBack()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (theme == 0)
		SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	else SetConsoleTextAttribute(hStdOut, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}
void setTextYellow()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (theme == 0)
		SetConsoleTextAttribute(hStdOut, 6);
	else SetConsoleTextAttribute(hStdOut, 6 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void SystemMessage(string Message)
{
	gotoxy(1, 32);
	cout << Message;
	Sleep(1000);
	gotoxy(1, 32);
	for (int i = 0; i <= Message.length(); i++)
	{
		cout << " ";
	}
}

void printCharS()
{
	for (int i = 0; i < 100; i++)
	{
		gotoxy(Objects[i].x, Objects[i].y);
		if (Objects[i].level == player.level && Objects[i].loc == player.loc && Objects[i].IsAlive)
		{
			setColor(Objects[i].color);
			cout << Objects[i].Char;
			setTextBack();
		}
	}
	gotoxy(player.x, player.y);
}
void loadLevelBase(string fileName)    /// Function which loads static level walls from text file
{
	string getContent;
	ifstream openfile(fileName.c_str());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	if (openfile.is_open())
	{
		while (!openfile.eof())
		{
			getline(openfile, getContent);
			setTextBack();
			cout << getContent << endl;
		}
	}
}
void loadLoc(int loc, int level)
{
	string path = "\levels\\\\loc.txt";
	path.insert(7, to_string(level));
	path.insert(11 + to_string(level).length(), to_string(loc));
	gotoxy(0, 0);
	loadLevelBase(path);
	player.loc = loc;
	printCharS();


}

void setTextRed()
{

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (theme == 0)
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	else SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}
void setTextBlue()
{

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (theme == 0)
		SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
	else SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}
void setTextGreen()
{

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (theme == 0)
		SetConsoleTextAttribute(hStdOut, 2);
	else SetConsoleTextAttribute(hStdOut, 2 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}
void setTextCyan()
{

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (theme == 0)
		SetConsoleTextAttribute(hStdOut, 3);
	else SetConsoleTextAttribute(hStdOut, 3 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}
void startPoint(int x, int y)
{
	player.x = x;
	player.y = y;
	
}

void changeloc(char key)
{
	if (key == 'w')
	{
		if (player.loc != 1 && player.loc != 2 && player.loc != 3)
		{
			player.loc -= 3;
			loadLoc(player.loc, player.level);
			startPoint(player.x, 31);
			player.y = 31;
			gotoxy(player.x, player.y);
			
		}

	}
	if (key == 's')
	{
		
		if (player.loc != 7 && player.loc != 8 && player.loc != 9)
		{
			player.y = 0;
			player.loc += 3;
			loadLoc(player.loc, player.level);
			startPoint(player.x, 0);
			gotoxy(player.x, player.y);
			
		}
	}
	if (key == 'a')
	{
		if (player.loc != 1 && player.loc != 4 && player.loc != 7)
		{
			player.x = 127;
			player.loc -= 1;
			loadLoc(player.loc, player.level);
			startPoint(127, player.y);
			gotoxy(player.x, player.y);
			
		}
	}
	if (key == 'd')
	{
		if (player.loc != 3 && player.loc != 6 && player.loc != 9)
		{
			player.x = 0;
			player.loc += 1;
			loadLoc(player.loc, player.level);
			startPoint(0, player.y);
			gotoxy(player.x, player.y);
			
		}
	}
}
void paintRiversAndGrass()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	TCHAR wAttrib = 0;
	COORD coord;
	coord.X = 0; coord.Y = 0;
	DWORD dwReaden = 0;
	char w;
	int i = 0;
	while (i != 145 * 54)
	{
		coord.X = i % 145; coord.Y = i / 145;
		ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), &wAttrib, 1, coord, &dwReaden);
		gotoxy(i % 145, i / 145);
		w = wAttrib;
		switch (wAttrib)
		{
		case '/':
		case '\\':
		case '|':
		case '_':setTextBlue(); cout << w; setTextBack(); break;
		case '-':setTextGreen(); cout << w; setTextBack(); break;
		case 'M':
		case 'М':
		
		case '^':setTextCyan(); cout << w; setTextBack(); break;
		case '%':setTextYellow(); cout << w; setTextBack(); break;

		default:
			break;
		}
		i++;
	}
		
	
}
void GETItem(int x, int y, int id)//x - место в инвентаре или снаряжении y - 1/снаряжение 2/инвентарь
{
	int xx = 0; int yy = 0;
	Item[id].id = id;
	string getContent;
	int f=0;
	if (player.Class == "Воин")
		f = 1;
	if (player.Class == "Маг")
		f = 2;
	if (player.Class == "Лучник")
		f = 3;
	string fileName = "Items\\" + to_string(id) + to_string(f) + ".txt";
	ifstream openfile(fileName.c_str());
	getline(openfile, getContent);
	Item[id].name = getContent;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	if (openfile.is_open())
	{
		for (int i = 0; i < 6; i++)
		getline(openfile, getContent);
			
		int p;
		openfile >> p;
		Item[id].type = p;
		openfile >> p;
		Item[id].damage = p;
		openfile >> p;
		if (f == 1)
			Item[id].strength = p;
		if(f ==2 )
			Item[id].agility = p;
		if (f==3)
			Item[id].iq = p;
		openfile >> p;
		Item[id].cost = p;
		openfile >> p;
		Item[id].crit = p;
		openfile >> p;
		Item[id].color = p;
		
		switch (y)
		{
		case 1:
			player.equipment[Item[id].type] = Item[id];
		case 2:
		case 3:
		default:
			break;
		}

			

	
	}
	setTextBack();

}

void printItem(int x, int y, int id)
{
	int xx = 0; int yy = 0;
	
	string getContent;
	string fileName = "Items\\" + to_string(id) + ".txt";
		ifstream openfile(fileName.c_str());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	if (openfile.is_open())
	{
		while (yy<6)
		{
			gotoxy(x + xx, y + yy);
			getline(openfile, getContent);
			setColor(Item[id].color);
			
			cout << getContent << endl;
			yy++;
		}
	}
	setTextBack();

}

void printOsn()
{
	for (int i = 0; i < 34; i++)
	{
		gotoxy(149, 17 + i);
			cout << "#";
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 16; i++)
		{
			gotoxy(133 + i, 23+j*7);
			cout << "#";
		}
	}
	for (int i = 0; i < 6; i++)
	{
		gotoxy(191, 17 + i);
		cout << "#";
	}
	for (int i = 0; i < 16; i++)
	{
		gotoxy(191 + i, 23 );
		cout << "#";
	}
	gotoxy(132, 16);
	setColor(3);
	if (player.Class == "Лучник")
		cout << "_Шапка_";
	if (player.Class == "Воин")
	cout << "_Шлем_";
	if (player.Class == "Маг")
		cout << "_Шляпа_";
	setTextBack();
	gotoxy(132, 17);
	string getContent;
	int f = 0;
	if (player.Class == "Воин")
		f = 1;
	if (player.Class == "Маг")
		f = 2;
	if (player.Class == "Лучник")
		f = 3;
	string fileName = "Items\\" + to_string(player.equipment[1].id) + to_string(f) + ".txt";
	ifstream openfile1(fileName.c_str());
	getline(openfile1, getContent);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	if (openfile1.is_open())
	{
		for (int i = 0; i < 6; i++)
		{
			getline(openfile1, getContent);
			gotoxy(134, 17 + i);
			setColor(player.equipment[1].color);
			cout << getContent;
			setTextBack();
		}
	}
	gotoxy(132, 23);
	setColor(3);
	if (player.Class == "Воин")
		cout << "_Нагрудник_";
	if (player.Class == "Маг")
		cout << "_Плащ_";
	if (player.Class == "Лучник")
		cout << "_Накидка_";
	
	setTextBack();
	 fileName = "Items\\" + to_string(player.equipment[2].id) + to_string(f) + ".txt";
	ifstream openfile2(fileName.c_str());
	getline(openfile2, getContent);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	if (openfile2.is_open())
	{
		for (int i = 0; i < 6; i++)
		{
			getline(openfile2, getContent);
			gotoxy(134, 24 + i);
			setColor(player.equipment[2].color);
			cout << getContent;
			setTextBack();
		}
	}
	gotoxy(132, 30);
	setColor(3);
	cout << "_Перчатки_";


	setTextBack();
	 fileName = "Items\\" + to_string(player.equipment[3].id) + to_string(f) + ".txt";
	ifstream openfile3(fileName.c_str());
	getline(openfile3, getContent);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	if (openfile3.is_open())
	{
		for (int i = 0; i < 6; i++)
		{
			getline(openfile3, getContent);
			gotoxy(134, 31 + i);
			setColor(player.equipment[3].color);
			cout << getContent;
			setTextBack();
		}
	}
	gotoxy(132, 37);
	setColor(3);
	if (player.Class == "Воин")
		cout << "_Поножи_";
	if (player.Class == "Маг")
		cout << "_Штаны_";
	if (player.Class == "Лучник")
		cout << "_Штаны_";

	setTextBack();
	 fileName = "Items\\" + to_string(player.equipment[4].id) + to_string(f) + ".txt";
	ifstream openfile4(fileName.c_str());
	getline(openfile4, getContent);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	if (openfile4.is_open())
	{
		for (int i = 0; i < 6; i++)
		{
			getline(openfile4, getContent);
			gotoxy(132, 38 + i);
			setColor(player.equipment[4].color);
			cout << getContent;
			setTextBack();
		}
	}
	gotoxy(132, 44);
	setColor(3);
	cout << "_Сапоги_";

	setTextBack();
	 fileName = "Items\\" + to_string(player.equipment[5].id) + to_string(f) + ".txt";
	ifstream openfile5(fileName.c_str());
	getline(openfile5, getContent);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	if (openfile5.is_open())
	{
		for (int i = 0; i < 6; i++)
		{
			getline(openfile5, getContent);
			gotoxy(134, 45 + i);
			setColor(player.equipment[5].color);
			cout << getContent;
			setTextBack();
		}
	}
	gotoxy(191, 16);
	setColor(3);
	if (player.Class == "Воин")
	cout << "_Меч_";
	if (player.Class == "Маг")
		cout << "_Посох_";
	if (player.Class == "Лучник")
		cout << "_Лук_";

	setTextBack();
	 fileName = "Items\\" + to_string(player.equipment[0].id) + to_string(f) + ".txt";
	ifstream openfile(fileName.c_str());
	getline(openfile, getContent);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	if (openfile.is_open())
	{
		for (int i = 0; i < 6; i++)
		{
			getline(openfile, getContent);
			gotoxy(193, 17 + i);
			setColor(player.equipment[0].color);
			cout << getContent;
			setTextBack();
		}
	}
}
void printBody() {

}
void printLegs() {

}
void setItems()
{
	
	Item[1].type = 0;
	Item[1].color = 0;
	Item[1].damage = 10*(1./player.difficulty);
	if (player.Class == "Воин")
	{
		Item[1].name = "Деревянный меч";
		Item[1].strength = 10;
		Item[1].cost = 10;
		Item[1].crit = 10 * (1. / player.difficulty);
	}
	if (player.Class == "Маг")
	{
		Item[1].name = "Деревянная палка";
		Item[1].iq = 10;
		Item[1].cost = 10;
		Item[1].crit = 10 * (1. / player.difficulty);
	}
	if (player.Class == "Лучник")
	{
		Item[1].name = "Деревянный лук";
		Item[1].agility = 10;
		Item[1].cost = 10;
		Item[1].crit = 10 * (1. / player.difficulty);
	}
}
void printInv()
{
	gotoxy(132, 16);
	cout << "############################################################################";
	for (int i = 0; i < 34; i++)
	{
		gotoxy(132, 17 + i);
		cout << "#                                                                          #";
	}
	gotoxy(132, 51);
	cout << "############################################################################";
	printOsn();
	printBody();
	printLegs();
}
void printAboutChar()
{
	gotoxy(132, 0);
	cout <<"############################################################################";
	gotoxy(132, 1);
	cout <<"|  О персонаже:                                                            |";
	gotoxy(132, 2);
	cout << "############################################################################";
	
	gotoxy(132, 3);
	if (player.name.length() < 20)
	{
		cout << "|  Имя:      #                     ";

		cout << player.name;
	}
	else {
		if (player.name.length() < 61)
		{
			cout << "|  Имя:      # ";

			cout << player.name;
		}
		else  cout << "|  Имя:      # НЕ ВЛЕЗАЕТ В ПОЛЕ! ";

	}
	gotoxy(207, 3);
	cout << "|";
	gotoxy(132, 4);
	cout << "############################################################################";
	gotoxy(132, 5);
	cout << "|  Класс:    #                     ";
	cout << player.Class;
	gotoxy(207, 5);
	cout << "|";
	gotoxy(132, 6);
	cout << "############################################################################";
	gotoxy(132, 7);
	cout << "|  Раса:     #                     ";
	cout << player.race;
	gotoxy(207, 7);
	cout << "|";
	gotoxy(132, 8);
	cout << "############################################################################";

	gotoxy(132, 9);
	cout << "|  Уровень:  #                          ";
	cout << player.lvl+1;
	
	gotoxy(207, 9);
	cout << "|";
	gotoxy(132, 10);
	cout << "############################################################################";
	gotoxy(132,11);
	cout << "|  Опыт:     #                        ";
	cout << player.exp;
	cout << " \\ ";
	cout << level_exp[player.lvl];
	gotoxy(207, 11);
	cout << "|";
	gotoxy(132, 12);
	cout << "############################################################################";

	gotoxy(132, 13);
	cout << "|  Деньги:   # Золотых монет: ";
	cout << player.money/1000;
	cout << "   Серебряных монет: ";
	cout << player.money /100%10;
	cout << "  Бронзовых монет: ";
	cout << player.money%100 ;
	
	
	gotoxy(207, 13);
	cout << "|";
	gotoxy(132, 14);
	cout << "############################################################################";

	
	
	printInv();

	gotoxy(0, 32);
	cout << "|                                                                                                   |";
	gotoxy(0, 33);
	cout << "#####################################################################################################";
	gotoxy(0, 37);
	setTextCyan();
	cout << "УПРАВЛЕНИЕ_________________________________________________________________________________________________________________________";
	gotoxy(0, 38);
	cout << "| W - Идти вверх/вперёд/на север |    A - Идти влево / на запад   |   S - Идти вниз/назад/на юг  |   D - Идти вправо / на восток  |";
	setTextBack();
	gotoxy(0, 40);
	cout << "ОБОЗНАЧЕНИЯ НА КАРТЕ____________________________________________________________________";
	gotoxy(0, 41);
	cout << "| e - Вход/Выход в/из здания |    g - Стражник   |   T -  Торговец  |  t  - Горожанин  |";
	gotoxy(0, 42);
	cout << "________________________________________________________________________________________";
	gotoxy(0, 43);
	cout << "|";
	setTextRed();
	 cout<<"Красным"; setTextBack(); cout << " обозначаются враги и вы например : |"; setTextRed(); cout << " X"; setTextBack(); cout << "  -  Вы | "; setTextRed(); cout << " В"; setTextBack(); cout << "  -  Волк | "; setTextRed(); cout << " Р"; setTextBack(); cout << " -  Разбойник | ";
	 gotoxy(0, 44);
	 cout << "________________________________________________________________________________________";
	 gotoxy(0, 45);
	 cout << "|";
	 setTextGreen();
	 cout << "Зелёным"; setTextBack(); cout << " обозначаются дружественные : |"; setTextGreen(); cout << " g"; setTextBack(); cout << "  -  Стражник | "; setTextGreen(); cout << " T"; setTextBack(); cout << "  - Торговец | "; setTextGreen(); cout << " К"; setTextBack(); cout << " - Капитан | ";
	gotoxy(5 , 52);
	cout << "_________________________________________________________________________________________________________________________________________________________________________________________________________";
	gotoxy(5, 53);

	cout << "|        I - Открыть инвентарь      |       J - Открыть журнал заданий       |        M - открыть карту республики        |          H - Открыть окно помощи      |          ESC - Открыть меню         |";
	
	

}
void gotomainPlayScreenAfterDialog()
{
	system("cls");
	loadLoc(player.loc, player.level);
	
	
	printAboutChar();
	gotoxy(player.x, player.y);
	setTextRed();
	cout << 'X';

	setTextBack();

	update();

}
void gotomainPlayScreen(int loc)
{
	system("cls");
	loadLoc(loc,player.level);
	player.loc = loc;
	switch (player.level)
	{
	case 1:startPoint(5, 10); break;
	case 2:
	case 3:
	case 4:startPoint(7, 4);
	default:
		break;
	}
	printAboutChar();
	gotoxy(player.x, player.y);
	setTextRed();
	cout << 'X';
	setTextBack();

	update();

}
void enterTown()
{
	switch (player.level)
	{
	case 1: gotomainPlayScreen(1);
	case 2:gotomainPlayScreen(4);
	case 3:gotomainPlayScreen(6);
	case 4:gotomainPlayScreen(4);
	
	default:
		break;
	}

}
void chooseTown()
{
	
	char s;
	
	switch (player.level)
			{
			case 1:
				gotoxy(broghird.x, broghird.y);
				cout << " ";
				player.level = 2;
				gotoxy(orzodh.x, orzodh.y);
				setTextRed();
				cout << "X";
				player.x = orzodh.x;
				player.y = orzodh.y;
				setTextBack();
				
				while (1)
				{
					s = getch();
					switch (s)
					{
					case -26:
					case'w': chooseTown(); break;
					case -29:
					case 'e':if (player.dopusk >= 2) enterTown();
							else
					{
						gotoxy(150, 30);
						cout << "У вас нет пропуска для входа в город";
						Sleep(1000);
						gotoxy(150, 30);
						cout << "                                    ";
					}

					default:
						break;
					}
				}break;
			case 2:
				gotoxy(orzodh.x, orzodh.y);
				cout << " ";
				player.level = 3;
				gotoxy(clounto_ridge.x, clounto_ridge.y);
				setTextRed();
				cout << "X";
				player.x = clounto_ridge.x;
				player.y = clounto_ridge.y;
				setTextBack();
				
				while (1)
				{
					s = getch();
					switch (s)
					{
					case -26:
					case'w': chooseTown(); break;
					case -29:
					case 'e':if (player.dopusk >= 3) enterTown();
							else
					{
						gotoxy(150, 30);
						cout << "У вас нет пропуска для входа в город";
						Sleep(1000);
						gotoxy(150, 30);
						cout << "                                    ";
					}

					default:
						break;
					}
				}break;
			case 3:
				gotoxy(clounto_ridge.x, clounto_ridge.y);
				cout << " ";
				player.level = 4;
				gotoxy(ghedg.x, ghedg.y);
				setTextRed();
				cout << "X";
				player.x = ghedg.x;
				player.y = ghedg.y;
				setTextBack();
				
				while (1)
				{
					s = getch();
					switch (s)
					{
					case -26:
					case'w': chooseTown(); break;
					case -29:
					case 'e':if (player.dopusk >= 4) enterTown();
							else
					{
						gotoxy(150, 30);
						cout << "У вас нет пропуска для входа в город";
						Sleep(1000);
						gotoxy(150, 30);
						cout << "                                    ";
					}

					default:
						break;
					}
				}break;
			case 4:
				gotoxy(ghedg.x, ghedg.y);
				cout << " ";
				player.level = 1;
				gotoxy(broghird.x, broghird.y);
				setTextRed();
				cout << "X";
				player.x = broghird.x;
				player.y = broghird.y;
				setTextBack();
				
				while (1)
				{
					s = getch();
					switch (s)
					{
					case -26:
					case'w': chooseTown(); break;
					case -29:			
					case 'e':if (player.dopusk >= 1) enterTown();
							else
					{
						gotoxy(150, 30);
						cout << "У вас нет пропуска для входа в город";
						Sleep(1000);
						gotoxy(150, 30);
						cout << "                                    ";
					}

					default:
						break;
					}
				}
				break;
			default:
				break;
			}
			
}	
void changelevel()
{

	system("cls");
	loadLevelBase("map.txt");
	paintRiversAndGrass();
	gotoxy(0, 0);
	set_towns_coordinate();
	gotoxy(150, 50);
	char S;
	cout << "        Нажмите E чтобы войти в город    ";
	gotoxy(150, 52);
	cout << "Используйте W для перемещения между локациями";
	
	if (player.level == 1)
	{
		gotoxy(broghird.x, broghird.y);
		setTextRed();
		cout << "X";
		player.x = broghird.x;
		player.y = broghird.y;
		setTextBack();

		while (1)
		{
			S = getch();
			switch (S)
			{
			case -26:
			case'w': chooseTown(); break;
			case -29:
			case 'e': enterTown();
			
			default:
				break;
			}
		}
	}
	if (player.level == 2)
	{
		gotoxy(orzodh.x, orzodh.y);
		setTextRed();
		cout << "X";
		player.x = broghird.x;
		player.y = broghird.y;
		setTextBack();
		
		while (1)
		{
			S = getch();
			switch (S)
			{
			case -26:
			case'w': chooseTown(); break;
			case -29:
			case 'e':if (player.dopusk >= 2) enterTown();
					else
			{
				gotoxy(150, 30);
				cout << "У вас нет пропуска для входа в город";
				Sleep(1000);
				gotoxy(150, 30);
				cout << "                                    ";
			}
			default:
				break;
			}
		}

	}
	if (player.level == 3)
	{
		gotoxy(clounto_ridge.x, clounto_ridge.y);
		setTextRed();
		cout << "X";
		player.x = broghird.x;
		player.y = broghird.y;
		setTextBack();
		
		while (1)
		{
			S = getch();
			switch (S)
			{
			case -26:
			case'w': chooseTown(); break;
			case -29:
			case 'e':if (player.dopusk >=3) enterTown();
					else
			{
				gotoxy(150, 30);
				cout << "У вас нет пропуска для входа в город";
				Sleep(1000);
				gotoxy(150, 30);
				cout << "                                    ";
			}
			default:
				break;
			}
		}
	}
	if (player.level == 4)
	{
		gotoxy(ghedg.x, ghedg.y);
		setTextRed();
		cout << "X";
		player.x = broghird.x;
		player.y = broghird.y;
		setTextBack();
		
		while (1)
		{
			S = getch();
			switch (S)
			{
			case -26:
			case'w': chooseTown(); break;
			case -29:
			case 'e':if (player.dopusk >= 4) enterTown();
					else
			{
				gotoxy(150, 30);
				cout << "У вас нет пропуска для входа в город";
				Sleep(1000);
				gotoxy(150, 30);
				cout << "                                    ";
			}
			default:
				break;
			}
		}
	}
	
	
}
void pSWT(string str)//printStringWithTime
{
	for (int i = 0; i < str.length(); i++)
	{
		cout << str[i];
		Sleep(50);
	}
}

void openWorldMap()
{
	system("cls");
	loadLevelBase("map.txt");
	paintRiversAndGrass();
	gotoxy(0, 0);
	set_towns_coordinate();
	if (player.level == 1)
	{
		gotoxy(broghird.x, broghird.y);
		cout << "X";
	}
	if (player.level == 2)
	{
		gotoxy(orzodh.x, orzodh.y);
		cout << "X";

	}
	if (player.level == 3)
	{
		gotoxy(clounto_ridge.x, clounto_ridge.y);
		cout << "X";

	}
	if (player.level == 4)
	{
		gotoxy(ghedg.x, ghedg.y);
		cout << "X";

	}

	int x;
	cin >> x;
}
void dialog(int x)
{
	if (x == -1)
	{
		SystemMessage("Этот персонаж не хочет взаимодействовать с вами...");
	}
	else
	{
		/*system("cls");
		string str;
		string getContent;
		switch (x)
		{
		case 0:
			str = "Guardian";

		default:
			break;
		}
		string fileName = "CharactersForDialogs\\" + str + ".txt";
		int yy = 0;
		ifstream openfile(fileName.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		if (openfile.is_open())
		{
			while (!openfile.eof())
			{
				gotoxy( 150, 30 + yy);
				getline(openfile, getContent);


				cout << getContent << endl;
				yy++;
			}
		}
		for (int i = 0; i < 54; i++)
		{
			gotoxy(90, i);
			cout << "|";
		}
		string fileName1 = "Dialogs\\" + to_string(x) + ".txt";
		ifstream openfile(fileName.c_str());
		yy = 0;
		if (openfile.is_open())
		{
			while (!openfile.eof())
			{
				gotoxy(150, 30 + yy);
				getline(openfile, getContent);


				cout << getContent << endl;

				yy++;
			}
		}
		char f; f = getch();*/




		//	gotomainPlayScreenAfterDialog();
		//}

		if (player.Class == "Воин")
		{
			player.inventory[player.inventory_last] = Item[0];
			if (player.equipment[0].id == NULL)
				player.equipment[0] = Item[1];

		}
		if (player.Class == "Воин")
		{
			player.inventory[player.inventory_last] = Item[0];
			if (player.equipment[0].id == NULL)
				player.equipment[0] = Item[1];

		}
		if (player.Class == "Воин")
		{
			player.inventory[player.inventory_last] = Item[0];
			if (player.equipment[0].id == NULL)
				GETItem(0, 1, 1);

		}
		gotomainPlayScreenAfterDialog();
	}
}
char conditionsForObjects(TCHAR wAttrib, char key)
{
	int xlast = player.x, ylast = player.y;
	if (wAttrib == 'b')
	{
		if (player.level == 1 && player.loc == 1)
		{
			gotoxy(4, 17);
			cout << "       ";
			gotoxy(4, 18);
			cout << "       ";
			gotoxy(4, 19);
			cout << "       ";
		}
		if (player.level == 1 && player.loc == 0 )
		{
			if (button0_1.pressed == false)
			{
				gotoxy(82, 6);
				cout << " ";

				button0_1.pressed = true;
			}
			else 
			{
				gotoxy(82, 6);

				cout << "#";
				gotoxy(82, 7);
				cout << "@";
				gotoxy(82, 8);
				cout << "@";
				button0_1.pressed == false;
			}
		}

	}
	else
		if (wAttrib == '?')
		{
			switch (key)
			{
			case 'w': gotoxy(player.x, player.y--); break;
			case 's': gotoxy(player.x, player.y++); break;
			case 'a': gotoxy(player.x--, player.y); break;
			case 'd': gotoxy(player.x++, player.y); break;
			default:
				break;
			}
			gotoxy(player.x, player.y);
			cout << ('X');
			gotoxy(xlast, ylast);
			cout << " ";
			gotoxy(1, 32);
			cout << "Вы подняли яблоко!";
			Sleep(2000);
			gotoxy(1, 32);
			cout << "                  ";

			return wAttrib;
		}
		else
			if (wAttrib == 'F')
			{
				changelevel();
			}
			else
				if (wAttrib == 'S')
				{

					switch (key)
					{
					case 'w': gotoxy(player.x, player.y--); break;
					case 's': gotoxy(player.x, player.y++); break;
					case 'a': gotoxy(player.x--, player.y); break;
					case 'd': gotoxy(player.x++, player.y); break;
					default:
						break;
					}
					gotoxy(player.x, player.y);
					cout << ('X');
					gotoxy(xlast, ylast);
					cout << " ";
					gotoxy(1, 32);
					cout << "Вы подняли Шлем!";
					if(player.equipment[0].id==NULL)
					player.equipment[0] = Item[0];
					player.inventory[player.inventory_last] = Item[0];
					printItem(133, 17,0);
					Sleep(2000);
					gotoxy(1, 32);
					cout << "                  ";
					for (int i = 0; i < 100; i++)
						if (Objects[i].Char == 'S' && Objects[i].level == player.level && Objects[i].loc == player.loc)
							Objects[i].IsAlive = false;

					return wAttrib;
				}
				else
					if (wAttrib == 'g')
					{
						switch (player.loc)
						{
						case 0:
							switch (player.level)
							{
							case 1:
								switch (key)
								{
								case 'w': gotoxy(player.x, player.y++); break;
								case 's': gotoxy(player.x, player.y--); break;
								case 'a': gotoxy(player.x++, player.y); break;
								case 'd': gotoxy(player.x--, player.y); break;
								default:
									break;
								}

								dialog(-1);


							case 2:
							case 3:
							case 4:
							case 5:
							case 6:
							default:

								break;
							}
						}
					}
					else
						if (wAttrib == 'K')
						{
							switch (player.loc)
							{
							case 0:
								switch (player.level)
								{
								case 1:
									switch (key)
									{
									case 'w': gotoxy(player.x, player.y++); break;
									case 's': gotoxy(player.x, player.y--); break;
									case 'a': gotoxy(player.x++, player.y); break;
									case 'd': gotoxy(player.x--, player.y); break;
									default:
										break;
									}
									
									dialog(0);


								case 2:
								case 3:
								case 4:
								case 5:
								case 6:
								default:

									break;
								}
							case 1:break;
							case 2:break;
							case 3:break;
							case 4:break;
							case 5:break;
							case 6:break;
							case 7:break;
							case 8:break;
							case 9:break;
							default:
								break;
							}

						}
						else
							if (wAttrib == '#')
							{
								changeloc(key);
							}
							else
								if (wAttrib == '@')
								{
									switch (key)
									{
									case 'w': gotoxy(player.x, player.y++); break;
									case 's': gotoxy(player.x, player.y--); break;
									case 'a': gotoxy(player.x++, player.y); break;
									case 'd': gotoxy(player.x--, player.y); break;
									default:
										break;
									}
								}
								else 
									if (wAttrib == 'e')
									{
										
										if (player.level == 1 && player.loc == 0)
										{
											system("cls");
											loadLoc(1, player.level);
											player.loc = 1;
											startPoint(23,23);
											printAboutChar();
											gotoxy(player.x, player.y);
											setTextRed();
											cout << 'X';
											setTextBack();

											update();
										}
										if (player.level == 1 && player.loc == 1)
										{
											system("cls");
											loadLoc(0, player.level);
											player.loc = 0;
											startPoint(115, 14);
											printAboutChar();
											gotoxy(player.x, player.y);
											setTextRed();
											cout << 'X';
											setTextBack();

											update();
										}

										return wAttrib;
									}
									return 0;
		


	



}
char nearSymb(char x)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	TCHAR wAttrib = 0;
	COORD coord;
	BOOL bOK;
	DWORD dwReaden = 0;
	switch (x)
	{
	case 'w': 
		
		coord.X = player.x;	
		coord.Y = player.y-1;
		
		ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), &wAttrib, 1, coord, &dwReaden);
		return conditionsForObjects(wAttrib, 'w');

		break;
	case 's':
		coord.X = player.x;
		coord.Y = player.y + 1;

		ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), &wAttrib, 1, coord, &dwReaden);
		return conditionsForObjects(wAttrib, 's');
		break ;
	case 'a':
		coord.X = player.x - 1;
		coord.Y = player.y;

		ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), &wAttrib, 1, coord, &dwReaden);
		return conditionsForObjects(wAttrib, 'a');
		break ;
	case 'd':
		coord.X = player.x+1;
		coord.Y = player.y;

		ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), &wAttrib, 1, coord, &dwReaden);
		return conditionsForObjects(wAttrib, 'd');
		break ;
	default:
		break;
	}
}
void getCharAndMove()
{
	char c;
	
		
		c = getch();
		
		switch (c)
		{
		case -26:
		case 'w':
			if (!nearSymb('w'))
			{
				if (player.y > 1)
					player.y--;
			}
			break;
			
		case -21:
		case 's':	if (!nearSymb('s'))
		{
			if (player.y < 30) player.y++;
		}break;
		case -94:
		case 'd':
			if (!nearSymb('d'))
			{
				if (player.x < 127) player.x++;
			}break;
		case -28:
		case 'a':
			if (!nearSymb('a'))
			{
				if (player.x > 1) player.x--;
			}break;
		default:
		
			break;
		}
	
}
void update()
{
	while (1)
	{
		

		int xlast = player.x, ylast = player.y;
		
		
		getCharAndMove();
		if (player.x == xlast && player.y == ylast)
		{
			gotoxy(player.x, player.y);
			setTextRed();
			cout << "X";
			setTextBack();
		}
		else {
			gotoxy(xlast, ylast);
			cout << " ";
			gotoxy(player.x, player.y);
			setTextRed();
			cout << "X";
			setTextBack();
		}
		
	}
}

void setStartPrisoners()
{
	
	Objects[count_obj].Char = 'K';
	Objects[count_obj].color = 3;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 12;
	Objects[count_obj].y = 14;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'Р';
	Objects[count_obj].color = 1;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 15;
	Objects[count_obj].y = 4;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'Р';
	Objects[count_obj].color = 1;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 25;
	Objects[count_obj].y = 5;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'g';
	Objects[count_obj].color = 3;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 19;
	Objects[count_obj].y =9;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'g';
	Objects[count_obj].color = 3;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 16;
	Objects[count_obj].y = 9;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'g';
	Objects[count_obj].color = 3;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 19;
	Objects[count_obj].y = 22;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'g';
	Objects[count_obj].color = 3;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 16;
	Objects[count_obj].y = 22;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'g';
	Objects[count_obj].color = 3;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 52;
	Objects[count_obj].y = 9;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'g';
	Objects[count_obj].color = 3;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 55;
	Objects[count_obj].y = 9;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'Р';
	Objects[count_obj].color = 1;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 39;
	Objects[count_obj].y = 3;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'Р';
	Objects[count_obj].color = 1;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 57;
	Objects[count_obj].y = 5;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'Р';
	Objects[count_obj].color = 1;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 60	;
	Objects[count_obj].y = 3;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'g';
	Objects[count_obj].color = 3;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 81;
	Objects[count_obj].y = 9;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'g';
	Objects[count_obj].color = 3;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 83;
	Objects[count_obj].y = 9;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'g';
	Objects[count_obj].color = 3;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 16;
	Objects[count_obj].y = 15;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'g';
	Objects[count_obj].color = 3;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 16;
	Objects[count_obj].y = 13;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'g';
	Objects[count_obj].color = 3;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 115;
	Objects[count_obj].y = 9;
	Objects[count_obj].IsAlive = true;
	count_obj++;

}
void intro()
{
	setTextYellow();
	gotoxy(5, 34);
	cout << "^";
	gotoxy(4, 35);
	cout << "/";
	gotoxy(6, 35);
	cout << "\\";
	gotoxy(5, 35);
	cout << "|";
	gotoxy(5, 36);
	cout << "|";
	gotoxy(5, 37);
	cout << "|";
	gotoxy(3, 38);
	setTextRed();
	cout << "ОКНО СООБЩЕНИЙ";
	setTextBack();
	Sleep(2000);
	gotoxy(5, 34);
	cout << " ";
	gotoxy(4, 35);
	cout << " ";
	gotoxy(6, 35);
	cout << " ";
	gotoxy(5, 35);
	cout << " ";
	gotoxy(5, 36);
	cout << " ";
	gotoxy(5, 37);
	cout << " ";
	gotoxy(3, 38);
	setTextRed();
	cout << "              ";
	setTextBack();

	gotoxy(1, 32);
	Sleep(500);
	cout << "Вы смотрите, как приводят нового заключенного...";
	Sleep(1000);
	gotoxy(120, 14);
	setTextGreen();
	cout << "g";
	gotoxy(119, 14);
	setTextRed();
	cout << "P";
	gotoxy(119, 14);
	Sleep(400);
	gotoxy(120, 14);
	cout << " ";
	gotoxy(119, 14);
	setTextGreen();
	cout << "g";
	gotoxy(119, 13);
	setTextRed();
	cout << "P";
	Sleep(400);
	gotoxy(119, 14);
	cout << " ";
	gotoxy(119, 13);
	setTextGreen();
	cout << "g";
	gotoxy(119, 12);
	setTextRed();
	cout << "P";
	Sleep(400);
	gotoxy(119, 13);
	cout << " ";
	gotoxy(119, 12);
	setTextGreen();
	cout << "g";
	gotoxy(119, 11);
	setTextRed();
	cout << "P";
	Sleep(400);
	gotoxy(119, 12);
	cout << " ";
	gotoxy(119, 11);
	setTextGreen();
	cout << "g";
	gotoxy(119, 10);
	setTextRed();
	cout << "P";
	Sleep(400);
	gotoxy(119, 11);
	cout << " ";
	gotoxy(119, 10);
	setTextGreen();
	cout << "g";
	gotoxy(118, 10);
	setTextRed();
	cout << "P";

	Sleep(300);
	gotoxy(119, 10);
	cout << " ";
	gotoxy(118, 10);
	setTextGreen();
	cout << "g";
	gotoxy(117, 10);
	setTextRed();
	cout << "P";
	Sleep(300);
	gotoxy(118, 10);
	cout << " ";
	gotoxy(117, 10);
	setTextGreen();
	cout << "g";
	gotoxy(116, 10);
	setTextRed();
	cout << "P";
	Sleep(300);
	gotoxy(117, 10);
	cout << " ";
	gotoxy(116, 10);
	setTextGreen();
	cout << "g";
	gotoxy(115, 10);
	setTextRed();
	cout << "P";
	Sleep(300);
	gotoxy(116, 10);
	cout << " ";
	gotoxy(115, 10);
	setTextGreen();
	cout << "g";
	gotoxy(114, 10);
	setTextRed();
	cout << "P";
	Sleep(300);
	gotoxy(115, 10);
	cout << " ";
	gotoxy(114, 10);
	setTextGreen();
	cout << "g";
	gotoxy(113, 10);
	setTextRed();
	cout << "P";
	Sleep(222);
	gotoxy(114, 10);
	cout << " ";
	gotoxy(113, 10);
	setTextGreen();
	cout << "g";
	gotoxy(113, 9);
	setTextRed();
	cout << "P";
	Sleep(222);
	gotoxy(113, 10);
	cout << " ";
	gotoxy(113, 9);
	setTextGreen();
	cout << "g";
	gotoxy(113, 8);
	setTextRed();
	cout << "P";
	Sleep(222);
	gotoxy(113, 9);
	cout << " ";
	gotoxy(113, 8);
	setTextGreen();
	cout << "g";
	gotoxy(113, 7);
	setTextRed();
	cout << "P";
	Sleep(200);
	gotoxy(113, 8);
	cout << " ";
	gotoxy(113, 7);
	setTextGreen();
	cout << "g";
	gotoxy(113, 6);
	setTextRed();
	cout << "P";
	Sleep(200);
	gotoxy(113, 7);
	cout << " ";
	gotoxy(113, 6);
	setTextGreen();
	cout << "g";
	gotoxy(113, 5);
	setTextRed();
	cout << "P";
	Sleep(200);
	gotoxy(113, 6);
	cout << " ";
	gotoxy(113, 5);
	setTextGreen();
	cout << "g";
	gotoxy(113, 4);
	setTextRed();
	cout << "P";
	Sleep(200);
	gotoxy(113, 5);
	cout << " ";
	gotoxy(113, 6);
	setTextGreen();
	cout << "g";
	Sleep(200);
	gotoxy(113, 6);
	setTextBack();
	cout << "#";
	gotoxy(113, 7);
	setTextGreen();
	cout << "g";
	Sleep(200);
	gotoxy(113, 7);
	setTextBack();
	cout << "@";
	gotoxy(113, 8);
	setTextGreen();
	cout << "g";
	Sleep(200);
	gotoxy(113, 8);
	cout << " ";
	gotoxy(113, 9);
	setTextGreen();
	cout << "g";
	Sleep(200);
	gotoxy(113, 9);
	cout << " ";
	gotoxy(112, 9);
	setTextGreen();
	cout << "g";
	Objects[count_obj].Char = 'g';
	Objects[count_obj].color = 3;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 112;
	Objects[count_obj].y = 9;
	Objects[count_obj].IsAlive = true;
	count_obj++;
	Objects[count_obj].Char = 'Р';
	Objects[count_obj].color = 1;
	Objects[count_obj].level = 1;
	Objects[count_obj].loc = 0;
	Objects[count_obj].x = 113;
	Objects[count_obj].y = 4;
	Objects[count_obj].IsAlive = true;
	count_obj++;

	setTextBack();


	gotoxy(1, 32);
	cout << "                                                ";
	gotoxy(1, 32);
	setTextCyan();
	cout << "Один из стражников, увидев, что вы очнулись, кликнул вас подойти к начальнику тюрьмы";
	setTextBack();
	Sleep(3000);
	gotoxy(1, 32);
	cout << "                                                                                     ";
}
void Start()
{
	system("cls");
	gotoxy(100, 25);
	setTextCyan();
	cout << "НОВАЯ ИГРА";
	gotoxy(100, 30);
	cout << "Загрузка...";
	for (int i = 0; i < 5; i++)
	{
		gotoxy(103, 32);
		cout << "# # #";
		gotoxy(103, 33);
		cout << "     ";
		gotoxy(103, 34);
		cout << "#   #";

		gotoxy(103, 35);
		cout << "     ";
		gotoxy(103, 36);
		cout << "# # #";
		Sleep(200);
		gotoxy(103, 32);
		cout << " # # ";

		gotoxy(103, 33);
		cout << "#   #";
		gotoxy(103, 34);
		cout << " # # ";
		gotoxy(103, 35);
		cout << "#   #";

		gotoxy(103, 36);
		cout << " # # ";
		Sleep(200);
	}
		
	Sleep(500);
	system("cls");

	
	button0_1.pressed = false;
	
	gotoxy(0, 0);
	loadLevelBase("levels\\Start\\start.txt");
	player.loc == 0;
	startPoint(87,5);
	gotoxy(87, 5);
	setTextRed();
	cout << "X";
	setTextBack();
	setStartPrisoners();
	setItems();
	gotoxy(0, 32);
	cout << "|                                                                                                   |";
	gotoxy(0, 33);
	cout << "#####################################################################################################";
	
	printCharS();
	//intro();
	printAboutChar();
	update();
	
	
}
int main()
{
	player.difficulty = 1;
	player.name = "Nice Gamer";
	player.lvl = 0;
	player.exp = 0;
	if (theme == 1)
	system("color 70");
	
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	::SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
	setlocale(LC_ALL, "Russian");
	COORD coord;
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &coord);
	setTextBack();
	player.money = 0;
	player.inventory_last = 0;
	player.Class = "Воин";
	player.race = "Человек";
	player.loc = 0;
	player.level = 1;
	player.dopusk = 1;
	Start();

	loadLoc(1, 1);
	startPoint(30,30);
	printAboutChar();
	gotoxy(player.x, player.y);
	setTextRed();
	cout << 'X';
	setTextBack();
	update();



	int x;
	cin >> x;
	system("pause");
}