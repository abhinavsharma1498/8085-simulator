#include "header.h"

int MVI(param *para)
{
	bool tmp;
	if(para->memory[para->pc][4] == 'M')
	{
		string address = para->registers['H'] + para->registers['L'];
		para->pc = addition(para->pc, "0001", tmp, tmp);
		para->memory[address] = para->memory[para->pc];
	}
	else
	{
		char reg = para->memory[para->pc][4];
		para->pc = addition(para->pc, "0001", tmp, tmp);
		para->registers[reg] = para->memory[para->pc];
	}
	para->pc = addition(para->pc, "0001", tmp, tmp);	
	return 0;
}