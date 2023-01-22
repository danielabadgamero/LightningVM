#include <SDL.h>

#include "LightningCore.h"
#include "LightningMonitor.h"

void Lightning::Monitor::refresh()
{
	SDL_memcpy(pixels, RAM + VIDEO, *rSize);

	SDL_UpdateTexture(screen, NULL, pixels, pitch);
	SDL_RenderCopy(renderer, screen, NULL, NULL);

	SDL_RenderPresent(renderer);
}