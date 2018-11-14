#include "header.h"

int DAD(param *para)
{
	bool AC = 0, CF = 0, tmp;
	string hex1 = para->registers['H'] + para->registers['L'], hex2;
	if(para->memory[para->pc][4] == 'B')
		hex2 = para->registers['B'] + para->registers['C'];
	else if(para->memory[para->pc][4] == 'D')
		hex2 = para->registers['D'] + para->registers['E'];
	else if(para->memory[para->pc][4] == 'H')
		hex2 = para->registers['H'] + para->registers['L'];
	hex1 = addition(hex1, hex2, AC, CF);
	para->registers['H'] = hex1.substr(0, 2);
	para->registers['L'] = hex1.substr(2, 2);
	para->registers['F'] = setFlags(para->registers['H']+para->registers['L'], AC, CF);
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}