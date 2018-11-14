#include "header.h"

int STA(param *para)
{
	bool tmp;
	para->pc = addition(para->pc, "0001", tmp, tmp);
	string address = para->memory[para->pc];
	para->pc = addition(para->pc, "0001", tmp, tmp);
	address = para->memory[para->pc] + address;
	para->memory[address] = para->registers['A'];
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}