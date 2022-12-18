#ifndef LIGHTNING_OP
#define LIGHTNING_OP

#include <functional>
#include <vector>
#include <map>
#include <string>

namespace Lightning
{
	namespace OP
	{
		enum Opcode
		{
			HALT,	// <> Finish execution and return to CMD mode.
			SET,	// <a> <b> Set register <a> to <b>.
			GET,	// <a> <b> Get value from register <a> and write it to <b>.
			RMEM,	// <a> <b> Read memory from address <a> and write it to <b>.
			WMEM,	// <a> <b> Write at memory address <a> the value of <b>.
			CALL,	// <a> Push next instruction to the stack and jump to memory address <a>.
			RET,	// <> Jump to the address at the top of the stack and pop it afterwards.
			ADD,	// <a> <b> <c> Set register <a> to the sum of <b> and <c>.
			OUT,	// <a> Print the ASCII value of <a> to the console.
		};

		inline struct
		{
			Opcode opcode{};
			std::vector<int> args{};
		} operation;

		inline std::map<Opcode, std::function<void()>> operations
		{
			{ HALT, nullptr },
			{ SET, nullptr },
			{ GET, nullptr },
			{ RMEM, nullptr },
			{ WMEM, nullptr },
			{ CALL, nullptr },
			{ RET, nullptr },
			{ ADD, nullptr },
			{ OUT, nullptr },
		};

		void loadOperations();
		bool parseOperation();
		void processOperation();
	}
}

#endif