#include "header.h"

int LDAX(param *para)
{
	string address;
	bool tmp;
	if(para->memory[para->pc][5] == 'B')
		address = para->registers['B'] + para->registers['C'];
	else if(para->memory[para->pc][5] == 'D')
		address = para->registers['D'] + para->registers['E'];
	else if(para->memory[para->pc][5] == 'H')
		address = para->registers['H'] + para->registers['L'];
	para->registers['A'] = para->memory[address];
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}