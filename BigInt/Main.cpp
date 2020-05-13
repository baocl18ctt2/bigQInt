#pragma once
#include <iostream>
using namespace std;
#include "QInt.h"
#include "QFloat.h"
#include "Console.h"
#include "conio.h"
#include <vector>
#include <sstream>

#define MAUNEN 176
#define MAUCHU 125
typedef char str[31];
str thaotac[2] = { "Start","End" };
enum TRANGTHAI { UP, DOWN, ENTER};
TRANGTHAI key(int z);
int menu(str thaotac[3], int n);
// Lay thao tac phim
TRANGTHAI key(int z)
{
	if (z == 224)
	{
		char c;
		c = _getch();
		if (c == 72)
			return UP;
		if (c == 80)
			return DOWN;
	}
	else if (z == 13)
		return ENTER;
}
void PrintMenu()
{
	int select;
	QInt a;
	Qfloat b;
	while (true)
	{
		system("cls");
		cout << "\n\t ****************************" << endl;
		cout << "\t  ----- CALCULATOR ----- " << endl;
		cout << "\t 1. QINT" << endl;
		cout << "\t 2. QFLOAT" << endl;
		cout << "\t 0. EXIT" << endl;
		cout << " ** please select: ";
		cin >> select;
		if (select == 1)
		{
			system("cls");
			a.ConvertAllToQint();
			system("pause");
		}
		if (select == 2)
		{
			system("cls");
			b.Menu2();
			system("pause");
		}
		if (select == 0)
			break;
	}
}
// Xu li phim
int menu(str thaotac[], int n)
{
	int tt = 0;
	int* mau = new int[n];
	for (int i = 0; i < n; i++)
		mau[i] = MAUCHU;
	mau[0] = MAUNEN;
	
	while (1)
	{
		clrscr();
		
		for (int i = 0; i < n; i++)
		{
			TextColor(mau[i]);
			cout << "\n\n\t\t" << i + 1 << ") " << thaotac[i] << endl;
		}
		int z = _getch();
		TRANGTHAI trangthai = key(z);
		switch (trangthai)
		{
		case UP:
		{
			if (tt == 0)
			{
				tt = n - 1;
			}
			else
				tt--;
			break;
		}
		case DOWN:
		{
			if (tt == n - 1)
				tt = 0;
			else
				tt++;
			break;
		}
		case ENTER:
		{
			if (tt != 1)
			{
				system("cls");
				PrintMenu();
			}
			else
				return tt;
		}
		}
		for (int i = 0; i < n; i++)
			mau[i] = MAUCHU;
		mau[tt] = MAUNEN;
	}
}

void main()
{
	system("color 70");
	menu(thaotac, 2);
	system("pause");
}

/*int main(int argc, char* argv[])
{
	fstream FileIn;
	FileIn.open(argv[1], ios::in);
	if (!FileIn)
		cout << "Loi";
	fstream FileOut;
	FileOut.open(argv[2], ios::out);
	if (strcmp(argv[3], "1") == 0)
	{
		while (!FileIn.eof())
		{
			string base;
			getline(FileIn, base);//doc 1 dong trong file
			vector <string> s;
			string delimiter = " ";
			size_t pos = 0;
			string token;
			while ((pos = base.find(delimiter)) < base.size())//doc tung chuoi trong line
			{
				token = base.substr(0, pos);
				s.push_back(token);
				base.erase(0, pos + delimiter.length());
			}
			s.push_back(base);


			if (s.size() == 3)				//truong hop chi co 3 chuoi
			{
				if (s[1] == "~")			//phep not
				{
					int k = 0;
					stringstream geek(s[0]);//chuyen string sang int
					geek >> k;
					QInt temp;
					temp.scanQInt(s[2], k);
					temp = ~temp;
					FileOut << temp.CreateBinStr() << endl;
				}
				else						//phep chuyen doi
				{
					int k1 = 0;
					stringstream geek1(s[0]);//chuyen string sang int
					geek1 >> k1;
					int k2 = 0;
					stringstream geek2(s[1]);//chuyen string sang int
					geek2 >> k2;
					QInt temp;
					temp.scanQInt(s[2], k1);
					if (k2 == 2)			//tu 10,16 sang 2
						FileOut << temp.CreateBinStr() << endl;
					else if (k2 == 10)		//tu 2 sang 10
						FileOut << temp.binToDec(temp) << endl;
					else if (k2 == 16)		//tu 2, 10 sang 16
						FileOut << temp.binToHex(temp) << endl;
				}
			}
			else if (s.size() == 4)			//cac truong hop tinh toan con lai
			{
				int k = 0;
				stringstream geek1(s[0]);	//chuyen string sang int
				geek1 >> k;

				QInt temp1, temp2, temp;
				temp1.scanQInt(s[1], k);	//chuoi 1
				temp2.scanQInt(s[3], k);	//chuoi 2

				if (s[2] == "<")		//< > == <= >=
				{
					if (temp1 < temp2)
						FileOut << "TRUE" << endl;
					else FileOut << "FALSE" << endl;
				}
				else if (s[2] == ">")
				{
					if (temp1 > temp2)
						FileOut << "TRUE" << endl;
					else FileOut << "FALSE" << endl;
				}
				else if (s[2] == "==")
				{
					if (temp1 == temp2)
						FileOut << "TRUE" << endl;
					else FileOut << "FALSE" << endl;
				}
				else if (s[2] == "<=")
				{
					if (temp1 <= temp2)
						FileOut << "TRUE" << endl;
					else FileOut << "FALSE" << endl;
				}
				else if (s[2] == ">=")
				{
					if (temp1 > temp2)
						FileOut << "TRUE" << endl;
					else FileOut << "FALSE" << endl;
				}
				else
				{
					if (s[2] == "+")			// + - * /
					{
						temp = temp1 + temp2;
					}
					else if (s[2] == "-")
					{
						temp = temp1 - temp2;
					}
					else if (s[2] == "*")
					{
						temp = temp1 * temp2;
					}
					else if (s[2] == "/")
					{
						temp = temp1 / temp2;
					}
					else if (s[2] == "&")
					{
						temp = temp1 & temp2;
					}
					else if (s[2] == "|")
					{
						temp = temp1 | temp2;
					}
					else if (s[2] == "^")
					{
						temp = temp1 ^ temp2;
					}
					else if (s[2] == "<<" || s[2] == ">>" || s[2] == "rol" || s[2] == "ror")
					{
						int timeMove = 0;
						stringstream geez(s[3]);	//chuyen string sang int
						geez >> timeMove;
						if (s[2] == "<<")
						{
							temp = temp1 << timeMove;
						}
						else if (s[2] == ">>")
						{
							temp = temp1 >> timeMove;
						}
						else if (s[2] == "rol")
						{
							temp = temp1.rol(timeMove);
						}
						else if (s[2] == "ror")
						{
							temp = temp1.ror(timeMove);
						}
					}
					if (k == 2)			
					{	//xuat dang 2
						string res = temp.CreateBinStr();
						while (res[0] == '0' && res.length() > 1)
							res.erase(0, 1);
						FileOut << res << endl;
					}
					else if (k == 10)		//xuat dang 10
						FileOut << temp.binToDec(temp) << endl;
					else if (k == 16)		//xuat dang 16
						FileOut << temp.binToHex(temp) << endl;
				}
			}
			s.clear();
		}
	}
	if (strcmp(argv[3], "2") == 0)
	{
		while (!FileIn.eof())
		{
			string base1;
			getline(FileIn, base1, ' ');
			string base2;
			getline(FileIn, base2, ' ');
			string str;
			getline(FileIn, str, '\n');
			if (base1 == "2")
			{
				Qfloat q;
				q.ScanQfloat(str, 2);
				FileOut << q.PrintQfloat(10) << endl;
			}
			if (base1 == "10")
			{
				Qfloat q;
				q.ScanQfloat(str, 10);
				FileOut << q.PrintQfloat(2) << endl;
			}
		}
	}
	FileOut.close();
	FileIn.close();
	return 0;
}
*/