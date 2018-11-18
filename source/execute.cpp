#include "header.h"

/*	Execute the assembly program from current program counter
*/
int execute(param *para, map<string, instruc> functionMap, int line)
{
	while(true)
	{
		//	Extracting opcode mnemonic for the instruction
		int len = para->memory[para->pc].find(' ');
		if(len == -1)
			len = para->memory[para->pc].length();
		string op = para->memory[para->pc].substr(0, len);

		//	Execute function corresponding to the opcode
		functionMap[op](para);

		//	Increment line number
		++line;

		if(op.compare("HLT") == 0)	//	If "HLT" is encountered, stop the execution of assembly program
		{
			cout << "Execution complete!" << endl;
			return INT_MIN;
		}

		//	Return error flag if next instruction is not found in memory
		if(para->memory.find(para->pc) == para->memory.end())
			return -1;

		//	Return current line number if breakpoint is encountered
		if(para->breaks[line-1])
			return line;
	}
	return line;
}
