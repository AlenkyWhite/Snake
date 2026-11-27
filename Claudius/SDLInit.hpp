#pragma once
#include "SDL.h"

class SDLInit {
private:

public:
	SDLInit() {
		SDL_Init(SDL_INIT_EVERYTHING);
	}
	~SDLInit() {
		SDL_Quit();
	}

	// Delete copy operations
	SDLInit(const SDLInit&) = delete;
	SDLInit& operator=(const SDLInit&) = delete;

	// Delete move operations
	SDLInit(SDLInit&&) = delete;
	SDLInit& operator=(SDLInit&&) = delete;
};