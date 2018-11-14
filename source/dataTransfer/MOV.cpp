#include "header.h"

int MOV(param *para)
{
	bool tmp;
	if(para->memory[para->pc][4] == 'M')
	{
		string address = para->registers['H'] + para->registers['L'];
		para->memory[address] = para->registers[para->memory[para->pc][6]];
	}
	else if(para->memory[para->pc][6] == 'M')
	{
		string address = para->registers['H'] + para->registers['L'];
		para->registers[para->memory[para->pc][4]] = para->memory[address];
	}
	else
		para->registers[para->memory[para->pc][4]] = para->registers[para->memory[para->pc][6]];
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}