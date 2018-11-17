#include "header.h"

int displayReg(param *para, char reg)
{
	cout << "Register " << reg << " : " << para->registers[reg] << endl;
	return 0;
}

int displayMem(param *para, string addr)
{
	cout << addr << " : " << para->memory[addr] << endl;
	return 0;
}

int debug(param *para, map<string, instruc> functionMap)
{
	cout << "Debugger started...\nEnter \'h\' for help." << endl;
	string str;
	int line = 0;
	while(true)
	{
		getline(cin, str);
		str = convert_upper(str);
		if(str[1] != ' ' && str.length() != 1)
		{
			cout << "No such command! Enter again." << endl;
			continue;
		}
		stringstream ss(str);
		char ch;
		ss >> ch;
		// cout << (int)ch;
		switch(ch)
		{
			case 'B':
				ss >> line;
				if(line < para->breaks.size())
				{
					para->breaks[line-1] = true;
					cout << "Breakpoint set at line " << line <<endl;
				}
				else
					cout << "Line exceeded the program! Enter again." << endl;
				line = 0;
				break;
			case 'R':
				if(str.length() == 1)
				{
					line = execute(para, functionMap, line);
					if(line != INT_MIN && para->breaks[line-1])
						cout << "Breakpoint reached." << endl;
					if(line != INT_MIN && line > para->breaks.size())
					{
						cout << "Error occurred!" <<endl;
						exit(1);
					}
					if(line == -1)
					{
						cout << "Opcode not found! HLT may be missing." << endl;
						exit(0);
					}
					if(line == INT_MIN)
					{
						display(*para);
						return 0;
					}
				}
				else
				{
					cout << "No such command! Enter again." << endl;
					cout << "Enter \'h\' for help." << endl;
				}
				break;
			case 'N':
				if(str.length() == 1)
				{
					cout << para->cmds[line] << endl;
					line = executeSingle(para ,functionMap, line);
					if(line != INT_MIN && para->breaks[line-1])
						cout << "Breakpoint reached." << endl;
					if(line == -1)
					{
						cout << "Error occurred!" <<endl;
						exit(1);
					}
					if(line == INT_MIN)
					{
						cout << "Execution complete!" << endl;
						display(*para);
						return 0;
					}
				}
				else
				{
					cout << "No such command! Enter again." << endl;
					cout << "Enter \'h\' for help." << endl;
				}
				break;
			case 'P':
				if(str.length() == 1)
					display(*para);
				else if(str.length() == 3 || str.length() == 6)
				{
					string target;
					ss >> target;
					if(target.length() == 1 && (valid_register(target[0], false) || target[0] == 'F'))
						displayReg(para, target[0]);
					else if(target.length() == 4 && valid_address(target))
						displayMem(para, target);
				}
				else
				{
					cout << "No such command! Enter again." << endl;
					cout << "Enter \'h\' for help." << endl;
				}
				break;
			case 'Q':
				if(str.length() == 1)
				{
					cout << "Are you sure? (y/n): ";
					char ch;
					cin >> ch;
					if(ch == 'y' || ch == 'Y')
					{
						cout << "Exiting..." << endl;
						return 0;
					}
				}
				else
				{
					cout << "No such command! Enter again." << endl;
					cout << "Enter \'h\' for help." << endl;
				}
				break;
			case 'H':
				if(str.length() == 1)
				{
					cout << "Debugging commands:" << endl;
					cout << "b num: Set breakpoint at line number \'num\'." << endl;
					cout << "r: Start execution of program untill breakpoint is reached." << endl;
					cout << "n: Execute a single instruction." << endl;
					cout << "p: Display value of all registers and memory used." << endl;
					cout << "p [reg]: Display value of register \'reg\'." << endl;
					cout << "p [address]: Display value at memory address \'address\'." << endl;
					cout << "q: Quit debugger and program." << endl;
				}
				else
				{
					cout << "No such command! Enter again." << endl;
					cout << "Enter \'h\' for help." << endl;
				}
				break;
			default:
				cout << "No such command! Enter again." << endl;
				cout << "Enter \'h\' for help." << endl;
		}
	}
	return 0;
}