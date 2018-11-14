#include "header.h"

int LXI(param *para)
{
	bool tmp;
	char low, high;
	if(para->memory[para->pc][4] == 'B')
	{
		low = 'C';
		high = 'B';
	}
	else if(para->memory[para->pc][4] == 'D')
	{
		low = 'E';
		high = 'D';
	}
	else if(para->memory[para->pc][4] == 'H')
	{
		low = 'L';
		high = 'H';
	}
	para->pc = addition(para->pc, "0001", tmp, tmp);
	para->registers[low] = para->memory[para->pc];
	para->pc = addition(para->pc, "0001", tmp, tmp);
	para->registers[high] = para->memory[para->pc];
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}