#pragma once
#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>
#include <vector>
#include <sstream>
using namespace std;

#define QINT_SIZE 4
#define HEX_CHARS "0123456789ABCDEF"
const char CHAR_55 = 55;
const char CHAR_48 = 48;

class QInt
{
private:
	int arr[QINT_SIZE];
public:
	QInt();
	~QInt();
	void setBit(int pos, bool value);
	bool getBit(int pos) const;
	bool IsZero() const;
	void scanQInt(string src, int base);
	QInt toInverse() const;
	string CreateBinStr() const;
	void printQInt(int base);
	bool isNegative() const;
	QInt decToBin(string src);
	QInt hexToBin(string src);
	string multipleByTwo(string src, int add);
	string binToDec(const QInt& src);
	string binToHex(const QInt& src);
	void mergeByFourBit(string a, string& b);
	QInt operator & (const QInt&);
	QInt operator | (const QInt&);
	QInt operator ^ (const QInt&);
	QInt operator ~();

	QInt operator +(const QInt&);
	QInt operator -(const QInt&);
	QInt operator * (const QInt&);
	QInt operator / (const QInt&);

	bool operator == (const QInt&);
	bool operator != (const QInt&);
	QInt& operator = (const QInt&);
	bool operator < (const QInt&);
	bool operator > (const QInt&);
	bool operator <=(const QInt&);
	bool operator >= (const QInt&);

	QInt operator <<(int);
	QInt operator >>(int);

	QInt rol();
	QInt ror();
	QInt rol(int);
	QInt ror(int);
	void printAllQInt(QInt& x);
	QInt CaculatorQint(string ss, int base);
	void ConvertAllToQint();
	bool CompareTwoString();
};

