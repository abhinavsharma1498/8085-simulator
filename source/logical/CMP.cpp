#include "header.h"

int CMP(param *para)
{
	string hex;
	bool AC, CF, tmp;
	if(para->memory[para->pc][4] == 'M')
	{
		string address = para->registers['H'] + para->registers['L'];
		hex = subtraction(para->registers['A'], para->memory[address], AC, CF, false);
	}
	else
		hex = subtraction(para->registers['A'], para->registers[para->memory[para->pc][4]], AC, CF, false);
	CF = !CF;
	para->registers['F'] = setFlags(hex, AC, CF);
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}