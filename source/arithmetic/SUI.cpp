#include "header.h"

int SUI(param *para)
{
	bool AC = false, CF = false, tmp;
	para->pc = addition(para->pc, "0001", tmp, tmp);
	string data = para->memory[para->pc];
	para->registers['A'] = subtraction(para->registers['A'], data, AC, CF, false);
	CF = !CF;
	para->registers['F'] = setFlags(para->registers['A'], AC, CF);
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}