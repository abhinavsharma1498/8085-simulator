#include "header.h"

int ADD(param *para)
{
	bool AC = 0, CF = 0;
	if(para->memory[para->pc][4] == 'M')
	{
		string address = para->registers['H'] + para->registers['L'];
		para->registers['A'] = addition(para->registers['A'], para->memory[address], AC, CF);
	}
	else
		para->registers['A'] = addition(para->registers['A'], para->registers[para->memory[para->pc][4]], AC, CF);
	para->registers['F'] = setFlags(para->registers['A'], AC, CF);
	para->pc = addition(para->pc, "0001", AC, CF);
	return 0;
}