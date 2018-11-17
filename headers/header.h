#ifndef HEADER_H
#define HEADER_H

#include "predef.h"

struct param
{
	map<string, string> memory;
	map<char, string> registers;
	vector<bool> breaks;
	vector<string> cmds;
	string pc;
};

typedef int (*instruc)(param *);

int initialize(param*);
int createFunctionMap(map<string, instruc>&);
bool readCmds(param*, istream&, bool);
int execute(param*, map<string, instruc>, int);
string addition(string, string, bool&, bool&);
string complement(string);
string subtraction(string, string, bool&, bool&, bool);
string setFlags(string, bool, bool);
string to_bin(string);
vector<string> getParts(string);
int instruc_size(string);
bool instruction_check(string);
bool valid_register(char, bool);
bool valid_address(string);
bool valid_data(string);
bool setData(param*);
string convert_upper(string);
int debug(param*, map<string, instruc>);
int executeSingle(param*, map<string, instruc>, int);
int display(param);
string logicand(string, string);
string logicor(string, string);
string logicxor(string, string);

int ADD(param*);
int ADI(param*);
int CMA(param*);
int CMP(param*);
int CPI(param*);
int DAD(param*);
int DCR(param*);
int DCX(param*);
int INR(param*);
int INX(param*);
int SUB(param*);
int SUI(param*);
int ANA(param*);
int ANI(param*);
int ORA(param*);
int ORI(param*);
int XRA(param*);
int XRI(param*);

int LDA(param*);
int LDAX(param*);
int LHLD(param*);
int LXI(param*);
int MOV(param*);
int MVI(param*);
int SHLD(param*);
int STA(param*);
int STAX(param*);
int XCHG(param*);

int JC(param*);
int JMP(param*);
int JNC(param*);
int JNZ(param*);
int JZ(param*);

int HLT(param*);

#endif
