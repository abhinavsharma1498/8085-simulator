#include "header.h"

int CMA(param *para)
{
	bool tmp;
	para->registers['A'] = complement(para->registers['A']);
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}