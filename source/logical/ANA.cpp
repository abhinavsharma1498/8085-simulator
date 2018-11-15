#include "header.h"

int ANA(param *para)
{
	bool tmp;
	if(para->memory[para->pc][4] == 'M')
	{
		string address = para->registers['H'] + para->registers['L'];
		para->registers['A'] = logicand(para->registers['A'], para->memory[address]);
	}
	else
	{
		para->registers['A'] = logicand(para->registers['A'], para->registers[para->memory[para->pc][4]]);
	}
	para->registers['F'] = setFlags(para->registers['A'], false, false);
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}