#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <functional>
#include <conio.h>

#include "LightningOP.h"
#include "LightningCore.h"

void Lightning::OP::loadOperations()
{
	operations[HALT] = []()
	{
		mode = Mode::CMD;
		std::cout << "\nProgramme terminated. Press any key to return to CMD mode.\n";
		while (!_kbhit());
		addr = RAM;
	};

	operations[SET] = []()
	{
		REG[*operation.args[0]] = operation.args[1]->value;
		REG[*operation.args[0]].occupied = true;
	};

	operations[GET] = []()
	{
		operation.args[1]->value = REG[*operation.args[0]];
		REG[*operation.args[0]].occupied = false;
	};

	operations[RMEM] = []()
	{
		operation.args[1]->value = RAM[operation.args[0]->value];
	};

	operations[WMEM] = []()
	{
		RAM[operation.args[0]->value] = operation.args[1]->value;
	};

	operations[CALL] = []()
	{
		stack.push(addr + 2);
		addr = operation.args[0];
		addr--;
	};

	operations[RET] = []()
	{
		addr = stack.top();
		stack.pop();
	};

	operations[ADD] = []()
	{
		REG[operation.args[0]->value] = operation.args[1]->value + operation.args[2]->value;
	};

	operations[OUT] = []()
	{
		std::cout << static_cast<char>(operation.args[0]->value);
	};
}

bool Lightning::OP::parseOperation()
{
	operation.opcode = static_cast<Opcode>(addr->value);
	operation.args.clear();
	switch (operation.opcode)
	{
	case CALL:
	case OUT:
		operation.args.push_back(addr + 1);
		break;
	case SET:
	case GET:
	case RMEM:
	case WMEM:
		operation.args.push_back(addr + 1);
		operation.args.push_back(addr + 2);
		break;
	case ADD:
		operation.args.push_back(addr + 1);
		operation.args.push_back(addr + 2);
		operation.args.push_back(addr + 3);
		break;
	default:
		operation.args.resize(0);
	}
}

void Lightning::OP::processOperation()
{
	operations[operation.opcode]();
	addr += static_cast<int>(operation.args.size());
}