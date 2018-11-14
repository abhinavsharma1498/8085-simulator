#include "header.h"

int DCR(param *para)
{
	bool AC = false, CF = false, tmp;
	if(para->memory[para->pc][4] == 'M')
	{
		string address = para->registers['H'] + para->registers['L'];
		para->memory[address] = subtraction(para->memory[address], "01", AC, CF, false);
		CF = !CF;
		para->registers['F'] = setFlags(para->memory[address], AC, CF);
	}
	else
	{
		para->registers[para->memory[para->pc][4]] = subtraction(para->registers[para->memory[para->pc][4]], "01", AC, CF, false);
		CF = !CF;
		para->registers['F'] = setFlags(para->registers[para->memory[para->pc][4]], AC, CF);
	}
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}