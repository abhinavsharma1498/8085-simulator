#include "header.h"

int ADI(param *para)
{
	bool AC = 0, CF = 0;
	para->pc = addition(para->pc, "0001", AC, CF);
	para->registers['A'] = addition(para->registers['A'], para->memory[para->pc], AC, CF);
	para->registers['F'] = setFlags(para->registers['A'], AC, CF);
	para->pc = addition(para->pc, "0001", AC, CF);
	return 0;
}