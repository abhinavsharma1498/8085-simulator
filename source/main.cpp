#include "header.h"

int display(param para)
{
	cout<<"\nRegisters:\n";
	cout<<"A: "<<para.registers['A']<<"\t";
	cout<<"F: "<<para.registers['F']<<"\n";
	cout<<"B: "<<para.registers['B']<<"\t";
	cout<<"C: "<<para.registers['C']<<"\n";
	cout<<"D: "<<para.registers['D']<<"\t";
	cout<<"E: "<<para.registers['E']<<"\n";
	cout<<"H: "<<para.registers['H']<<"\t";
	cout<<"L: "<<para.registers['L']<<"\n";
	cout<<"\nMemory:\n";
	map<string, string>::iterator itr = para.memory.begin();
	while(itr != para.memory.end())
	{
		cout<<itr->first<<": "<<itr->second<<"\t";
		++itr;
		if(itr != para.memory.end())
		{
			cout<<itr->first<<": "<<itr->second;
			++itr;
		}
		cout<<endl;
	}
	return 0;
}

int main(int argc, char **argv)
{
	param para;
	map<string, instruc> functionMap;
	string epc;
	bool status = false, debugOn = false;
	int line = 0;
	initialize(&para);
	createFunctionMap(functionMap);
	status = setData(&para);
	switch(argc)
	{
		case 1:
			status = readCmds(&para, cin, false);
			break;
		case 2:
			if(strcmp(argv[1], "--debugger") == 0)
			{
				status = readCmds(&para, cin, false);
				if(!status)
				{
					cout << "Error occurred with reading file! Exiting..." << endl;
					exit(1);
				}
				debugOn = true;
				debug(&para, functionMap);
			}
			else
			{
				ifstream fin(argv[1]);
				if(!fin)
				{
					cout << "File do not exist! Entering command line mode..." << endl;
					status = readCmds(&para, cin, false);
				}
				else
				{
					status = readCmds(&para, fin, true);
					fin.close();
				}
			}
			break;
		case 3:
			if(strcmp(argv[1], "--debugger") == 0)
			{
				ifstream fin(argv[2]);
				if(!fin)
				{
					cout << "File do not exist! Entering command line mode..." << endl;
					status = readCmds(&para, cin, false);
				}
				else
				{
					status = readCmds(&para, fin, true);
					fin.close();
				}
				if(!status)
				{
					cout << "Error occurred with reading file! Exiting..." << endl;
					exit(1);
				}
				debugOn = true;
				debug(&para, functionMap);
			}
			else if(strcmp(argv[2], "--debugger") == 0)
			{
				ifstream fin(argv[1]);
				if(!fin)
				{
					cout << "File do not exist! Entering command line mode..." << endl;
					status = readCmds(&para, cin, false);
				}
				else
				{
					status = readCmds(&para, fin, true);
					fin.close();
				}
				if(!status)
				{
					cout << "Error occurred with reading file! Exiting..." << endl;
					exit(1);
				}
				debugOn = true;
				debug(&para, functionMap);
			}
	}
	if(!debugOn)
	{
		if(!status)
		{
			cout << "Error occurred with reading file! Exiting..." << endl;
			exit(1);
		}
		line = execute(&para, functionMap, line);
		if(line == -1)
		{
			cout << "Error occurred! Exiting..." << endl;
			exit(1);
		}
		display(para);
	}
	return 0;
}
