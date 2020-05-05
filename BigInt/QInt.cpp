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

//Xuat QInt theo co so 2
void QInt::printQInt(int base)
{
	string res;
	res = CreateBinStr();
	while (res[0] == '0' && res.length() > 1)
		res.erase(0, 1);
	cout << res;
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
