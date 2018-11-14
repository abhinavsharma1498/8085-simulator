#include "header.h"

int LDA(param *para)
{
	bool tmp;
	para->pc = addition(para->pc, "0001", tmp, tmp);
	string address = para->memory[para->pc];
	para->pc = addition(para->pc, "0001", tmp, tmp);
	address = para->memory[para->pc] + address;
	para->registers['A'] = para->memory[address];
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}