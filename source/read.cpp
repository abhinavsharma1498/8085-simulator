#include "header.h"

int initialize(param *para)
{
	string pc;
	cout<<"Enter starting address: ";
	while(!valid_address(pc))
		cin>>pc;
	para->pc = pc;
	para->registers['A'] = "00";
	para->registers['F'] = "00";
	para->registers['B'] = "00";
	para->registers['C'] = "00";
	para->registers['D'] = "00";
	para->registers['E'] = "00";
	para->registers['H'] = "00";
	para->registers['L'] = "00";
	return 0;
}

int createFunctionMap(map<string, instruc> &functionMap)
{
	functionMap["MOV"] = MOV;
	functionMap["XCHG"] = XCHG;
	functionMap["ADD"] = ADD;
	functionMap["SUB"] = SUB;
	functionMap["INR"] = INR;
	functionMap["DCR"] = DCR;
	functionMap["INX"] = INX;
	functionMap["DCX"] = DCX;
	functionMap["DAD"] = DAD;
	functionMap["CMA"] = CMA;
	functionMap["CMP"] = CMP;
	functionMap["LDAX"] = LDAX;
	functionMap["STAX"] = STAX;
	functionMap["ANA"] = ANA;
	functionMap["ORA"] = ORA;
	functionMap["XRA"] = XRA;
	functionMap["MVI"] = MVI;
	functionMap["ADI"] = ADI;
	functionMap["SUI"] = SUI;
	functionMap["CPI"] = CPI;
	functionMap["ANI"] = ANI;
	functionMap["ORI"] = ORI;
	functionMap["XRI"] = XRI;
	functionMap["LDA"] = LDA;
	functionMap["STA"] = STA;
	functionMap["LXI"] = LXI;
	functionMap["LHLD"] = LHLD;
	functionMap["SHLD"] = SHLD;
	functionMap["JMP"] = JMP;
	functionMap["JC"] = JC;
	functionMap["JNC"] = JNC;
	functionMap["JZ"] = JZ;
	functionMap["JNZ"] = JNZ;
	functionMap["HLT"] = HLT;
	return 0;
}

param *add_to_memory(param *para, string cmd, string &pc)
{
	vector<string> parts = getParts(cmd);
	int space = cmd.find(' ');
	string str;
	if(space == -1)
		str = cmd;
	else
		str = cmd.substr(0, space);
	bool tmp;
	switch(instruc_size(str))
	{
		case 1:
			para->memory[pc] = parts[0];
			pc = addition(pc, "0001", tmp, tmp);
			break;
		case 2:
			para->memory[pc] = parts[0];
			pc = addition(pc, "0001", tmp, tmp);
			para->memory[pc] = parts[1];
			pc = addition(pc, "0001", tmp, tmp);
			break;
		case 3:
			para->memory[pc] = parts[0];
			pc = addition(pc, "0001", tmp, tmp);
			para->memory[pc] = parts[1].substr(2, 2);
			pc = addition(pc, "0001", tmp, tmp);
			para->memory[pc] = parts[1].substr(0, 2);
			pc = addition(pc, "0001", tmp, tmp);
			break;
	}
	return para;
}

string convert_upper(string str)
{
	for(int i = 0; i < str.length(); ++i)
	{
		if(str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 'a' - 'A';
	}
	return str;
}

bool readCmds(param *para, istream& in, bool file)
{
	if(!file)
		cout << "Enter the instructions (Enter \'./\' to finish):" << endl;
	while(true)
	{
		string str;
		static string pc = para->pc;
		if(!file)
			cout << pc << " : ";
		getline(in, str);
		str = convert_upper(str);
		if(str.compare("./") == 0)
			return true;
		if(instruction_check(str))
		{
			para = add_to_memory(para, str, pc);
			para->cmds.push_back(str);
			para->breaks.push_back(false);
		}
		else if(file)
			return false;
		else
			cout << "Invalid instruction! Enter again." << endl;
	}
	return true;
}
