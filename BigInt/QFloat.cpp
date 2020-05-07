#include "Qfloat.h"

Qfloat::Qfloat()
{
	for (int i = 0; i < 4; i++)
	{
		data[i] = 0;
	}
}

Qfloat::~Qfloat()
{
}

void Qfloat::setBit1(int& X, int i)
{
	X = (X | (1 << (31 - i)));
}

int Qfloat::GetBit(int X, int i)
{
	return (X >> (31 - i)) & 1;
}

void Qfloat::setDayBitKhong(int daybit[], int n)
{
	for (int i = 0; i < n; i++) {
		daybit[i] = 0;
	}
}

void Qfloat::stringToBit(string str, int daybit[])// Biến đổi phần nguyên thành dãy bit
{
	setDayBitKhong(daybit, 112);
	int leng = str.length();
	int* songuyenlon = new int[100];
	int t = 0;
	if (str.compare(0, 1, "-") == 0) {//Nếu là số âm thì trừ độ dài số trừ đi 1
		leng = leng - 1;
		t = 1;
	}
	for (int i = 0; i < leng; i++) {
		songuyenlon[i] = (int)str[i + t] - 48; // Biến đổi chuỗi thành số và lưu trong mảng
	}
	int dem = 0;
	for (int j = 0; ; j++) {
		dem = 0;
		if (songuyenlon[leng - 1] % 2 != 0) // Gán bít bằng 1 nếu số cuối lẻ
			daybit[111 - j] = 1;
		for (int l = 0; l < leng; l++) { //Chia mảng số nguyên cho 2
			if (songuyenlon[l] % 2 != 0)
				songuyenlon[l + 1] = songuyenlon[l + 1] + 10;
			songuyenlon[l] = songuyenlon[l] / 2;
			if (songuyenlon[l] == 0) {
				dem++;
			}
		}
		if (dem == leng) { // Mảng số nguyên bằng 0 thì dừng
			break;
		}
	}
}

void Qfloat::stringToBit2(string str, int daybit[]) // Biến đổi phần thập phân thành dãy bit
{
	setDayBitKhong(daybit, 112);
	int leng = str.length();
	int* sothapphan = new int[100];
	setDayBitKhong(sothapphan, 100);

	for (int i = 0; i < leng; i++) {
		sothapphan[i] = (int)str[i] - 48; // Biến đổi chuỗi thành số và lưu trong mảng
	}
	int dem = 0;
	int m = 0;
	for (int i = 0; i < 112; i++) {
		if (sothapphan[0] >= 5) {// Gán bit bằng 1 nếu số đâu >= 5 (sử dụng phương pháp nhan hai)
			daybit[i] = 1;
		}
		dem = 0, m = 0;
		for (int j = leng - 1; j >= 0; j--) {// Nhân 2 chuỗi thập phân
			if (2 * sothapphan[j] < 10) {
				sothapphan[j] = (sothapphan[j] * 2) + m;
				m = 0;
			}
			else {
				sothapphan[j] = (2 * sothapphan[j] - 10) + m;
				m = 1;// Lớn hơn 10 thì nhớ 1
			}
			if (sothapphan[j] == 0) {
				dem++;
			}
		}
		if (dem == leng) { // Mảng số nguyên bằng 0 thì dừng
			break;
		}
	}
}

void Qfloat::tachString(string str, string& str1, string& str2)// Tách chuỗi số nguyên ban đầu thành phần nguyên và phần thập phân
{																// (Phân cách nhau bới dấu ".")
	int leng = str.length();
	int i;
	for (i = 0; i < leng; i++)
	{
		if (str.compare(i, 1, ".") == 0) {
			break;
		}
	}
	str1 = str.substr(0, i);
	str2 = str.substr(i + 1, leng - 1);
}

void Qfloat::chuanHoaDayBit(int daybit[], int daybit1[], int daybit2[], int& E)// Chuẩn hóa về dạng 1.F * 2^E
{
	int i;
	for (i = 0; i < 112; i++) {
		if (daybit1[i] == 1)break;
	}
	int k = 0;
	if (i <= 111) {// Nếu phần nguyên khác 0
		for (int j = i + 1; j < 112; j++) {
			daybit[k] = daybit1[j];
			k++;
		}
		E = k;
		for (int j = 0; j < 112; j++)
		{
			daybit[k] = daybit2[j];
			k++;
		}
	}
	else {// Nếu phần nguyên bằng 0
		int j = 0;
		for (j = 0; j < 112; j++) {
			if (daybit2[j] == 1)break;
		}
		E = -j - 1;
		for (int l = j + 1; l < 112; l++)
		{
			daybit[k] = daybit2[l];
			k++;
		}
	}
}

void Qfloat::decToBin(int dec, int bin[16])// Đổi số thập phân thành nhị phân
{
	setDayBitKhong(bin, 16);
	for (int i = 15; dec > 0; i--) {
		if (dec % 2 != 0) {
			bin[i] = 1;
		}
		dec = dec / 2;
	}
}

void Qfloat::ScanQfloat(string str, int base)// In chuỗi số chấm động
{
	if (base == 2)
	{
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == '1')
			{
				setBit1(data[i / 32], i % 32);
			}
		}
	}
	if (base == 10)
	{
		string str1, str2;
		tachString(str, str1, str2);
		int daybit1[112];
		int daybit2[112];
		stringToBit(str1, daybit1);
		stringToBit2(str2, daybit2);

		int daybit[224];
		setDayBitKhong(daybit, 224);
		int E;
		chuanHoaDayBit(daybit, daybit1, daybit2, E);

		if (str.compare(0, 1, "-") == 0) {// Nếu là số âm thì thì phần bitSign dấu bằng 1 và ngược lại
			setBit1(data[0], 0);
		}
		int Exp = E + 16383;// Phần mũ Exponent với thừa số K = 16383 (K = 2^(15-1) - 1)
		int ExpBin[16];
		decToBin(Exp, ExpBin);

		for (int i = 1; i < 16; i++) {
			if (ExpBin[i] == 1) {
				setBit1(data[i / 32], i % 32); // Gán dãy bít vào QInt
			}
		}
		for (int i = 16; i < 128; i++) {
			if (daybit[i - 16] == 1) {
				setBit1(data[i / 32], i % 32); // Gán dãy bít vào QInt
			}
		}
	}
}

int Qfloat::binToDec(int bin[15])// Đổi nhị phân sang thập phân
{
	int dec = 0;
	for (int i = 0; i < 15; i++) {
		dec = dec + bin[14 - i] * pow(2, i);
	}
	return dec;
}

void Qfloat::tinhHaiMuX(int dayso[100], int x)// Tính 2 mũ x
{
	setDayBitKhong(dayso, 100);
	if (x == 0) { // 2 mũ 0 bằng 1
		dayso[99] = 1;
		return;
	}
	dayso[99] = 2;
	int m = 0;
	for (int i = 99; i > 100 - x; i--) {
		for (int k = 99; k >= 0; k--)
		{
			if (2 * dayso[k] < 10) {
				dayso[k] = (dayso[k] * 2) + m;
				m = 0;
			}
			else {
				dayso[k] = (2 * dayso[k] - 10) + m;
				m = 1;// Lớn hơn 10 thì nhớ 1
			}
		}
	}
}

void Qfloat::tinhHaiMuTruX(int dayso[], int x)// Tính 2 mũ trừ x
{
	setDayBitKhong(dayso, 100);
	dayso[0] = 5;
	if (x == -1) {
		return;
	}
	for (int i = 1; i < -x; i++) {
		for (int k = 0; k < 100; k++) {
			if (dayso[k] % 2 != 0)
				dayso[k + 1] += 10;
			dayso[k] = (dayso[k] / 2);
		}
	}
}

void Qfloat::congHaiDaySo(int daybit[100], int kq[100])// Cộng hai dãy số nguyên
{
	for (int i = 99; i >= 0; i--) {
		if (kq[i] + daybit[i] < 10) {
			kq[i] = kq[i] + daybit[i];
		}
		else {
			kq[i] = kq[i] + daybit[i] - 10;
			kq[i - 1] += 1;
		}

	}
}

int Qfloat::xuLyPrint(int kq1[], int kq2[])// In chuỗi số đã nhập từ số chấm động
{
	int ExpBin[15];
	setDayBitKhong(ExpBin, 15);
	for (int i = 1; i < 16; i++) {
		if (GetBit(data[i / 32], i % 32) == 1) {
			ExpBin[i - 1] = 1;
		}
	}
	int dec = binToDec(ExpBin);
	if (dec == 32767) { // Mũ toàn bit 1
		for (int i = 16; i < 112; i++) {
			if (GetBit(data[i / 32], i % 32) == 1) {
				return 1;
			}
		}
		return -1;
	}
	if (dec == 0) {// Mũ toàn bit 0
		for (int i = 16; i < 112; i++) {
			if (GetBit(data[i / 32], i % 32) == 1) {
				return 2;
			}
		}
		return 3;
	}
	int E = dec - 16383;

	setDayBitKhong(kq1, 100);
	setDayBitKhong(kq2, 100);
	int temp[100];
	setDayBitKhong(temp, 100);
	int daybit1[112];
	int daybit2[112];
	setDayBitKhong(daybit1, 112);
	setDayBitKhong(daybit2, 112);
	if (E < 0) {		// Nếu E < 0, tức phần nguyên bằng 0
		daybit2[-E - 1] = 1;//Dãy bit của phần thập phân
		for (int i = 16; i < 112; i++) {
			daybit2[-E + i - 16] = GetBit(data[i / 32], i % 32);
		}
	}
	else {// E > 0, tức phần nguyên khác 0
		daybit1[111 - E] = 1;// Dãy bit của phần nguyên
		for (int i = 16; i < 16 + E; i++) {
			daybit1[i - 15 + 111 - E] = GetBit(data[i / 32], i % 32);
		}
		for (int i = 16 + E; i < 112; i++) {
			daybit2[i - (16 + E)] = GetBit(data[i / 32], i % 32);//Dãy bit của phần thập phân
		}
		for (int i = 1; i < 112; i++) {// Cộng phần nguyên
			if (daybit1[i] == 1) {
				tinhHaiMuX(temp, 111 - i);
				congHaiDaySo(temp, kq1);
			}
		}
	}
	for (int i = 1; i < 112; i++) {// Cộng phần thập phân
		if (daybit2[i - 1] == 1) {
			tinhHaiMuTruX(temp, -i);
			congHaiDaySo(temp, kq2);
		}
	}
	return 0;
}

string Qfloat::PrintQfloat(int base)
{
	string ketqua;
	if (base == 2)
	{
		ketqua.push_back(char(GetBit(data[0], 0)) + 48);
		ketqua.push_back(' ');
		for (int i = 1; i < 16; i++) {
			ketqua.push_back(char(GetBit(data[i / 32], i % 32)) + 48); // In dãy QInt ra màn hình
		}
		ketqua.push_back(' ');
		for (int i = 16; i < 128; i++) {
			ketqua.push_back(char(GetBit(data[i / 32], i % 32)) + 48); // In dãy QInt ra màn hình
		}
	}
	if (base == 10)
	{
		int kq1[100];
		int kq2[100];
		int test = xuLyPrint(kq1, kq2);
		if (test == -1) return "NaN – Not a Number";
		if (test == 1) return "Infinity";
		if (test == 2) return "Denormalized";
		if (test == 3)return "0";
		cout << endl;
		int i = 0;
		if (GetBit(data[0], 0)) {// In dấu trừ
			ketqua.push_back('-');
		}
		for (i = 0; i < 99; i++) {// Bỏ qua các số 0 trong dãy 100 số in ra
			if (kq1[i] != 0) break;
		}
		for (int j = i; j < 100; j++) {
			ketqua.push_back(char(kq1[j]) + 48);
		}
		ketqua.push_back('.');
		for (int j = 0; j < 25; j++) {
			ketqua.push_back(char(kq2[j]) + 48);
		}
	}
	return ketqua;
}

Qfloat Qfloat::BinToDec(string bit)
{
	ScanQfloat(bit, 2);
	return *this;
}

string Qfloat::DecToBin(Qfloat x)
{
	string ketqua;
	ketqua = x.PrintQfloat(2);
	return ketqua;
}

