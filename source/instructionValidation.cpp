#include "header.h"

int instruc_size(string str)
{
  static string one_byte[] = {"MOV", "XCHG", "ADD", "SUB", "INR", "DCR", "INX", "DCX", "DAD", "CMA", "CMP", "LDAX", "STAX", "HLT", "ANA", "ORA", "XRA"};
  static string two_byte[] = {"MVI", "ADI", "SUI", "CPI", "ANI", "ORI", "XRI"};
  static string three_byte[] = {"LDA", "LXI", "STA", "LHLD", "SHLD", "JMP", "JC", "JNC", "JZ", "JNZ"};
  for(int i = 0; i < 17; ++i)
  {
    if(str.compare(one_byte[i]) == 0)
      return 1;
  }
  for(int i = 0; i < 7; ++i)
  {
    if(str.compare(two_byte[i]) == 0)
      return 2;
  }
  for(int i = 0; i < 10; ++i)
  {
    if(str.compare(three_byte[i]) == 0)
      return 3;
  }
  return 0;
}

bool valid_register(char reg, bool pair = false)
{
	if(pair)
	{
		switch(reg)
		{
			case 'B':
			case 'D':
			case 'H':
				return true;
		}
	}
	else
	{
		switch(reg)
		{
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'H':
			case 'L':
			case 'M':
				return true;
		}
	}
	return false;
}

bool valid_data(string data)
{
	if(data.length() != 2)
		return false;
	for(int i = 0; i < 2; ++i)
	{
		switch(data[i])
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
				break;
			default:
				return false;
		}
	}
	return true;
}

bool valid_address(string addr)
{
	if(addr.length() != 4)
		return false;
	for(int i = 0; i < 4; ++i)
	{
		switch(addr[i])
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
				break;
			default:
				return false;
		}
	}
	return true;
}

vector<string> getParts(string cmd)
{
	vector<string> cmdParts;
	string str;
	int tmp = cmd.find(' ');
	if(tmp == -1)
		str = cmd;
	else
		str = cmd.substr(0, tmp);

	int size = instruc_size(str);

	if(size == 1)
		cmdParts.push_back(cmd);
	else if(size == 2)
	{
		if(str == "MVI" && cmd[5] == ' ')
		{
			if(cmd.length() != 8)
				return cmdParts;
			cmdParts.push_back(cmd.substr(0, 5));
			cmdParts.push_back(cmd.substr(6, 2));
		}
		else
		{
			if(cmd.length() != 6)
				return cmdParts;
			cmdParts.push_back(str);
			cmdParts.push_back(cmd.substr(4, 2));
		}
	}
	else if(size == 3)
	{
		if(str == "LXI")
		{
			if(cmd.length() != 10)
				return cmdParts;
			cmdParts.push_back(cmd.substr(0, 5));
			cmdParts.push_back(cmd.substr(6, 4));
		}
		else if(str == "JC" || str == "JZ")
		{
			if(cmd.length() != 7)
				return cmdParts;
			cmdParts.push_back(str);
			cmdParts.push_back(cmd.substr(3, 4));
		}
		else
		{
			if(((str == "LHLD" || str == "SHLD") && cmd.length() != 9) || ((str == "LDA" || str == "STA" || str == "JNC" || str == "JNZ" || str == "JMP") && cmd.length() != 8))
				return cmdParts;
			cmdParts.push_back(str);
			if(str == "LHLD" || str == "SHLD")
				cmdParts.push_back(cmd.substr(5, 4));
			else
				cmdParts.push_back(cmd.substr(4, 4));
		}
	}
	return cmdParts;
}

bool operand_check(vector<string> cmd)
{
	string str;
	int tmp = cmd[0].find(' ');
	if(tmp == -1)
		str = cmd[0];
	else
		str = cmd[0].substr(0, tmp);

	int size = instruc_size(str);

	if(size == 1)
	{
		if(str == "MOV" && cmd[0][5] == ',')
			return valid_register(cmd[0][4]) && valid_register(cmd[0][6]) && (cmd[0].length() == 7);
		if(str == "CMA" || str == "HLT" || str == "XCHG")
			return str.length() == cmd[0].length();
		if(str == "ADD" || str == "CMP" || str == "DCR" || str == "INR" || str == "SUB" || str == "ANA" || str == "ORA" || str == "XRA")
			return valid_register(cmd[0][4]) && (cmd[0].length() == 5);
		if(str == "LDAX" || str == "STAX")
			return valid_register(cmd[0][5], true) && (cmd[0].length() == 6);
		if(str == "DAD" || str == "DCX" || str == "INX")
			return valid_register(cmd[0][4], true) && (cmd[0].length() == 5);
	}
	else if(size == 2)
	{
		if(str == "MVI")
			return valid_register(cmd[0][4]) && valid_data(cmd[1]);
		else
			return valid_data(cmd[1]);
	}
	else if(size == 3)
	{
		if(str == "LXI")
			return valid_register(cmd[0][4], true) && valid_address(cmd[1]);
		else
			return valid_address(cmd[1]);
	}
	return false;
}

bool instruction_check(string cmd)
{
	vector<string> parts = getParts(cmd);
	if(parts.size() !=0 && operand_check(parts))
		return true;
	return false;
}