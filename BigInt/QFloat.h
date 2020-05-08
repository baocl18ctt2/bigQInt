#pragma once


#include <iostream>
using namespace std;
#include <string>
#include <fstream>

class Qfloat
{
private:
	int data[4];
public:
	Qfloat();
	~Qfloat();
	void setBit1(int& X, int i);
	void setBit0(int& X, int i);
	int GetBit(int X, int i);
	void setDayBitKhong(int daybit[], int n);
	void stringToBit(string str, int daybit[]);
	void stringToBit2(string str, int daybit[]);
	void tachString(string str, string& str1, string& str2);
	void chuanHoaDayBit(int daybit[], int daybit1[], int daybit2[], int& E);
	void decToBin(int dec, int bin[16]);
	void ScanQfloat(string str, int);

	int binToDec(int bin[15]);
	void tinhHaiMuX(int dayso[100], int x);
	void tinhHaiMuTruX(int dayso[], int x);
	void congHaiDaySo(int daybit[100], int kq[100]);
	int xuLyPrint(int kq1[], int kq2[]);
	string PrintQfloat(int);
	Qfloat BinToDec(string);
	string DecToBin(Qfloat);
};

