#include <SDL.h>

#include "LightningCPU.h"
#include "LightningCore.h"

void Lightning::Core::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GetCurrentDisplayMode(0, &screen);

	window = SDL_CreateWindow("Lightning VM", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_CENTERED, screen.w, screen.h, SDL_WINDOW_FULLSCREEN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	SDL_ShowCursor(SDL_DISABLE);

	Threads::Core = SDL_CreateThread(cycle, "Core", NULL);
	Threads::CPU = SDL_CreateThread(CPU::cycle, "CPU", NULL);

	running = true;
}

int Lightning::Core::cycle(void*)
{	
	while (!running);

	while (running)
	{
		if (systemBus.control[chipSelect] == 1)
		{
			if (systemBus.control[read] == 1)
			{
				systemBus.data = RAM[systemBus.address];
				systemBus.control[read] = 0;
			}
			else if (systemBus.control[write] == 1)
			{
				RAM[systemBus.address] = systemBus.data;
				systemBus.control[write] = 0;
			}
		}
		else if (systemBus.control[read])
		{
			SDL_Log("here");
			systemBus.data = ROM[systemBus.address];
			systemBus.control[read] = 0;
		}
		SDL_Log("%d", systemBus.control[read]);
	}

	return 0;
}

void Lightning::Core::quit()
{
	SDL_WaitThread(Threads::Core, NULL);
	SDL_WaitThread(Threads::CPU, NULL);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}