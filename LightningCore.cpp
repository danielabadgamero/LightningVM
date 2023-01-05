#include <windows.h>
#include <iostream>

#include "LightningCore.h"

void Lightning::clearScreen()
{
	COORD tl{ 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO s{};
	HANDLE console{ GetStdHandle(STD_OUTPUT_HANDLE) };
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written{};
	DWORD cells{ static_cast<DWORD>(s.dwSize.X * s.dwSize.Y) };
	FillConsoleOutputCharacterW(console, ' ', cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

void Lightning::init()
{
	RAM = new unsigned char[1ull << 32]; // 4GB

	do
	{
		CPU.REG[IR] = ROM[CPU.PC];
		CPU.REG[IR] <<= 8;
		CPU.REG[IR] += ROM[CPU.PC + 1];
		CPU.REG[IR] <<= 8;
		CPU.REG[IR] += ROM[CPU.PC + 2];
		CPU.REG[IR] <<= 8;
		CPU.REG[IR] += ROM[CPU.PC + 3];
		CPU.process();
		CPU.PC += 4;
	} while (CPU.REG[IR]);

	CPU.PC = 0;
}

void Lightning::quit()
{
	delete RAM;
}

void Lightning::CPU::process()
{
	switch (REG[IR] >> 24)
	{
	case HALT:
		running = false;
		break;
	case SET:
		REG[(REG[IR] & Rd) >> 16] = REG[IR] & imm16;
		break;
	case SAC:
		REG[AC] = REG[IR] & imm24;
		break;
	case SAR:
		REG[AR] = REG[IR] & imm24;
		break;
	case SDR:
		REG[DR] = REG[IR] & imm24;
		break;
	case COUT:
		std::cout << static_cast<char>(REG[(REG[IR] & Rs1) >> 8]);
		break;
	case IOUT:
		std::cout << REG[(REG[IR] & Rs1) >> 8];
		break;
	case RMEM:
		REG[DR] = RAM[REG[AR]];
		break;
	case WMEM:
		RAM[REG[AR]] = REG[DR];
		break;
	default:
		REG[(REG[IR] & Rd) >> 16] = ALU.process(static_cast<int>(REG[IR] >> 24), REG[(REG[IR] & Rs1) >> 8], REG[(REG[IR] & Rs2)]);
	}
}

long long Lightning::CPU::ALU::process(int opcode, long long rs1, long long rs2)
{
	switch (opcode)
	{
	case ADD:
		return rs1 + rs2;
	case SUB:
		return rs1 - rs2;
	case MUL:
		return rs1 * rs2;
	case DIV:
		return rs1 / rs2;
	case MOD:
		return rs1 % rs2;
	case AND:
		return rs1 & rs2;
	case OR:
		return rs1 | rs2;
	case XOR:
		return rs1 ^ rs2;
	case NOT:
		return ~rs1;
	case CPY:
		return rs1;
	case LSFT:
		return rs1 << rs2;
	case RSFT:
		return rs2 >> rs1;
	default:
		return -1;
	}
}