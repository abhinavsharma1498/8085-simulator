#include "header.h"

int executeSingle(param *para, map<string, instruc> functionMap, int line)
{
	int len = para->memory[para->pc].find(' ');
	if(len == -1)
		len = para->memory[para->pc].length();
	string op = para->memory[para->pc].substr(0, len);
	functionMap[op](para);
	++line;
	if(op.compare("HLT") == 0)
		return INT_MIN;
	if(para->memory.find(para->pc) == para->memory.end())
		return -1;
	if(para->breaks[line-1])
		return line;
	return line;
}