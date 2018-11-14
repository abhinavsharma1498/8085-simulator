#include "header.h"

int INR(param *para)
{
	bool AC = 0, CF = 0, tmp;
	if(para->memory[para->pc][4] == 'M')
	{
		string address = para->registers['H'] + para->registers['L'];
		para->memory[address] = addition(para->memory[address], "01", AC, CF);
		para->registers['F'] = setFlags(para->memory[address], AC, CF);
	}
	else
	{
		para->registers[para->memory[para->pc][4]] = addition(para->registers[para->memory[para->pc][4]], "01", AC, CF);
		para->registers['F'] = setFlags(para->registers[para->memory[para->pc][4]], AC, CF);
	}
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}