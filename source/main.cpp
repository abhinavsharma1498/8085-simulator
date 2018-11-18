#include "header.h"

/*	Display used memory and registers
*/

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
	map<string, string>::iterator itr = para.memory.begin();	// Iterate through memory
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

/*	Driver function
*/

int main(int argc, char **argv)
{
	param para;	//	8085 memory, registers, prog counter, breakpoints
	map<string, instruc> functionMap;	//	Maps string to the function
	string epc;
	bool status = false, debugOn = false;	//	status of input and debugOn flag
	int line = 0;	//	Line number of input instruction

	//	read.cpp	int initialize(param *para);
	initialize(&para);	//	Initialize the registers of 8085 and prog counter

	//	read.cpp	int createFunctionMap(map<string, instruc> &functionMap);
	createFunctionMap(functionMap);	//	Create a map of string to function

	//	set.cpp		bool setData(param *para);
	status = setData(&para);	//	Initialize memory before starting the execution

	//	Decoding command line parameters passed
	switch(argc)
	{
		//	No parameter
		case 1:
			//	read.cpp	bool readCmds(param *para, istream& in, bool file);
			status = readCmds(&para, cin, false);	//	Read the instuctions from command line
			break;

		//	Single parameter passed, i.e. either debug mode or passing instructions from file
		case 2:
			if(strcmp(argv[1], "--debugger") == 0)	//	Debug mode on
			{
				//	read.cpp	bool readCmds(param *para, istream& in, bool file);
				status = readCmds(&para, cin, false);	//	Scan commands from console
				if(!status)
				{
					cout << "Error occurred with reading file! Exiting..." << endl;
					exit(1);
				}
				debugOn = true;

				//	debugger/debug.cpp	int debug(param *para, map<string, instruc> functionMap);
				debug(&para, functionMap);	//	Start execution in debug mode
			}
			else	//	Debug mode off
			{
				ifstream fin(argv[1]);	//	Initialize the input file pointer
				if(!fin)
				{
					cout << "File do not exist! Entering command line mode..." << endl;

					//	read.cpp	bool readCmds(param *para, istream& in, bool file);
					status = readCmds(&para, cin, false);	//	Scan commands from console if file does not exist
				}
				else
				{
					//	read.cpp	bool readCmds(param *para, istream& in, bool file);
					status = readCmds(&para, fin, true);	//	Scan commands from specified input file
					fin.close();	//	Free the file pointer
				}
			}
			break;

		//	Two parameters passed, i.e. in debug mode with input from file
		case 3:
			if(strcmp(argv[1], "--debugger") == 0)	//	Argument 2 is passed input file path
			{
				ifstream fin(argv[2]);	//	Initialize input file pointer
				if(!fin)
				{
					cout << "File do not exist! Entering command line mode..." << endl;
					//	read.cpp	bool readCmds(param *para, istream& in, bool file);
					status = readCmds(&para, cin, false);	//	Scan commands from console if file does not exist
				}
				else
				{
					//	read.cpp	bool readCmds(param *para, istream& in, bool file);
					status = readCmds(&para, fin, true);	//	Scan commands from specified input file
					fin.close();	//	Free the file pointer
				}
				if(!status)
				{
					cout << "Error occurred with reading file! Exiting..." << endl;
					exit(1);
				}
				debugOn = true;
				//	debugger/debug.cpp	int debug(param *para, map<string, instruc> functionMap);
				debug(&para, functionMap);	//	Start execution in debug mode
			}
			else if(strcmp(argv[2], "--debugger") == 0)	//	Argument 1 is passed input file path
			{
				ifstream fin(argv[1]);	//	Initialize input file pointer
				if(!fin)
				{
					cout << "File do not exist! Entering command line mode..." << endl;
					//	read.cpp	bool readCmds(param *para, istream& in, bool file);
					status = readCmds(&para, cin, false);	//	Scan commands from console if file does not exist
				}
				else
				{
					//	read.cpp	bool readCmds(param *para, istream& in, bool file);
					status = readCmds(&para, fin, true);	//	Scan commands from specified input file
					fin.close();	//	Free the file pointer
				}
				if(!status)
				{
					cout << "Error occurred with reading file! Exiting..." << endl;
					exit(1);
				}
				//	debugger/debug.cpp	int debug(param *para, map<string, instruc> functionMap);
				debug(&para, functionMap);	//	Start execution in debug mode
			}
	}
	if(!debugOn)	//	When debug mode is off
	{
		if(!status)
		{
			cout << "Error occurred with reading file! Exiting..." << endl;
			exit(1);
		}
		//	execute.cpp		int execute(param *para, map<string, instruc> functionMap, int line);
		line = execute(&para, functionMap, line);	//	Execute the assembly program
		if(line == -1)
		{
			cout << "Error occurred! Exiting..." << endl;
			exit(1);
		}
		display(para);	//	Display the 8085 status
	}
	return 0;
}
