#include <windows.h>

#include "LightningCore.h"
#include "LightningCMD.h"
#include "LightningTEXT.h"
#include "LightningFS.h"
#include "LightningOP.h"
#include "LightningLL.h"

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
	Lightning::FS::loadFilesystem();
	Lightning::CMD::loadFunctions();
	Lightning::TEXT::loadFunctions();
	Lightning::LL::loadFunctions();
	Lightning::OP::loadOperations();
}

void Lightning::writeBin(Lightning::OP::Opcode opcode, unsigned char Rd, unsigned char Rs1, unsigned char Rs2, short imm)
{
	using namespace Lightning;

	RAM[*PC] = opcode << 27;
	RAM[*PC] += Rd << 24;
	RAM[*PC] += Rs1 << 20;
	RAM[*PC] += Rs2 << 16;
	RAM[*PC] += static_cast<unsigned short>(imm);

	*PC += 1;
}