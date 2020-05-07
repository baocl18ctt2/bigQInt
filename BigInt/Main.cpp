#define _CRT_SECURE_NO_WARNINGS
#include "QInt.h"
#include <vector>
void main()
{
	QInt a, b, c, d;
	a.scanQInt("10", 10);
	a.printQInt(2);
	b.scanQInt("5", 10);
	b.printQInt(2);
	c = a * b;
	c.printQInt(2);
	cout << endl;
	system("pause");
}
