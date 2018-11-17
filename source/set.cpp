#include "header.h"

bool setData(param *para)
{
	string addr, data;
	cout << "Enter address and data to be set before execution (Enter \'./\' to finish):" << endl;
	while(addr != "./")
	{
		cin >> addr;
		addr = convert_upper(addr);
		if(addr == "./")
			break;
		cin >> data;
		data = convert_upper(data);
		if(valid_address(addr) && valid_data(data))
			para->memory[addr] = data;
		else
			cout << "Invalid entry! Enter again." << endl;
	}
	cin.ignore();
	return true;
}
