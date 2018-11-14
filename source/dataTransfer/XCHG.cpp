#include "header.h"

int XCHG(param *para)
{
	string temp;
	bool tmp;
	temp = para->registers['D'];
	para->registers['D'] = para->registers['H'];
	para->registers['H'] = temp;
	temp = para->registers['E'];
	para->registers['E'] = para->registers['L'];
	para->registers['L'] = temp;
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}