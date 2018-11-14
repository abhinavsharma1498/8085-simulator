#include "header.h"

int SHLD(param *para)
{
	bool tmp;
	para->pc = addition(para->pc, "0001", tmp, tmp);
	string address = para->memory[para->pc];
	para->pc = addition(para->pc, "0001", tmp, tmp);
	address = para->memory[para->pc] + address;
	para->memory[address] = para->registers['L'];
	address = addition(address, "0001", tmp, tmp);
	para->memory[address] = para->registers['H'];
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}
