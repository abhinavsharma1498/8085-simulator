#include "header.h"

/*	Utility function to convert character to integer
*/
int to_int(char ch)
{
	static map<char, int> lookup;
	static bool isFirst = true;
	if(isFirst)
	{
		for(int i = 0; i < 16; ++i)
			lookup["0123456789ABCDEF"[i]] = i;
		isFirst = false;
	}
	return lookup[ch];
}

/*	Utility function to convert integer to character
*/
char to_char(int num)
{
	static map<int, char> lookup;
	static bool isFirst = true;
	if(isFirst)
	{
		for(int i = 0; i < 16; ++i)
			lookup[i] = "0123456789ABCDEF"[i];
		isFirst = false;
	}
	return lookup[num];
}

/*	Utility function to convert binary to hexadecimal
*/
string to_hex(string bin)
{
	string hex = "";
	int tmp = 0;
	for(int i = 0; i < 4; ++i)
		tmp += (bin[3-i] - '0') * pow(2, i);
	// cout<<to_char(tmp)<<":";
	hex += to_char(tmp);
	tmp = 0;
	for(int i = 0; i < 4; ++i)
		tmp += (bin[7-i] - '0') * pow(2, i);
	// cout<<tmp<<":";
	hex += to_char(tmp);
	return hex;
}

/*	Utility function to convert hexadecimal to binary
*/
string to_bin(string hex)
{
	string bin = "";
	int tmp = to_int(hex[1]), i = 4;
	while(i--)
	{
		bin = to_char(tmp%2) + bin;
		// cout<<bin<<" ";
		tmp /= 2;
	}
	tmp = to_int(hex[0]);
	i = 4;
	while(i--)
	{
		bin = to_char(tmp%2) + bin;
		tmp /= 2;
		// cout<<bin<<" ";
	}
	return bin;
}

/*	Utility function to add two hexadecimal numbers and set respective flags
*/
string addition(string hex1, string hex2, bool &AC, bool &CF)
{
	int carry = 0;
	string sum = "";
	for(int i = 0; i < hex1.length(); ++i)
		sum += " ";
	for(int i = hex1.length() - 1; i > -1; --i)
	{
		int sumDigit = to_int(hex1[i]) + to_int(hex2[i]) + carry;
		if(sumDigit >= 16)
		{
			carry = 1;
			sumDigit -= 16;
		}
		else
			carry = 0;
		sum[i] = to_char(sumDigit);
		if(i == 2)
			AC = (carry == 1)?true:false;
	}
	CF = (carry == 1)?true:false;
	return sum;
}

/*	Utility function to get complement to hexadecimal number
*/
string complement(string hex)
{
	string comp = "";
	for(int i = 0; i < hex.length(); ++i)
		comp += to_char(15 - to_int(hex[i]));
	return comp;
}

/*	Utility function to subtract two hexadecimal numbers and set respective flags
*/
string subtraction(string hex1, string hex2, bool &AC, bool &CF, bool sixteen)
{
	bool tmp;
	if(sixteen)
		return (addition(hex1, addition(complement(hex2), "0001", tmp, tmp), AC, CF));
	return (addition(hex1, addition(complement(hex2), "01", tmp, tmp), AC, CF));
}

/*	Utility function to perform logical AND on two hexadecimal numbers
*/
string logicand(string hex1, string hex2)
{
	string bin1 = to_bin(hex1), bin2 = to_bin(hex2), res = "";
	for(int i = 0; i < bin1.length(); ++i)
		if(bin1[i] == '1' && bin2[i] == '1')
			res += '1';
		else
			res += '0';
	return to_hex(res);
}

/*	Utility function to perform logical OR on two hexadecimal numbers
*/
string logicor(string hex1, string hex2)
{
	string bin1 = to_bin(hex1), bin2 = to_bin(hex2), res = "";
	for(int i = 0; i < bin1.length(); ++i)
		if(bin1[i] == '1' || bin2[i] == '1')
			res += '1';
		else
			res += '0';
	return to_hex(res);
}

/*	Utility function to perform logical XOR on two hexadecimal numbers
*/
string logicxor(string hex1, string hex2)
{
	string bin1 = to_bin(hex1), bin2 = to_bin(hex2), res = "";
	for(int i = 0; i < bin1.length(); ++i)
		if(bin1[i] != bin2[i])
			res += '1';
		else
			res += '0';
	return to_hex(res);
}

/*	Function to set 8085 flags
*/
string setFlags(string hex, bool AC, bool CF)
{
	string bin = "00000000";

	//	Sign flag
	if((hex[0] >= '8' && hex[0] <= '9') || (hex[0] >= 'A' && hex[0] <= 'F'))
		bin[0] = '1';

	//	Zero flag
	if(hex.compare("00") == 0)
		bin[1] = '1';

	//	Auxilary carry flag
	bin[3] = AC?'1':'0';

	//	Parity flag
	for(int i = 0; i < 2; ++i)
	{
		switch(hex[i])
		{
			case '1':
			case '2':
			case '4':
			case '7':
			case '8':
			case 'B':
			case 'D':
			case 'E':
				if(bin[5] == '0')
					bin[5] = '1';
				else if(bin[5] == '1')
					bin[5] = '0';
		}
	}

	//	Carry flag
	bin[7] = CF?'1':'0';

	return to_hex(bin);
}