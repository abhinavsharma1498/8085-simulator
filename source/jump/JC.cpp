#include "header.h"

int JC(param *para)
{
	string flag = to_bin(para->registers['F']);
	bool t;
	if(flag[7] == '1')
	{
		para->pc = addition(para->pc, "0001", t, t);
		string address = para->memory[para->pc];
		para->pc = addition(para->pc, "0001", t, t);
		address = para->memory[para->pc] + address;
		para->pc = addition(para->pc, "0001", t, t);
		if(para->memory.find(address) != para->memory.end())
			para->pc = address;
		else
			return 1;
	}
	else
		para->pc = addition(para->pc, "0003", t, t);
	return 0;
}