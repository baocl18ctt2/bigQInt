#pragma once
#include <iostream>
using namespace std;
#include "QInt.h"
#include "QFloat.h"
#include "Console.h"
#include "conio.h"
#define MAUNEN 176
#define MAUCHU 125
typedef char str[31];
str thaotac[2] = { "Start","End" };
enum TRANGTHAI { UP, DOWN, LEFT, RIGHT, ENTER};
TRANGTHAI key(int z);
int menu(str thaotac[3], int n);
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
		if (c == 77)
			return RIGHT;
		if (c == 75)
			return LEFT;
	}
	else if (z == 13)
		return ENTER;
}
void PrintMenu()
{
	int select;
	QInt a;
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
			a.Menu1();
			system("pause");
		}
		if (select == 2)
		{

		}
		if (select == 0)
			break;
	}
}
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
		cout << "\n\t---------------------------" << endl;
		
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