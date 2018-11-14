#include "header.h"

int HLT(param *para)
{
	bool tmp;
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0; 
}