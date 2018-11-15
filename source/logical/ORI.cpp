#include "header.h"

int ORI(param *para)
{
	bool tmp;
	para->pc = addition(para->pc, "0001", tmp, tmp);
	para->registers['A'] = logicor(para->registers['A'], para->memory[para->pc]);
	para->registers['F'] = setFlags(para->registers['A'], false, false);
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}