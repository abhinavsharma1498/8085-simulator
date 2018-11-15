#include "header.h"

int CPI(param *para)
{
	bool AC, CF, tmp;
	string hex;
	para->pc = addition(para->pc, "0001", tmp, tmp);
	hex = subtraction(para->registers['A'], para->memory[para->pc], AC, CF, false);
	CF = !CF;
	para->registers['F'] = setFlags(hex, AC, CF);
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}