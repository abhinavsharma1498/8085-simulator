#include "header.h"

int DCX(param *para)
{
	bool AC = 0, CF = 0, tmp;
	if(para->memory[para->pc][4] == 'B')
	{
		string data = para->registers['B'] + para->registers['C'];
		data = subtraction(data, "0001", AC, CF, true);
		para->registers['B'] = data.substr(0, 2);
		para->registers['C'] = data.substr(2, 2);
	}
	else if(para->memory[para->pc][4] == 'D')
	{
		string data = para->registers['D'] + para->registers['E'];
		data = subtraction(data, "0001", AC, CF, true);
		para->registers['D'] = data.substr(0, 2);
		para->registers['E'] = data.substr(2, 2);
	}
	else if(para->memory[para->pc][4] == 'H')
	{
		string data = para->registers['H'] + para->registers['L'];
		data = subtraction(data, "0001", AC, CF, true);
		para->registers['H'] = data.substr(0, 2);
		para->registers['L'] = data.substr(2, 2);
	}
	para->pc = addition(para->pc, "0001", tmp, tmp);
	return 0;
}