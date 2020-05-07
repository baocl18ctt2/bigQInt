#define _CRT_SECURE_NO_WARNINGS
#include "QInt.h"
#include <vector>
void main()
{
	QInt a, b, c, d;
	a.scanQInt("100011111111000000000000000111111111001000000110000111", 2);
	a.printQInt(10);
	a.printQInt(16);
	b.scanQInt("-873129580771448538940058586182283", 10);
	b.printQInt(2);
	cout << endl;
	system("pause");
}
