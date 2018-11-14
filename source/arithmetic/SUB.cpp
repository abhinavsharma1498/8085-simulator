#include "header.h"

int SUB(param *para)
{
	bool AC = 0, CF = 0, tmp;
	if(para->memory[para->pc][4] == 'M')
	{
		string address = para->registers['H'] + para->registers['L'];
		para->registers['A'] = subtraction(para->registers['A'], para->memory[address], AC, CF, false);
	}
	else
		para->registers['A'] = subtraction(para->registers['A'], para->registers[para->memory[para->pc][4]], AC, CF, false);
	CF = !CF;
	para->registers['F'] = setFlags(para->registers['A'], AC, CF);
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}