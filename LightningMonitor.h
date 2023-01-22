#ifndef LIGHTNING_MONITOR
#define LIGHTNING_MONITOR

#include <SDL.h>

#include "LightningCPU.h"

namespace Lightning::Monitor
{
	inline SDL_Texture* screen{};
	inline Uint8* pixels{};

	inline int pitch{};

	inline int* rSize{ &CPU::peripherals[CPU::monitor][0] };

	void refresh();
}

#endif