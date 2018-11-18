#include "header.h"

/*	Return the size of the instruction (1 byte, 2 byte, or 3 byte)
*/
int instruc_size(string str)
{
	//	1 byte instruction's opcodes
	static string one_byte[] = {"MOV", "XCHG", "ADD", "SUB", "INR", "DCR", "INX", "DCX", "DAD", "CMA", "CMP", "LDAX", "STAX", "HLT", "ANA", "ORA", "XRA"};
	//	2 byte instruction's opcodes
	static string two_byte[] = {"MVI", "ADI", "SUI", "CPI", "ANI", "ORI", "XRI"};
	//	3 byte instruction's opcodes
	static string three_byte[] = {"LDA", "LXI", "STA", "LHLD", "SHLD", "JMP", "JC", "JNC", "JZ", "JNZ"};

	//	Compare the opcode and return the size
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

	//	Return 0 if not found
	return 0;
}

/*	Check whether the register used are valid or not
*/
bool valid_register(char reg, bool pair = false)
{
	if(pair)	//	If register to be checked belong to a register pair
	{
		switch(reg)
		{
			case 'B':
			case 'D':
			case 'H':
				return true;
		}
	}
	else	//	If register to be checked does not belong to a register pair
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

/*	Check whether valid 8 byte data is passed
*/
bool valid_data(string data)
{
	//	Checking on the basis of length
	if(data.length() != 2)
		return false;

	//	Checking the digits of the data
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

/*	Check whether valid address is passed
*/
bool valid_address(string addr)
{
	//	Checking on the basis of length
	if(addr.length() != 4)
		return false;

	//	Checking the digits of the address
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

/*	Splitting the input command into parts to validate the instruction
*/
vector<string> getParts(string cmd)
{
	vector<string> cmdParts;	//	To store parts of command
	string str;		//	To save the opcode

	int tmp = cmd.find(' ');
	
	if(tmp == -1)
		str = cmd;
	else
		str = cmd.substr(0, tmp);

	int size = instruc_size(str);	//	Getting instruction size

	if(size == 1)	//	Append the 1 byte instruction of parts
		cmdParts.push_back(cmd);
	else if(size == 2)	//	For 2 byte instructions
	{
		if(str == "MVI" && cmd[5] == ' ')	//	Store parts if opcode is "MVI"
		{
			if(cmd.length() != 8)	//	Checking the length of instruction
				return cmdParts;

			//	Storing parts of the command
			cmdParts.push_back(cmd.substr(0, 5));
			cmdParts.push_back(cmd.substr(6, 2));
		}
		else	//	For remaining 2 byte instructions
		{
			if(cmd.length() != 6)	//	Checking the length of instruction
				return cmdParts;

			//	Storing parts of the command
			cmdParts.push_back(str);
			cmdParts.push_back(cmd.substr(4, 2));
		}
	}
	else if(size == 3)	//	For 3 byte instructions
	{
		if(str == "LXI")	//	Store parts if opcode is "LXI"
		{
			if(cmd.length() != 10)	//	Checking the length of instruction
				return cmdParts;
			
			//	Storing parts of the command
			cmdParts.push_back(cmd.substr(0, 5));
			cmdParts.push_back(cmd.substr(6, 4));
		}
		else if(str == "JC" || str == "JZ")		//	Store parts if opcode is "JC" or "JZ"
		{
			if(cmd.length() != 7)	//	Checking the length of instruction
				return cmdParts;

			//	Storing parts of the command
			cmdParts.push_back(str);
			cmdParts.push_back(cmd.substr(3, 4));
		}
		else	//	Store parts for remaining 3 byte instructions
		{
			if(((str == "LHLD" || str == "SHLD") && cmd.length() != 9) || ((str == "LDA" || str == "STA" || str == "JNC" || str == "JNZ" || str == "JMP") && cmd.length() != 8))		//	Checking the length of instruction for respective opcode				
				return cmdParts;

			//	Storing parts of the command
			cmdParts.push_back(str);
			if(str == "LHLD" || str == "SHLD")
				cmdParts.push_back(cmd.substr(5, 4));
			else
				cmdParts.push_back(cmd.substr(4, 4));
		}
	}
	return cmdParts;
}

/*	Check whether operand is correct from parts
*/
bool operand_check(vector<string> cmd)
{
	string str;	//	Store the opcode
	
	int tmp = cmd[0].find(' ');

	if(tmp == -1)
		str = cmd[0];
	else
		str = cmd[0].substr(0, tmp);

	int size = instruc_size(str);	//	Getting size of instruction

	if(size == 1)	//	Checking validity for 1 byte instructions
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
	else if(size == 2)	//	Checking validity for 2 byte instructions
	{
		if(str == "MVI")
			return valid_register(cmd[0][4]) && valid_data(cmd[1]);
		else
			return valid_data(cmd[1]);
	}
	else if(size == 3)	//	Checking validity for 3 byte instructions
	{
		if(str == "LXI")
			return valid_register(cmd[0][4], true) && valid_address(cmd[1]);
		else
			return valid_address(cmd[1]);
	}
	return false;
}

/*	Driver function for instruction validation
*/
bool instruction_check(string cmd)
{
	vector<string> parts = getParts(cmd);
	if(parts.size() !=0 && operand_check(parts))
		return true;
	return false;
}