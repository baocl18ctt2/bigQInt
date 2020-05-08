#include "QInt.h"


QInt::QInt()
{
	for (int i = 0; i < QINT_SIZE; i++)
	{
		arr[i] = 0;
	}
}

QInt::~QInt()
{

}
//Lay bit
bool QInt::getBit(int pos) const
{
	int bytePos = QINT_SIZE - 1 - pos / 32;
	int bitPos = pos % 32;
	return ((this->arr[bytePos] >> bitPos) & 1);
}

//Cap nhat vi tri bit
void QInt::setBit(int pos, bool value)
{
	int bytePos = QINT_SIZE - 1 - pos / 32;
	int bitPos = pos % 32;
	if (value)
	{
		this->arr[bytePos] = ((1 << bitPos) | this->arr[bytePos]);
	}
	else
	{
		this->arr[bytePos] = ((~(1 << bitPos)) & this->arr[bytePos]);
	}
}

//Nhap QInt theo co so
void QInt::scanQInt(string src, int base)
{
	int bitPos = 0;
	switch (base)
	{
	case 2:
		for (int i = src.length() - 1; i >= 0; i--)
		{
			setBit(bitPos, src[i] == '1');
			bitPos++;
		}
		break;
	case 10:
	{
		*this = decToBin(src);
		break;
	}
	case 16:
	{
		*this = hexToBin(src);
		break;
	}
	}
}

//Xuat QInt theo co so 
void QInt::printQInt(int base)
{
	string res;
	switch (base)
	{
	case 2:
	{
		res = CreateBinStr();
		while (res[0] == '0' && res.length() > 1)
			res.erase(0, 1);
		cout << left << setw(10) << "\t|	3. BIN:   " << setw(10) << res << endl;
		break;
	}
	case 10:
	{
		cout << left << setw(10) << "\t|	2. DEC:   " << setw(10) << binToDec(*this) << endl;
		break;
	}
	case 16:
	{
		cout << left << setw(10) << "\t|	1. HEX:   " << setw(10) << binToHex(*this) << endl;
		break;
	}
	}
}

//Kiem tra so am
bool QInt::isNegative() const
{
	return (this->getBit(QINT_SIZE * 32 - 1));
}

// Tao ra mang 128 bit
string QInt::CreateBinStr() const
{
	string res = "";
	for (int i = 0; i < QINT_SIZE; i++)
	{
		res += bitset<32>(this->arr[i]).to_string();
	}
	return res;
}

string divByTwo(string src)
{
	string res = "";
	int digit = 0;
	for (int i = 0; i < src.length(); i++)
	{
		digit += src[i] - '0';
		int phannguyen = digit / 2;
		int phandu = digit % 2;
		if (phandu == 0)
			digit = 0;
		else
			digit = 10;
		res += phannguyen + '0';
	}
	if (res[0] == '0' && res.length() > 1)
		res.erase(0, 1);
	return res;
}
QInt QInt::toInverse() const
{
	//Dao bit
	QInt res;
	for (int i = 0; i < QINT_SIZE; i++)
	{
		res.arr[i] = ~this->arr[i];
	}
	//Cong 1
	for (int i = QINT_SIZE - 1; i >= 0; i--)
	{
		if (res.arr[i] < pow(2, 31) - 1)
		{
			res.arr[i] += 1;
			break;
		}
		else
			res.arr[i] = 0;
	}
	return res;
}

QInt QInt::decToBin(string src)
{
	QInt res;
	bool isNegative = false;
	if (src[0] == '-')
	{
		isNegative = true;
		src.erase(0, 1);
	}
	string binStr = "";
	do
	{
		int lastDigit = src[src.length() - 1] - '0';
		if (lastDigit % 2 == 0)
			binStr += '0';
		else
			binStr += '1';
		src = divByTwo(src);
	} while (src != "0");
	// Xuat bit theo thu tu nguoc lai.
	reverse(binStr.begin(), binStr.end());
	res.scanQInt(binStr, 2);
	if (isNegative == true)
	{
		res = res.toInverse();
	}
	return res;
}

QInt QInt::hexToBin(string src)
{
	bool isNegative = false;
	if (src[0] == '-')
	{
		isNegative = true;
		src.erase(0, 1);
	}
	QInt res;
	string binStr = "";
	for (int i = 0; i < src.length(); i++)
	{
		int pos = ((string)HEX_CHARS).find(src[i], 0);
		binStr += bitset<4>(pos).to_string();
	}
	res.scanQInt(binStr, 2);
	if (isNegative == true)
		res = res.toInverse();
	return res;
}

bool QInt::IsZero() const
{
	for (int i = 0; i < QINT_SIZE; i++)
	{
		if (arr[i] != 0)
			return false;
	}
	return true;
}

string QInt::multipleByTwo(string src, int add)
{
	string res = "";
	int carry = add;

	for (int i = src.length() - 1; i >= 0; i--)
	{
		int temp = src[i] - '0';
		temp = temp * 2 + carry;
		res += (temp % 10 + '0');
		carry = temp / 10;
	}
	if (carry > 0)
	{
		res += (carry + '0');
	}
	reverse(res.begin(), res.end());
	return res;
}
string QInt::binToDec(const QInt& src)
{
	string result;
	if (src.IsZero())
	{
		result = "0";
		return result;
	}
	QInt posSrc = src;
	if (src.isNegative())
	{
		posSrc = posSrc.toInverse();
	}
	string binStr = posSrc.CreateBinStr();
	int pos = binStr.find('1', 0) + 1;
	result = "1";
	while (pos < binStr.length())
	{
		int add = binStr[pos] - '0';
		result = multipleByTwo(result, add);
		pos++;
	}
	if (src.isNegative() == true)
		result = '-' + result;
	return result;
}
string QInt::binToHex(const QInt& src)
{
	string result = "";
	if (src.IsZero())
	{
		result = "0";
		return result;
	}
	QInt posSrc = src;
	string binStr = posSrc.CreateBinStr();
	int pos = binStr.length() - 1;
	while (pos >= 0)
	{
		string temp = "";
		while (pos % 4 != 0)
		{
			temp += binStr[pos];
			pos--;
		}
		temp += binStr[pos];
		reverse(temp.begin(), temp.end());
		mergeByFourBit(temp, result);
		pos--;
	}
	reverse(result.begin(), result.end());
	while (result[0] == '0' && result.length() > 1)
		result.erase(0, 1);
	return result;
}

void QInt::mergeByFourBit(string a, string& b)
{
	int remainder = 0;
	int k = 0;
	for (int i = a.length() - 1; i >= 0; i--)
	{
		remainder += (a[i] - '0') * pow(2, k);
		k++;
	}
	int m;
	if (remainder == 0)
		b += remainder + '0';
	while (remainder > 0)
	{
		m = remainder % 16;
		if (m >= 10) {
			b += (char)(m + CHAR_55);

		}
		else {
			b += (char)(m + CHAR_48);
		}
		remainder = remainder / 16;
	}
	

}

QInt QInt::operator+(const QInt& A)
{
	QInt result;
	bool biennho = 0;
	for (int i = 0; i < QINT_SIZE *32;i++)
	{
		int temp = (*this).getBit(i) + A.getBit(i) + biennho;
		switch (temp)
		{
		case 0:
		{
			result.setBit(i, 0);
			biennho = 0;
			break;
		}
		case 1:
		{
			result.setBit(i, 1);
			biennho = 0;
			break;
		}
		case 2:
		{
			result.setBit(i, 0);
			biennho = 1;
			break;
		}
		case 3:
		{
			result.setBit(i, 1);
			biennho = 1;
			break;
		}
		}
	}
	bool bitfirst = (*this).isNegative();
	bool bitfirst1 = A.isNegative();
	if (bitfirst1 + bitfirst != 1 && result.isNegative() != bitfirst)
		throw "OverFlow.";
	return result;
}
QInt QInt::operator-(const QInt& b)
{
	QInt temp = b;
	QInt temp1;
	temp1.scanQInt("1", 10);
	if (b.isNegative() == false)
	{
		temp = ~temp;
		temp = temp + temp1;

	}
	else
	{
		temp = temp - temp1;
		temp = ~temp;
	}
	QInt result = *this + temp;
	return result;
}

QInt QInt::operator*(const QInt& B)
{
	QInt Q = *this;
	bool bienNho = 0;
	QInt A;
	int n = 128;
	while (n > 0)
	{
		if (Q.getBit(0) == 0 && bienNho == 1)
		{
			A = A + B;
		}
		else if (Q.getBit(0) == 1 && bienNho == 0)
		{
			A = A - B;
		}
		// shiftRight Q,A,bienNho
		bienNho = Q.getBit(0);
		Q = Q >> 1;
		Q.setBit(127, A.getBit(0));
		A = A >> 1;
		n--;
	}
	return Q;
}

QInt QInt::operator/(const QInt& x)
{
	QInt Q = *this;
	QInt M = x;
	QInt A;
	if (*this == A)
	{
		return A;
	}
	bool checkNegative = (this->isNegative() ^ M.isNegative()); // kiem tra 2 so co trai dau ko
	QInt temp;
	temp.scanQInt("1", 10);
	if (Q.isNegative())
	{
		Q = ~(Q - temp);
	}
	if (M.isNegative())
	{
		M = ~(M - temp);
	}
	int k = 128;
	while (k > 0)
	{
		A = A << 1;
		A.setBit(0, Q.getBit(127));
		Q = Q << 1;
		A = A - M;
		if (A.isNegative())
		{
			A = A + M;
			Q.setBit(0, 0);
		}
		else
		{
			Q.setBit(0, 1);
		}
		k--;
	}
	if (checkNegative == true)
	{
		Q = ~Q + temp;
	}
	return Q;
}

QInt QInt::operator&(const QInt& x)
{
	QInt temp;
	for (int i = 0; i < QINT_SIZE; ++i)
	{
		temp.arr[i] = this->arr[i] & x.arr[i];
	}
	return temp;
}

QInt QInt::operator|(const QInt& x)
{
	QInt temp;
	for (int i = 0; i < 4; i++)
	{
		temp.arr[i] = this->arr[i] | x.arr[i];
	}
	return temp;
}

QInt QInt::operator^(const QInt& x)
{
	QInt temp;
	for (int i = 0; i < 4; i++)
	{
		temp.arr[i] = this->arr[i] ^ x.arr[i];
	}
	return temp;
}

QInt QInt::operator~()
{
	QInt temp;
	for (int i = 0; i < 4; ++i)
	{
		temp.arr[i] = ~this->arr[i];
	}
	return temp;
}

bool QInt::operator==(const QInt& x)
{
	if (this == &x)
		return true;
	for (int i = 0; i < QINT_SIZE; ++i)
	{
		if (this->arr[i] != x.arr[i])
		{
			return false;
		}
	}
	return true;
}

bool QInt::operator!=(const QInt& x)
{
	return (*this == x);
}

QInt& QInt::operator=(const QInt& x)
{
	for (int i = 0; i < QINT_SIZE; ++i)
	{
		this->arr[i] = x.arr[i];
	}
	return *this;
}

bool QInt::operator<(const QInt& x)
{
	if (*this == x)
		return false;
	bool A = this->isNegative();
	bool B = x.isNegative();
	if ((A + B) == 1)
	{
		if (A)
			return true;
		return false;
	}
	for (int i = 126; i >= 0; i--)
	{
		if (this->getBit(i) > x.getBit(i))
		{
			return false;
		}
		else if (this->getBit(i) < x.getBit(i))
		{
			return true;
		}
	}
}

bool QInt::operator>(const QInt& x)
{
	return !((*this < x) ^ (*this == x));

}

bool QInt::operator<=(const QInt& x)
{
	return (!(*this > x));
}

bool QInt::operator>=(const QInt& x)
{
	return (!(*this < x));
}
QInt QInt::operator<<(int x)
{
	QInt temp;
	for (int i = 127; i >= x; i--) {
		temp.setBit(i, this->getBit(i - x));
	}

	return temp;
}
QInt QInt::operator>>(int x)
{
	QInt temp;
	for (int i = 127; i > 127 - x; i--)
		temp.setBit(i, this->getBit(127));
	for (int i = 127 - x; i >= 0; i--)
		temp.setBit(i, this->getBit(i + x));
	return temp;
}
QInt QInt::rol(int x)
{
	for (int i = 0; i < x; i++)
		*this = this->rol();
	return *this;
}

QInt QInt::ror(int x)
{
	for (int i = 0; i < x; i++)
		*this = this->ror();
	return *this;
}



QInt QInt::rol()
{
	QInt temp;
	for (int i = 127; i >= 1; i--)
		temp.setBit(i, this->getBit(i - 1));
	temp.setBit(0, this->getBit(127));
	return temp;
}

QInt QInt::ror()
{
	QInt temp;
	temp.setBit(127, this->getBit(0));
	for (int i = 126; i >= 0; i--)
		temp.setBit(i, this->getBit(i + 1));
	return temp;
}
void QInt::printAllQInt()
{
	cout << "\n\n\t|--------------------------------------------------------" << endl;
	cout << "\t|" << endl;
	QInt::printQInt(16);
	QInt::printQInt(10);
	QInt::printQInt(2);
	cout << "\t|" << endl;
	cout << "\t|---------------------------------------------------------" << endl;
}

void QInt::Menu1()
{
	int select;
	while (true)
	{
		system("cls");
		cout << "\n\t ****************************" << endl;
		cout << " \t ----- CALCULATOR QINT ----- " << endl;
		cout << "\t 1. HEX" << endl;
		cout << "\t 2. DEC" << endl;
		cout << "\t 3. BIN" << endl;
		cout << "\t 0. EXIT" << endl;
		cout << " ** please select: ";
		cin >> select;
		string ss;
		if (select == 1)
		{
			cout << "\n -- Nhap chuoi: ";
			cin.ignore();
			getline(cin, ss);
			QInt::scanQInt(ss, 16);
			printAllQInt();
			system("pause");
		}
		if (select == 2)
		{
			cout << "\n -- Nhap chuoi: ";
			cin.ignore();
			getline(cin, ss);
			QInt::scanQInt(ss, 10);
			printAllQInt();
			system("pause");
		}
		if (select == 3)
		{
			cout << "\n -- Nhap chuoi: ";
			cin.ignore();
			getline(cin, ss);
			QInt::scanQInt(ss, 2);
			printAllQInt();
			system("pause");
		}
		if (select == 0)
			break;
	}
}
