#include "header.h"

int JMP(param *para)
{
	bool tmp;
	para->pc = addition(para->pc, "0001", tmp, tmp);
	string address = para->memory[para->pc];
	para->pc = addition(para->pc, "0001", tmp, tmp);
	address = para->memory[para->pc] + address;
	para->pc = addition(para->pc, "0001", tmp, tmp);
	if(para->memory.find(address) != para->memory.end())
		para->pc = address;
	else
		return 1;
	return 0;
}