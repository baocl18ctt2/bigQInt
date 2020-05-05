#define _CRT_SECURE_NO_WARNINGS
#include "QInt.h"
#include <vector>
void main()
{
	QInt a, b, c, d;
	a.scanQInt("100011111111000000000000000111111111001000000110000111", 2);
	string src = c.binToDec(a);
	cout << src << endl;
	string src1 = d.binToHex(a);
	cout << src1 << endl;
	b.scanQInt("13413465468788951346798413452523456465", 10);
	b.printQInt(2);
	cout << endl;
	system("pause");
	
}
