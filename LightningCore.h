#ifndef LIGHTNING_CORE
#define LIGHTNING_CORE

#include <SDL.h>

namespace Lightning
{
	inline SDL_Window* window{};
	inline SDL_Renderer* renderer{};
	inline SDL_Event e{};
	inline SDL_Point windowSize{};

	inline char RAM[1 << 24]{};	// 16MB
	inline char ROM[1 << 12]{};	// 4KB

	void init(SDL_Point);
	void cycle();
	void quit();
}

#endif